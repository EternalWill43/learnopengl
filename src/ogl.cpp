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
    return "";
  }
  file.seekg(0, file.end);
  int length = file.tellg();
  file.seekg(0, file.beg);
  char* buf = new char[length + 1];
  file.read(buf, length);
  buf[length] = '\0';
  return buf;
}

char* vertex_source = CStrFromFile("./src/shaders/vert.glsl");
const char* vertex_shader_from_file = vertex_source;
char* frag_source = CStrFromFile("./src/shaders/frag.glsl");
const char* fragment_shader_from_file = frag_source;

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
}