/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>

#include "tileset.h"

int main()
{
    //Versions prior to SGDK 1.80 use TILE_USERINDEX
    u16 ind = TILE_USER_INDEX;
    VDP_loadTileSet(&mapabosque, ind, DMA);
    PAL_setPalette(PAL0,palbosque.data,DMA);
    VDP_setTileMapEx(BG_B,&map1,
    TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),
    0,0,0,0,map1.w,map1.h,DMA);
    VDP_setTileMapEx(BG_A,&map1b,
    TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),
    0,0,0,0,map1b.w,map1b.h,DMA);
    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
