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

u16 xord;
u16 countpixel;
u16 col_update;
u16 ind;


void inputHandle();
void updatePhisics();
int main()
{
    player.x=20;
    player.y=135;
    player.offset=0;
    countpixel=0;
    xord=0;
    SPR_init();
    ind = TILE_USER_INDEX;
    VDP_drawImageEx(BG_B,&sky,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    ind+= sky.tileset->numTile;
    VDP_drawImageEx(BG_A,&map1,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    player.elliSprt=SPR_addSprite(&elli,20,135,TILE_ATTR(PAL2,FALSE,FALSE,FALSE));
    SPR_setAnim(player.elliSprt,IDLE);
    VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);
    PAL_setPalette(PAL2,elli.palette->data,CPU);
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
            xord=1;
        }else{
            player.x+=2;
            xord=0;
        }
       
        
    }else{
        xord=0;
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
    SPR_setPosition(player.elliSprt,player.x,player.y);
    if(xord>0){
        player.offset+=2;
        countpixel++;
        if(countpixel>7) countpixel=0;
    }

    if(player.offset>1023) player.offset=0;
    if(countpixel==0){
        col_update=(((player.offset+320)>>3)&79);
        VDP_setMapEx(BG_A,map1.tilemap,TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,ind),col_update,0,col_update,0,1,28);
    }
    VDP_setHorizontalScroll(BG_A,-player.offset);
}
