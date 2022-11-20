/**
 * Example 11: Line Scroll
 * 
 * Use Line Scroll to deform a Logo Image
 **/
#include <genesis.h>

#include "gfx.h"

s16 lines[224];

int main()
{
    u16 index = TILE_USER_INDEX;
    VDP_drawImageEx(BG_B,&logo,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),0,0,TRUE,DMA);
    //Set Scroll Mode
    VDP_setScrollingMode(HSCROLL_LINE,VSCROLL_PLANE);
    int i;
    for(i=0;i<224;i++){
        lines[i]=0;
    }    
    while(1)
    {
        
        for(i=84;i<121;i+=2){
            lines[i]+=2;
        }

        for(i=85;i<120;i+=2){
            lines[i]-=2;
        }
        //Generate Line Scroll
        VDP_setHorizontalScrollLine(BG_B,0,lines,224,DMA_QUEUE);
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
