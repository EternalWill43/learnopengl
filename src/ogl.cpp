#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 35044
#define GL_VERTEX_SHADER 35633
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_ELEMENT_ARRAY_BUFFER 0x8893

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

const char* fragment_shader_source =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "in vec4 pos;\n"
    "uniform sampler2D ourTexture;"
    "void main()\n"
    "{\n"
    "  FragColor = texture(ourTexture, TexCoord);\n"
    "};";

const char* vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord\n"
    "out vec3 ourColor;\n"
    "out vec4 pos;\n"
    "out vec2 TexCoord;\n"
    "uniform float xOffset;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x + xOffset, aPos.y, aPos.z, 1.0);\n"
    "   ourColor = aColor;\n"
    "   pos = gl_Position;\n"
    "   TexCoord = aTexCoord;\n"
    "};";

// NOTE: Can't statically link the binary if I have to do file i/o
// char* vertex_source = CStrFromFile("./src/shaders/vert.glsl");
// const char* vertex_shader_from_file = vertex_source;
// char* frag_source = CStrFromFile("./src/shaders/frag.glsl");
// const char* fragment_shader_from_file = frag_source;

typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;

typedef void (*GL_GENBUFFERS)(GLsizei, GLuint*);
typedef void (*GL_BINDBUFFER)(GLenum, GLuint);
typedef void (*GL_BUFFERDATA)(GLenum, GLsizeiptr, const void*, GLenum);
typedef GLuint (*GL_CREATESHADER)(GLenum);
typedef void (*GL_SHADERSOURCE)(GLuint, GLsizei, const GLchar**, const GLint*);
typedef void (*GL_COMPILESHADER)(GLuint);
typedef GLuint (*GL_CREATEPROGRAM)(void);
typedef void (*GL_ATTACHSHADER)(GLuint, GLuint);
typedef void (*GL_LINKPROGRAM)(GLuint);
typedef void (*GL_USEPROGRAM)(GLuint);
typedef void (*GL_DELETESHADER)(GLuint);
typedef void (*GL_VERTEXATTRIBPOINTER)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (*GL_ENABLEVERTEXATTRIBARRAY)(GLuint);
typedef void (*GL_GENVERTEXARRAYS)(GLsizei, GLuint*);
typedef void (*GL_BINDVERTEXARRAY)(GLuint);
typedef void (*GL_BUFFERSUBDATA)(GLenum, GLintptr, GLsizeiptr, const void* data);
typedef void (*GL_DELETEVERTEXARRAYS)(GLsizei, const GLuint*);
typedef void (*GL_DELETEBUFFERS)(GLsizei, const GLuint*);
typedef void (*GL_DELETEPROGRAM)(GLuint);
typedef void (*GL_UNIFORM4F)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef GLint (*GL_GETUNIFORMLOCATION)(GLuint, const GLchar*);
typedef void (*GL_GENERATEMIPMAP)(GLenum);

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
