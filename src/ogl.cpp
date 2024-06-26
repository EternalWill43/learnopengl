#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 35044
#define GL_VERTEX_SHADER 35633
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_CLAMP 0x2900
#define GL_CLAMP_TO_BORDER 0x812D

char* CStrFromFile(std::string path)
{
  std::ifstream file(path, std::ios::binary);
  if (!file)
  {
    std::cout << "File does not exist\n";
    return nullptr;
  }
  file.seekg(0, file.end);
  int length = file.tellg();
  file.seekg(0, file.beg);
  char* buf = new char[length + 1];
  file.read(buf, length);
  buf[length] = '\0';
  return buf;
}

#ifndef RELEASE
const char* frag_file = CStrFromFile("./src/shaders/frag.glsl");
const char* vert_file = CStrFromFile("./src/shaders/vert.glsl");
#endif

const char* fragment_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "  \n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "\n"
    "uniform sampler2D texture1;\n"
    "uniform sampler2D texture2;\n"
    "uniform float flip;\n"
    "uniform float opacity;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec2 coord = vec2((flip != 0.0 ? 1.0f - TexCoord.x : TexCoord.x), TexCoord.y);\n"
    "    FragColor = mix(texture(texture1, TexCoord), texture(texture2, coord), opacity);\n"
    "   // FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
    "}";

const char* vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 transform;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = transform * vec4(aPos, 1.0);\n"
    "    ourColor = aColor;\n"
    "    TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}";

// NOTE: Can't statically link the binary if I have to do file i/o
// char* vertex_source = CStrFromFile("./src/shaders/vert.glsl");
// const char* vertex_shader_from_file = vertex_source;
// char* frag_source = CStrFromFile("./src/shaders/frag.glsl");
// const char* fragment_shader_from_file = frag_source;

typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;

typedef void(APIENTRY* GL_GENBUFFERS)(GLsizei, GLuint*);
typedef void(APIENTRY* GL_BINDBUFFER)(GLenum, GLuint);
typedef void(APIENTRY* GL_BUFFERDATA)(GLenum, GLsizeiptr, const void*, GLenum);
typedef GLuint(APIENTRY* GL_CREATESHADER)(GLenum);
typedef void(APIENTRY* GL_SHADERSOURCE)(GLuint, GLsizei, const GLchar**, const GLint*);
typedef void(APIENTRY* GL_COMPILESHADER)(GLuint);
typedef GLuint(APIENTRY* GL_CREATEPROGRAM)(void);
typedef void(APIENTRY* GL_ATTACHSHADER)(GLuint, GLuint);
typedef void(APIENTRY* GL_LINKPROGRAM)(GLuint);
typedef void(APIENTRY* GL_USEPROGRAM)(GLuint);
typedef void(APIENTRY* GL_DELETESHADER)(GLuint);
typedef void(
    APIENTRY* GL_VERTEXATTRIBPOINTER)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void(APIENTRY* GL_ENABLEVERTEXATTRIBARRAY)(GLuint);
typedef void(APIENTRY* GL_GENVERTEXARRAYS)(GLsizei, GLuint*);
typedef void(APIENTRY* GL_BINDVERTEXARRAY)(GLuint);
typedef void(APIENTRY* GL_BUFFERSUBDATA)(GLenum, GLintptr, GLsizeiptr, const void* data);
typedef void(APIENTRY* GL_DELETEVERTEXARRAYS)(GLsizei, const GLuint*);
typedef void(APIENTRY* GL_DELETEBUFFERS)(GLsizei, const GLuint*);
typedef void(APIENTRY* GL_DELETEPROGRAM)(GLuint);
typedef void(APIENTRY* GL_UNIFORM4F)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef GLint(APIENTRY* GL_GETUNIFORMLOCATION)(GLuint, const GLchar*);
typedef void(APIENTRY* GL_GENERATEMIPMAP)(GLenum);
typedef void(APIENTRY* GL_ACTIVETEXTURE)(GLenum);
typedef void(APIENTRY* GL_UNIFORM1I)(GLint, GLint);
typedef void(APIENTRY* GL_UNIFORM1F)(GLint, GLfloat);
typedef void(APIENTRY* GL_GETUNIFORMFV)(GLuint, GLint, GLfloat*);
typedef void(APIENTRY* GL_UNIFORMMATRIX4FV)(GLint, GLsizei, GLboolean, const GLfloat*);

