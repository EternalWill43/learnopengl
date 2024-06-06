#include <Windows.h>
#include <gl/GL.h>
#include <glfw3.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "ogl.cpp"

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

void RotateTriangles(Vec3F2 arr[], size_t count, float angle = 0.1f)
{
  for (size_t i = 0; i < count; ++i)
  {
    float cosTheta, sinTheta;
    if (i % 2 == 0)
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
  glfwSwapInterval(1);

  InitializeOpenGlFunctions();
  ValidateGLFunctions();

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader2, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader2);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  unsigned int shaderProgram2 = glCreateProgram();
  glAttachShader(shaderProgram2, vertexShader);
  glAttachShader(shaderProgram2, fragmentShader2);
  glLinkProgram(shaderProgram2);

  glDeleteShader(fragmentShader2);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float firstTriangle[] = {-0.9f, -0.5f, 0.0f, -0.0f, -0.5f, 0.0f, -0.45f, 0.5f, 0.0f};
  float secondTriangle[] = {0.0f, -0.5f, 0.0f, 0.9f, -0.5f, 0.0f, 0.45f, 0.5f, 0.0f};
  unsigned int VBOs[2], VAOs[2];
  glGenVertexArrays(2, VAOs);
  glGenBuffers(2, VBOs);

  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgram);

  glfwTerminate();

  return 0;
}