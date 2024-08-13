#include <stdio.h>
#include <stdlib.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

#include <asndlib.h>
#include <mp3player.h>
#include "sample_mp3.h"

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

void init_audio() {
    ASND_Init();
    MP3Player_Init();
    
    MP3Player_PlayBuffer(sample_mp3, sample_mp3_size, NULL);
}

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

    // Initialise the video system
    VIDEO_Init();

    // This function initialises the attached controllers
    WPAD_Init();
	
	// Audio Subsystem
	init_audio();

    // Obtain the preferred video mode from the system
    // This will correspond to the settings in the Wii menu
    rmode = VIDEO_GetPreferredMode(NULL);

    // Allocate memory for the display in the uncached region
    xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

    // Initialise the console, required for printf
    console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);

    // Set up the video registers with the chosen mode
    VIDEO_Configure(rmode);

    // Tell the video hardware where our display memory is
    VIDEO_SetNextFramebuffer(xfb);

    // Make the display visible
    VIDEO_SetBlack(false);

    // Flush the video register changes to the hardware
    VIDEO_Flush();

    // Wait for Video setup to complete
    VIDEO_WaitVSync();
    if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();

    // Position the cursor
    printf("\x1b[2;0H");

    // Set the color to light blue (94 is light blue)
    printf("\x1b[36;1m"); // Cyan text color

// Ocean
    printf("                          ..--------------------..\n");
    printf("                         |``--------------------''|\n");
    printf("                         |                        |\n");
    printf("                         |      ,,,;;;;;;,,,      |\n");
    printf("                         |   ,;;;;;;;;;;;;;;;;,   |\n");
    printf("                         |  ;;;;;;;;;;;;;;;;;;;;  |\n");
    printf("                         | ;;;;;;;;;'''  _  '';;; |\n");
    printf("                         |   _'''_  _   (_'  |  ` |\n");
    printf("                         |  |_) |_  |_) ._)  |    |\n");
    printf("                         | .|   |_  |     .....   |\n");
    printf("                         | :::..     ...::::::::: |\n");
	printf("                         |  ::::::::::::::::::::  |\n");
	printf("                         |   '::::::::::::::::'   |\n");
	printf("                         |      '''::::::'''      |\n");
	printf("                         |                        |\n");
	printf("                         |                        |\n");
	printf("                         ';----..............----;'\n");
	printf("                           '--------------------'\n");
	//Additional lines to separate the can and the bottom text
	printf("\n");
	printf("\n");
	
	


    // Set a blue background and white text for the header
    printf("\x1b[44;37m  Wii Pepsi by August Wolf                             Press HOME to exit.  \x1b[40;37m\n");
    printf("\x1b[44;37m                                                                            \x1b[40;37m\n");
    printf("\x1b[44;37m               Pepsi and Pepsi Man are owned by PepsiCo, Inc.               \x1b[40;37m\n");
	
    while (1) {
        // Call WPAD_ScanPads each loop, this reads the latest controller states
        WPAD_ScanPads();

        // WPAD_ButtonsDown tells us which buttons were pressed in this loop
        // this is a "one shot" state which will not fire again until the button has been released
        u32 pressed = WPAD_ButtonsDown(0);

        // We return to the launcher application via exit
        if (pressed & WPAD_BUTTON_HOME) exit(0);

        // Wait for the next frame
        VIDEO_WaitVSync();
    }

    return 0;
}
