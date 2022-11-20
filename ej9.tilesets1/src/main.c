/**
 * Example 9: TileMap generated Using TMX File
 * 
 * Generates a TileMap Using an TMX and TSX File.
 * 
 * NOTE: This example needs SGDK 1.80 or later.
 **/
#include <genesis.h>

#include "tileset.h"

int main()
{
    //Versions prior to SGDK 1.80 use TILE_USERINDEX
    u16 ind = TILE_USER_INDEX;
    //Load TileSet
    VDP_loadTileSet(&mapabosque, ind, DMA);
    //Set TileSet pallete
    PAL_setPalette(PAL0,palbosque.data,DMA);
    //Draw Each TileMap.
    VDP_setTileMap(BG_B,&map1,0,0,map1.w,map1.h,DMA);
    VDP_setTileMap(BG_A,&map1b,
    0,0,map1b.w,map1b.h,DMA);
    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
