/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include "gfx.h"
#include "sprt.h"

#define RIGTH 1
#define LEFT 3
#define IDLE 4

struct{
    Sprite* elliSprt;
    u16 x;
    u16 y;
    u16 offset;
}player;


u16 ind;

Map * map;


void inputHandle();
void updatePhisics();
int main()
{
    player.x=20;
    player.y=135;
    player.offset=0;
    
    SPR_init();
    ind = TILE_USER_INDEX;
    VDP_drawImageEx(BG_B,&sky,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    ind+= sky.tileset->numTile;
    PAL_setPalette(PAL1,pltmap.data,DMA);
    VDP_loadTileSet(&map_tileset,ind,DMA);
    map=MAP_create(&map1,BG_A,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind));

    player.elliSprt=SPR_addSprite(&elli,20,135,TILE_ATTR(PAL2,FALSE,FALSE,FALSE));
    SPR_setAnim(player.elliSprt,IDLE);
    PAL_setPalette(PAL2,elli.palette->data,CPU);
    VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);
   
    while(1)
    {
        inputHandle();
        updatePhisics();
        SPR_update();
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void inputHandle(){
    u16 value = JOY_readJoypad(JOY_1);

    if(value & BUTTON_RIGHT){
        SPR_setAnim(player.elliSprt, RIGTH);
         if(player.x>220){
           player.offset+=2;
        }else{
            player.x+=2;
        }   
    }else{
        if(value & BUTTON_LEFT){
            SPR_setAnim(player.elliSprt, LEFT);
            
             if(player.x>5){
             player.x-=2;
            }
        }else{
            if(!(value & BUTTON_LEFT) && !(value & BUTTON_RIGHT)){
                SPR_setAnim(player.elliSprt,IDLE);
            }
        }
    }
}

void updatePhisics(){
    if(player.offset>320) player.offset=0;
    SPR_setPosition(player.elliSprt,player.x,player.y);
    MAP_scrollTo(map,player.offset,0);
}