GL_GENBUFFERS glGenBuffers = NULL;
GL_BINDBUFFER glBindBuffer = NULL;
GL_BUFFERDATA glBufferData = NULL;
GL_CREATESHADER glCreateShader = NULL;
GL_SHADERSOURCE glShaderSource = NULL;
GL_COMPILESHADER glCompileShader = NULL;
GL_CREATEPROGRAM glCreateProgram = NULL;
GL_ATTACHSHADER glAttachShader = NULL;
GL_LINKPROGRAM glLinkProgram = NULL;
GL_USEPROGRAM glUseProgram = NULL;
GL_DELETESHADER glDeleteShader = NULL;
GL_VERTEXATTRIBPOINTER glVertexAttribPointer = NULL;
GL_ENABLEVERTEXATTRIBARRAY glEnableVertexAttribArray = NULL;
GL_GENVERTEXARRAYS glGenVertexArrays = NULL;
GL_BINDVERTEXARRAY glBindVertexArray = NULL;
GL_BUFFERSUBDATA glBufferSubData = NULL;
GL_DELETEVERTEXARRAYS glDeleteVertexArrays = NULL;
GL_DELETEBUFFERS glDeleteBuffers = NULL;
GL_DELETEPROGRAM glDeleteProgram = NULL;
GL_UNIFORM4F glUniform4f = NULL;
GL_GETUNIFORMLOCATION glGetUniformLocation = NULL;
GL_GENERATEMIPMAP glGenerateMipmap = NULL;
GL_ACTIVETEXTURE glActiveTexture = NULL;
GL_UNIFORM1I glUniform1i = NULL;
GL_UNIFORM1F glUniform1f = NULL;
GL_GETUNIFORMFV glGetUniformfv = NULL;
GL_UNIFORMMATRIX4FV glUniformMatrix4fv = NULL;

void ValidateGLFunctions()
{
  if (glGenBuffers == NULL)
  {
    std::cout << "glGenBuffers function null\n";
    exit(1);
  }
  if (glBindBuffer == NULL)
  {
    std::cout << "glBindBuffer function null\n";
    exit(1);
  }
  if (glBufferData == NULL)
  {
    std::cout << "glBufferData function null\n";
    exit(1);
  }
  if (glCreateShader == NULL)
  {
    std::cout << "glCreateShader function null\n";
    exit(1);
  }
  if (glShaderSource == NULL)
  {
    std::cout << "glShaderSource function null\n";
    exit(1);
  }
  if (glCompileShader == NULL)
  {
    std::cout << "glCompileShader function null\n";
    exit(1);
  }
  if (glCreateProgram == NULL)
  {
    std::cout << "glCreateProgram function null\n";
    exit(1);
  }
  if (glAttachShader == NULL)
  {
    std::cout << "glAttachShader function null\n";
    exit(1);
  }
  if (glLinkProgram == NULL)
  {
    std::cout << "glLinkProgram function null\n";
    exit(1);
  }
  if (glUseProgram == NULL)
  {
    std::cout << "glUseProgram function null\n";
    exit(1);
  }
  if (glDeleteShader == NULL)
  {
    std::cout << "glDeleteShader function null\n";
    exit(1);
  }
  if (glVertexAttribPointer == NULL)
  {
    std::cout << "glVertexAttribPointer function null\n";
    exit(1);
  }
  if (glEnableVertexAttribArray == NULL)
  {
    std::cout << "glEnableVertexAttribArray function null\n";
    exit(1);
  }
  if (glGenVertexArrays == NULL)
  {
    std::cout << "glGenVertexArrays function null\n";
    exit(1);
  }
  if (glBindVertexArray == NULL)
  {
    std::cout << "glBindVertexArray function null\n";
    exit(1);
  }
  if (glBufferSubData == NULL)
  {
    std::cout << "glBufferSubData function null\n";
  }
  if (glDeleteVertexArrays == NULL)
  {
    std::cout << "glDeleteVertexArrays function null\n";
  }
  if (glDeleteBuffers == NULL)
  {
    std::cout << "glDeleteBuffers function null\n";
    exit(1);
  }
  if (glDeleteProgram == NULL)
  {
    std::cout << "glDeleteProgram function null\n";
    exit(1);
  }
  if (glUniform4f == NULL)
  {
    std::cout << "glUniform4f function null\n";
    exit(1);
  }
  if (glGetUniformLocation == NULL)
  {
    std::cout << "glGetUniformLocation function null\n";
    exit(1);
  }
  if (glGenerateMipmap == NULL)
  {
    std::cout << "glGenerateMipmap function null\n";
    exit(1);
  }
  if (glActiveTexture == NULL)
  {
    std::cout << "glActiveTexture function is null\n";
    exit(1);
  }
  if (glUniform1i == NULL)
  {
    std::cout << "glUniform1i function is null\n";
    exit(1);
  }
  if (glUniform1f == NULL)
  {
    std::cout << "glUniform1f function is null\n";
    exit(1);
  }
  if (glGetUniformfv == NULL)
  {
    std::cout << "glGetUniformfv function is null\n";
    exit(1);
  }
  if (glUniformMatrix4fv == NULL)
  {
    std::cout << "glUniformMatrix4fv function is null\n";
  }
}

