#include <stdio.h>
#include <cstddef>
#include <cstdint>

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
