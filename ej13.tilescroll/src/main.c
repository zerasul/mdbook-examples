/**
 * Example 13: Tile Scroll
 * 
 * Uses 2 Tile Column Scroll to generate Rain Efect.
 **/
#include <genesis.h>

#include "gfx.h"

int main()
{
    VDP_setScreenWidth320();
    u16 ind = TILE_USER_INDEX;
    VDP_loadTileSet(&rain,ind,DMA);
    PAL_setPalette(PAL1,rainplt.data,CPU);
    u16 tileMap[2048];
    int i;
    for(i=0;i<2048;i++){
        tileMap[i]=TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind);
    }
    VDP_setTileMapDataRect(BG_A,tileMap,0,0,40,32,40,DMA_QUEUE);
    ind+=rain.numTile;
    VDP_drawImageEx(BG_B,&city,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    ind+= city.tileset->numTile;
    //Set Scroll Mode
    VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_2TILE);  
    
    s16 scrollVector[20];
  
    for(i=0;i<20;i++){
        scrollVector[i]=0;
    }

    
    while(1)
    {
        for(i=0;i<20;i++){
            scrollVector[i]-=2;
        }
        //Set 2 Tile Scroll
        VDP_setVerticalScrollTile(BG_A,0,scrollVector,20,DMA);
        SYS_doVBlankProcess();
    }
    return (0);
}