void InitializeOpenGlFunctions()
{
  glGenBuffers = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
  glBindBuffer = (GL_BINDBUFFER)wglGetProcAddress("glBindBuffer");
  glBufferData = (GL_BUFFERDATA)wglGetProcAddress("glBufferData");
  glCreateShader = (GL_CREATESHADER)wglGetProcAddress("glCreateShader");
  glShaderSource = (GL_SHADERSOURCE)wglGetProcAddress("glShaderSource");
  glCompileShader = (GL_COMPILESHADER)wglGetProcAddress("glCompileShader");
  glCreateProgram = (GL_CREATEPROGRAM)wglGetProcAddress("glCreateProgram");
  glAttachShader = (GL_ATTACHSHADER)wglGetProcAddress("glAttachShader");
  glLinkProgram = (GL_LINKPROGRAM)wglGetProcAddress("glLinkProgram");
  glUseProgram = (GL_USEPROGRAM)wglGetProcAddress("glUseProgram");
  glDeleteShader = (GL_DELETESHADER)wglGetProcAddress("glDeleteShader");
  glVertexAttribPointer = (GL_VERTEXATTRIBPOINTER)wglGetProcAddress("glVertexAttribPointer");
  glEnableVertexAttribArray =
      (GL_ENABLEVERTEXATTRIBARRAY)wglGetProcAddress("glEnableVertexAttribArray");
  glGenVertexArrays = (GL_GENVERTEXARRAYS)wglGetProcAddress("glGenVertexArrays");
  glBindVertexArray = (GL_BINDVERTEXARRAY)wglGetProcAddress("glBindVertexArray");
  glBufferSubData = (GL_BUFFERSUBDATA)wglGetProcAddress("glBufferSubData");
  glDeleteVertexArrays = (GL_DELETEVERTEXARRAYS)wglGetProcAddress("glDeleteVertexArrays");
  glDeleteBuffers = (GL_DELETEBUFFERS)wglGetProcAddress("glDeleteBuffers");
  glDeleteProgram = (GL_DELETEPROGRAM)wglGetProcAddress("glDeleteProgram");
  glUniform4f = (GL_UNIFORM4F)wglGetProcAddress("glUniform4f");
  glGetUniformLocation = (GL_GETUNIFORMLOCATION)wglGetProcAddress("glGetUniformLocation");
  glGenerateMipmap = (GL_GENERATEMIPMAP)wglGetProcAddress("glGenerateMipmap");
  glActiveTexture = (GL_ACTIVETEXTURE)wglGetProcAddress("glActiveTexture");
  glUniform1i = (GL_UNIFORM1I)wglGetProcAddress("glUniform1i");
  glUniform1f = (GL_UNIFORM1F)wglGetProcAddress("glUniform1f");
  glGetUniformfv = (GL_GETUNIFORMFV)wglGetProcAddress("glGetUniformfv");
  glUniformMatrix4fv = (GL_UNIFORMMATRIX4FV)wglGetProcAddress("glUniformMatrix4fv");
}

void SetMat4(unsigned int shaderProgram, char* name, float* mat)
{
  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, mat);
}