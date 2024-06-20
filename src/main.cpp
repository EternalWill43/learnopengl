#include <Windows.h>
// -----------------------
#include <gl/GL.h>
//------
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <random>

#include "ogl.cpp"

const int TARGET_FPS = 120;
const double FRAME_DURATION = 1000.0 / TARGET_FPS;
static int64_t global_perf_count_frequency;
constexpr float PI = 3.14159265358979323846f;
static unsigned int flip_location;
static float flip = 0.0f;
static float reset = 0;
static float opacity = 0.2f;
static float angle = 0.15f;
static float z_rotate = 1.0;
static float x_rotate = 1.0;
static float y_rotate = 1.0;
static uint8_t r_down = 0;
static uint8_t x_down = 0;
static uint8_t z_down = 0;
static uint8_t y_down = 0;
static float rotation_speed = 2.0f;

#if RELEASE
const char* container_path = "./container.jpg";
const char* awesome_path = "./awesomeface.png";
#else
const char* container_path = "./src/container.jpg";
const char* awesome_path = "./src/awesomeface.png";
#endif

union Vec3
{
  struct
  {
    float x;
    float y;
    float z;
  };
  struct
  {
    float r;
    float g;
    float b;
  };
  float v[3];
};

struct Vec3F2
{
  float x;
  float y;
  float z = 0.0f;
};

double RandomDouble(float min, float max)
{
  // Set up random number generation
  std::random_device rd;                           // Seed source
  std::mt19937 gen(rd());                          // Mersenne Twister engine
  std::uniform_real_distribution<> dis(min, max);  // Uniform distribution between min and max

  return dis(gen);  // Generate and return the random float
}

inline LARGE_INTEGER Win32GetWallClock()
{
  LARGE_INTEGER Result;
  QueryPerformanceCounter(&Result);
  return Result;
}

inline float Win32GetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End)
{
  float Result = ((float)End.QuadPart - Start.QuadPart) / (float)global_perf_count_frequency;
  return Result;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  if (yoffset > 0.0f)
  {
    opacity += 0.1f;
    if (opacity > 1.0f)
      opacity = 1.0f;
  }
  else
  {
    opacity -= 0.1f;
    if (opacity < 0.0f)
      opacity = 0.0f;
  }
}

void handleKeyToggle(GLFWwindow* window, int key, float* toggle, uint8_t* keyState)
{
  if (glfwGetKey(window, key) == GLFW_PRESS && !(*keyState))
  {
    *toggle = *toggle ? 0 : 1;
    *keyState = 1;
  }
  if (glfwGetKey(window, key) == GLFW_RELEASE && *keyState)
  {
    *keyState = 0;
  }
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    flip = 1.0f;
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    flip = 0.0f;
  if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
  {
    rotation_speed -= 0.05f;
  }
  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
  {
    rotation_speed += 0.05f;
  }
  handleKeyToggle(window, GLFW_KEY_X, &x_rotate, &x_down);
  handleKeyToggle(window, GLFW_KEY_Y, &y_rotate, &y_down);
  handleKeyToggle(window, GLFW_KEY_Z, &z_rotate, &z_down);
  handleKeyToggle(window, GLFW_KEY_R, &reset, &r_down);
}

void RotateTriangles(Vec3F2 arr[], size_t count)
{
  for (size_t i = 0; i < count; i += 2)
  {
    float cosTheta, sinTheta;
    cosTheta = cos(angle);
    sinTheta = sin(angle);
    float x = arr[i].x;
    float y = arr[i].y;
    arr[i].x = x * cosTheta - y * sinTheta;
    arr[i].y = x * sinTheta + y * cosTheta;
  }
}

int main()
{
  LARGE_INTEGER perf_freq_result;
  QueryPerformanceFrequency(&perf_freq_result);
  global_perf_count_frequency = perf_freq_result.QuadPart;
  TIMECAPS caps;
  timeGetDevCaps(&caps, sizeof(caps));
  UINT DesiredSchedulerMS = 1;
  bool SleepIsGranular = (timeBeginPeriod(DesiredSchedulerMS) == TIMERR_NOERROR);
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
  glfwSetScrollCallback(window, scroll_callback);
  glfwMakeContextCurrent(window);

  InitializeOpenGlFunctions();
  ValidateGLFunctions();

  unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
#if RELEASE
  glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
#else
  glShaderSource(vertex_shader, 1, &vert_file, NULL);
#endif
  glCompileShader(vertex_shader);

  unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
#if RELEASE
  glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
#else
  glShaderSource(fragment_shader, 1, &frag_file, NULL);
#endif
  glCompileShader(fragment_shader);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertex_shader);
  glAttachShader(shaderProgram, fragment_shader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  // ------------------------------------------------------------------
  float vertices[] = {
      // positions          // colors           // texture coords
      0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
      -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
  };
  unsigned int indices[] = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };

  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 0.5));
  // trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // load and create a texture
  // -------------------------
  unsigned int texture1, texture2;
  // texture 1
  // ---------
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(
      true);  // tell stb_image.h to flip loaded texture's on the y-axis.
  // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any
  // IDE/platform; replace it with your own image path.
  unsigned char* data = stbi_load(container_path, &width, &height, &nrChannels, 0);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  // texture 2
  // ---------
  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // load image, create texture and generate mipmaps
  data = stbi_load(awesome_path, &width, &height, &nrChannels, 0);
  if (data)
  {
    // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to
    // tell OpenGL the data type is of GL_RGBA
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
  // -------------------------------------------------------------------------------------------
  glUseProgram(shaderProgram);
  // either set it manually like so:
  glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
  // or set it via the texture class
  glUniform1i(glGetUniformLocation(shaderProgram, "texture2"), 1);
  flip_location = glGetUniformLocation(shaderProgram, "flip");
  float flip_value;
  int opacity_location = glGetUniformLocation(shaderProgram, "opacity");
  unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
  // render loop
  // -----------
  int once = 1;
  while (!glfwWindowShouldClose(window))
  {
    // Input processing
    processInput(window);
    LARGE_INTEGER start = Win32GetWallClock();

    // Clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Check if reset is triggered and reset the transformation matrix
    if (reset)
    {
      trans = glm::mat4(1.0f);  // Reset the transformation matrix to identity
      reset = 0;                // Reset the flag
    }

    // Apply rotation if any of the rotation flags are set
    if (x_rotate || y_rotate || z_rotate)
    {
      trans =
          glm::rotate(trans, glm::radians(rotation_speed), glm::vec3(x_rotate, y_rotate, z_rotate));
    }
    // trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));

    // Send the transformation matrix to the vertex shader
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

    // Bind textures to texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // Set other uniform variables
    glUniform1f(flip_location, flip);
    glUniform1f(opacity_location, opacity);

    // Use the shader program and bind the VAO
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // Draw the elements
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glm::mat4 second = glm::mat4(1.0f);
    float deltaTime = sin((float)glfwGetTime());
    second = glm::rotate(second, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    second = glm::translate(second, glm::vec3(-0.5f, 0.5f, 0.0f));
    second = glm::rotate(second, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
    second = glm::scale(second, glm::vec3(deltaTime, deltaTime, deltaTime));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(second));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Swap buffers and poll IO events
    glfwSwapBuffers(window);
    glfwPollEvents();

    LARGE_INTEGER end = Win32GetWallClock();
    float time_elapsed = Win32GetSecondsElapsed(start, end);
    if (FRAME_DURATION - time_elapsed > 0)
    {
      Sleep(static_cast<int>(FRAME_DURATION - time_elapsed));
    }
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}