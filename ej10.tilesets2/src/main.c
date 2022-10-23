/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>

#include "gfx.h"

#include "map1.h"

u16 tileMap1[1120];
u16 tileMap1b[1120];

int main()
{
    u16 ind = TILE_USER_INDEX;
    VDP_loadTileSet(&tilesetBosque,TILE_USER_INDEX,CPU);
    PAL_setPalette(PAL0,palbosque.data,CPU);
    int i,j;

    for (i = 0; i < 40; i++)
        {
        for (j = 0; j < 28; j++)
         {
            tileMap1[(i) + 40 * j]=TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, (ind-1) + map1b[(i) + 40 * j]);
            tileMap1b[(i) + 40 * j]=TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, (ind-1) + map1[(i) + 40 * j]);
         }
    }
    
    VDP_setTileMapDataRect(BG_A,tileMap1,0,0,40,28,40,CPU);
    VDP_setTileMapDataRect(BG_B,tileMap1b,0,0,40,28,40,CPU);
    

    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}
