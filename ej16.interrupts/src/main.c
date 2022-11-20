/**
 * Example 16: VBlank Interrupt
 * 
 * Uses VBlank Interrupt to update Sprite animation,position,etc.
 **/
#include <genesis.h>
#include "gfx.h"
#include "sprt.h"

#define IDLE 4
#define LEFT 3
#define RIGHT 1
#define UP 0
#define DOWN 2


struct{
    Sprite* sprite;
    u16 x;
    u16 y;
    u8 anim;
}player;

void vblank_int_function();

void handleInput();


int main()
{
    SYS_disableInts();
    u16 ind = TILE_USER_INDEX;
    VDP_drawImageEx(BG_A,&back1,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,CPU);
    ind+=back1.tileset->numTile;
    player.x=30;
    player.y=20;
    player.anim=IDLE;
    PAL_setPalette(PAL1,player_sprt.palette->data,CPU);
    player.sprite = SPR_addSprite(&player_sprt,player.x,player.y,TILE_ATTR(PAL1,FALSE,FALSE,FALSE));
    
    SYS_enableInts();
    //Set VBlank Interrupt function.
    SYS_setVBlankCallback(vblank_int_function);

    
    while(1)
    {
        handleInput();
        //For versions prior to SGDK 1.60 
        // use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void vblank_int_function(){

    SPR_setPosition(player.sprite,player.x,player.y);
    SPR_setAnim(player.sprite,player.anim);
    SPR_update();
}


void handleInput(){
    u16 value = JOY_readJoypad(JOY_1);

    if(value & BUTTON_RIGHT){
        player.anim= RIGHT;
        player.x++;
    }else{
        if(value & BUTTON_LEFT){
            player.anim=LEFT;
            if(player.x>5)
                player.x--;
        }else{
            if(value & BUTTON_UP){
                player.anim=UP;
                if(player.y>5)
                    player.y--;
            }else{
                if(value & BUTTON_DOWN){
                    player.anim=DOWN;
                    player.y++;
                }else{
                    player.anim=IDLE;
                }
            }
        }
    }
}
