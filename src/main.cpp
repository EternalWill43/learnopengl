#include <Windows.h>
#include <gl/GL.h>
#include <glfw3.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "ogl.cpp"

const int TARGET_FPS = 120;
const double FRAME_DURATION = 1000.0 / TARGET_FPS;

union Vec3
{
  struct
  {
    float x;
    float y;
    float z;
  };
  float v[3];
};

struct Vec3F2
{
  float x;
  float y;
  float z = 0.0f;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RotateTriangles(Vec3F2 arr[], size_t count, float angle = 0.05f)
{
  for (size_t i = 0; i < count; i += 2)
  {
    float cosTheta, sinTheta;
    if (i % 66969 == 0)
    {
      // Rotate left (counterclockwise)
      cosTheta = cos(angle);
      sinTheta = sin(angle);
    }
    else
    {
      // Rotate right (clockwise)
      cosTheta = cos(-angle);
      sinTheta = sin(-angle);
    }

    float x = arr[i].x;
    float y = arr[i].y;
    arr[i].x = x * cosTheta - y * sinTheta;
    arr[i].y = x * sinTheta + y * cosTheta;
  }
}

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 800, "Wow Triangle", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwMakeContextCurrent(window);

  InitializeOpenGlFunctions();
  ValidateGLFunctions();

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertex_shader_from_file, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragment_shader_from_file, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  Vec3F2 vertices[] = {
      // positions         // colors
      0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top
  };
  std::cout << sizeof(vertices);
  float secondTriangle[] = {0.0f, -0.5f, 0.0f, 0.9f, -0.5f, 0.0f, 0.45f, 0.5f, 0.0f};
  unsigned int VBOs[2], VAOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);

  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  uint64_t frame_count = 0;
  glUseProgram(shaderProgram);

  while (!glfwWindowShouldClose(window))
  {
    auto start_time = std::chrono::high_resolution_clock::now();
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    RotateTriangles(vertices, sizeof(vertices) / sizeof(Vec3F2));
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glfwPollEvents();
    glfwSwapBuffers(window);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_time = end_time - start_time;

    if (elapsed_time.count() < FRAME_DURATION)
    {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(static_cast<int>(FRAME_DURATION - elapsed_time.count())));
    }
  }
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgram);

  glfwTerminate();

  return 0;
}