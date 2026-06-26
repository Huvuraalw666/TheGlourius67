#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <time.h>

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

int main(int argc, char **argv) {

    // 1. The video of the stupid thing starts
    VIDEO_Init();
    
    // 2. Configure You SON Stickers
    rmode = VIDEO_GetPreferredMode(NULL);
    
    // 3. Reserve The Aura
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    
    // 4. Configure the Tung Tung Tung Sahur
    console_init(xfb, 0, 0, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
    
    // 5. Apply The Sigma's tips
    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if(rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();

    // 6. Clear Brainrot
    printf("\x1b[2J");

    // 7. Initialize THE DIH
    WPAD_Init();

    // Seed for chance
    srand(time(NULL)); 

    // Nuevas variables de control
    int speed_divider = 5; 
    int frame_counter = 0;

while(1) {
        WPAD_ScanPads();
        u32 pressed = WPAD_ButtonsDown(0);

        // Home button to release the AURA
        if (pressed & WPAD_BUTTON_HOME) exit(0);

        // Meme Reset
        if (pressed & WPAD_BUTTON_1) {
            printf("\x1b[2J");
        }

        // Tralalero TralaRUN
        if (pressed & WPAD_BUTTON_2) {
            speed_divider = (speed_divider == 5) ? 20 : 5;
        }

        //  C++ / C sucks my penis
        if (frame_counter % speed_divider == 0) {
            int x = (rand() % 80) + 1; 
            int y = (rand() % 25) + 1;
            int color = 31 + (rand() % 7); 

            printf("\x1b[%d;%dH\x1b[%dm67\x1b[0m", y, x, color);
        }
        
        frame_counter++;
        VIDEO_WaitVSync();
    }

    return 0;
}
