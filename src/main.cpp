#include <stdio.h>
#include <cstddef>
#include <cstdint>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GL/gl.h>


extern "C" {
    int sceSystemServiceHideSplashScreen();
    int sceVideoOutOpen(std::int32_t user_id, std::int32_t bus_type, std::int32_t index,
                        const void *param);
    int sceVideoOutSetFlipRate(std::int32_t handle, std::int32_t rate);
    int sceVideoOutSubmitFlip(std::int32_t handle, std::int32_t buffer_index,
                              std::uint32_t flip_mode, std::int64_t flip_argument);
    int sceVideoOutWaitVblank(std::int32_t handle);

}



int main() {
    sceSystemServiceHideSplashScreen();
    const int video = sceVideoOutOpen(0xff, 0, 0, nullptr);
    sceVideoOutSetFlipRate(video, 0);

   const EGLint surface_type = EGL_WINDOW_BIT;
   const EGLint ca[] = {EGL_SURFACE_TYPE,surface_type,EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,
      EGL_RED_SIZE,8,EGL_GREEN_SIZE,8,EGL_BLUE_SIZE,8,EGL_ALPHA_SIZE,8,EGL_DEPTH_SIZE,24,EGL_NONE};
   const EGLint ctx[] = {EGL_CONTEXT_MAJOR_VERSION_KHR,3,EGL_CONTEXT_MINOR_VERSION_KHR,3,
      EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR,EGL_NONE};
   EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
   EGLSurface surface = EGL_NO_SURFACE;
   EGLContext context = EGL_NO_CONTEXT;
   EGLConfig config = NULL; EGLint count = 0;
   GLuint vs = 0, fs = 0, program = 0, vao = 0, vbo = 0, instances = 0;
   int current = 0, passed = 0, clean = 1;
   unsigned completed = 0;


    
    printf("Hello world\n");
    int frameCount = 0;
    while(true) {
        if(frameCount > 600) {
            break;
        }
        sceVideoOutWaitVblank(video);
        frameCount++;
    }
    //SDL_Init(SDL_INIT_VIDEO);
    return 0;
}
