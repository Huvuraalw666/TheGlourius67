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
    
    // 2. Configure preferred video mode
    rmode = VIDEO_GetPreferredMode(NULL);
    
    // 3. Reserve memory for the Framebuffer
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
    
    // 4. Configure the console to use that framebuffer
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
    
    // 5. Apply video settings
    VIDEO_Configure(rmode);
    VIDEO_SetNextFramebuffer(xfb);
    VIDEO_SetBlack(FALSE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    if(rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();

    // 6. Clear the screen (set it to a fucking black initial color so the text stands out)
    printf("\x1b[2J");

    // 7. Initialize the Wiimote
    WPAD_Init();

    // Seed for chance
    srand(time(NULL)); 

    while(1) {
        WPAD_ScanPads();
        u32 pressed = WPAD_ButtonsDown(0);

        // bye bye
        if (pressed & WPAD_BUTTON_HOME) exit(0);

        // --- THE GLOURIUS 67 ---
        // Generate coordinates (Y between 1-24, X between 1-75)
        int x = (rand() % 75) + 1; 
        int y = (rand() % 24) + 1;
        
        // ANSI Color (31 to 37)
        int color = 31 + (rand() % 7); 

        // Position cursor and print 67
        // The sequence \x1b[H moves the cursor to the indicated position
        printf("\x1b[%d;%dH\x1b[%dm67\x1b[0m", y, x, color);

        // Force it to be drawn on the screen
        VIDEO_WaitVSync();
    }

    return 0;
}
        //SHUT UP FUCK UP NIGGERRRRRRRRRRRREEEEEEEEEEERRRRRRRRRRRRRRRR