/**
 * Example 4: Mouse Support
 * 
 * Show Mouse Information (you need an emulator with mouse support like Kega Fusion or a real Sega Mouse).
 **/
#include <genesis.h>


struct
{
    u16 x;
    u16 y;
    u8 portType;
}status;


void read_mouse();

int main()
{
    char bufferx[32];
    char buffery[32];
    VDP_drawText("Mouse Test", 10,5);

    status.portType= JOY_getPortType(PORT_1);
    status.x=16;
    status.y=16;
    JOY_setSupport(PORT_1,JOY_SUPPORT_MOUSE);
    while(1)
    {
        read_mouse();
        sprintf(bufferx, "X: %d",status.x);
        sprintf(buffery, "Y: %d", status.y);
        VDP_drawText(bufferx, 10,17);
        VDP_drawText(buffery, 10,19);
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void read_mouse(){
    u16 readX;
    u16 readY;
    //Only for mouse controller.
    if(status.portType == PORT_TYPE_MOUSE ){
        readX=JOY_readJoypadX(JOY_1);
        readY=JOY_readJoypadY(JOY_1);
    }
    status.x+=readX;
    status.y+=readY;
}

