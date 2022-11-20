/**
 * Hello World Example
 * Shows "Hello Sega" In Screen.
 **/
#include <genesis.h>

int main()
{
    VDP_drawText("Hello Sega!!", 10,13);
    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
