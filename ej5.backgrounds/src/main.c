/**
 * Example 5: Backgrounds Use.
 * 
 * Show how to draw tow backgrounds
 **/
#include <genesis.h>

#include "gfx.h"

int main()
{
   
    while(1)
    {
        
        VDP_setScreenWidth320();
        // Versions prior to SGDK 1.80 use TILE_USERINDEX
        u16 ind = TILE_USER_INDEX;
        //Draw first background on layer B
        VDP_drawImageEx(BG_B,&bg_a,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
        ind+=bg_a.tileset->numTile;
        //Draw second background on layer A, and uses second palette with black color as transparent color.
        VDP_drawImageEx(BG_A,&bg_b,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
        ind+=bg_b.tileset->numTile;
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
