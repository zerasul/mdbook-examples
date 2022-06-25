/**
 * Example 5: Backgrounds Use.
 **/
#include <genesis.h>

#include "gfx.h"

int main()
{
   
    while(1)
    {
        
        VDP_setScreenWidth320();
        u16 ind = TILE_USERINDEX;
        VDP_drawImageEx(BG_B,&bg_a,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
        ind+=bg_a.tileset->numTile;
        VDP_drawImageEx(BG_A,&bg_b,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
        ind+=bg_b.tileset->numTile;
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
