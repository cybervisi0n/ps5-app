#include <stdio.h>
#include <cstddef>
#include <cstdint>
#include <algorithm>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>

typedef struct notify_request {
  char useless1[45];
  char message[3075];
} notify_request_t;

extern "C" {
   int sceKernelSendNotificationRequest(int, notify_request_t*, size_t, int);
}

const char * VertexShaderSource =
#include "shaders/vertex.glsl"
;

const char * FragmentShaderSource =
#include "shaders/fragment.glsl"
;


static constexpr EGLint surface_type = EGL_WINDOW_BIT;
static constexpr EGLint SurfaceInfo[] = {
   EGL_SURFACE_TYPE, surface_type,
   EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
   EGL_RED_SIZE, 8,
   EGL_GREEN_SIZE, 8,
   EGL_BLUE_SIZE, 8,
   EGL_ALPHA_SIZE, 8,
   EGL_DEPTH_SIZE, 24,
   EGL_NONE};

static constexpr EGLint ContextInfo[] = {
   EGL_CONTEXT_MAJOR_VERSION_KHR,3,
   EGL_CONTEXT_MINOR_VERSION_KHR,3,
   EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,
   EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,
   EGL_NONE};


struct Vertex {
   float x;
   float y;
   float z;
   float r;
   float g;
   float b;
   float a;
};

static constexpr Vertex TriangleVerts[] = {
    {  0.0f,  0.5f, 0.0f,        1.0f,   0,   0, 1.0f },
    { -0.5f, -0.5f, 0.0f,          0, 1.0f,   0, 1.0f },
    {  0.5f, -0.5f, 0.0f,          0,   0, 1.0f, 1.0f },
};

static GLuint CompileShader(int type, const char * shaderSource) {
   GLuint shader = glCreateShader(type);
   GLint success = 0;
   glShaderSource(shader, 1, &shaderSource, nullptr);
   glCompileShader(shader);
   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
   if(!success) {
      notify_request_t debugMessage = {};
      int len;

      sprintf(debugMessage.message, "Failed to compile shader:");
      sceKernelSendNotificationRequest(0, &debugMessage, sizeof(debugMessage), 0);

      glGetShaderInfoLog(shader, sizeof(debugMessage.message), &len, debugMessage.message);
      sceKernelSendNotificationRequest(0, &debugMessage, sizeof(debugMessage), 0);

      return static_cast<GLuint>(-1);
   }

   return shader;
} 

int main() {
   EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   EGLSurface surface = EGL_NO_SURFACE;
   EGLContext context = EGL_NO_CONTEXT;
   EGLConfig config = NULL; 
   EGLint count = 0;
   notify_request_t debugMessage = {};

   eglInitialize(display, NULL, NULL);
   eglBindAPI(EGL_OPENGL_API);
   eglChooseConfig(display, SurfaceInfo, &config, 1, &count);
   surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)0, NULL);
   context = eglCreateContext(display, config, EGL_NO_CONTEXT, ContextInfo);
   eglMakeCurrent(display,surface,surface,context);

   GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, VertexShaderSource);
   GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, FragmentShaderSource);

   GLuint program = glCreateProgram();

   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);
   glLinkProgram(program);
   
   GLint linkSuccess = 0;
   glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);

   if(!linkSuccess) {
      sprintf(debugMessage.message, "Failed to link shader");
      sceKernelSendNotificationRequest(0, &debugMessage, sizeof(debugMessage), 0);
   }

   glUseProgram(program);

   GLuint vbo, vao;
   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
   glGenBuffers(1, &vbo);
   glBindBuffer(GL_ARRAY_BUFFER, vbo);

   // Position
   glEnableVertexAttribArray(0); 
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
   
   // Color
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));

   glBufferData(GL_ARRAY_BUFFER,sizeof(TriangleVerts),TriangleVerts,GL_DYNAMIC_DRAW);
   glDisable(GL_DEPTH_TEST);

   while(true) {
      glClear(GL_COLOR_BUFFER_BIT);
      glDrawArrays(GL_TRIANGLES, 0, sizeof(TriangleVerts) / sizeof(Vertex));
      eglSwapBuffers(display, surface);
   }

   return 0;
}
