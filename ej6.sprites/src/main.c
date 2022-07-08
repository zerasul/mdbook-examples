/**
 * Example 6. Sprites
 **/
#include <genesis.h>

#include "gfx.h"
#include "sprt.h"

#define SHA_UP 0
#define SHA_DOWN 2
#define SHA_LEFT 3
#define SHA_RIGHT 1
#define SHA_STAY 4


Sprite * sha;
Sprite * elli;

u16 sha_x=15;
u16 sha_y=125;

int shaPrio=TRUE;
int elliPrio=FALSE;

void readInput();
void asyncReadInput(u16,u16,u16);

char buffer[20];
char buffer2[20];

int main()
{
    JOY_init();
    JOY_setEventHandler(asyncReadInput);
    SPR_init();
    
    VDP_setScreenWidth320();
    u16 index = TILE_USERINDEX;
    VDP_drawImageEx(BG_B, &bg_b, TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),0,0,TRUE,CPU);
    index+=bg_b.tileset->numTile;
    VDP_drawImageEx(BG_A, &bg_a, TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,index),0,0,TRUE,CPU);
    index+=bg_a.tileset->numTile;
    sha = SPR_addSprite(&shaSprt,sha_x,sha_y,TILE_ATTR_FULL(PAL2,TRUE,FALSE,FALSE,index));
    VDP_setPalette(PAL2,shaSprt.palette->data);
    elli = SPR_addSprite(&elliSprt,45, 155,TILE_ATTR_FULL(PAL3,TRUE,FALSE,FALSE,index));
    VDP_setPalette(PAL3,elliSprt.palette->data);
    SPR_setAnimAndFrame(sha,2,1);
    SPR_setAnim(sha,SHA_STAY);
    SPR_setAnim(elli,4);
    while(1)
    {

        readInput();
        SPR_setPosition(sha,sha_x,sha_y);
        SPR_update();
        sprintf(buffer,"Sha Priority: %d",shaPrio);
        sprintf(buffer2,"Elli Priority: %d", elliPrio);
        VDP_drawText(buffer,4,2);
        VDP_drawText(buffer2,4,3);
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}


void readInput(){
    int inputValue = JOY_readJoypad(JOY_1);

    if(inputValue & BUTTON_DOWN){
        SPR_setAnim(sha,SHA_DOWN);
        sha_y++;
    }else{
        if(inputValue & BUTTON_UP){
            SPR_setAnim(sha,SHA_UP);
            sha_y--;
        }else{
            if(inputValue & BUTTON_LEFT){
                SPR_setAnim(sha,SHA_LEFT);
                sha_x--;
            }else{
                if(inputValue & BUTTON_RIGHT){
                    SPR_setAnim(sha,SHA_RIGHT);
                    sha_x++;
                }else{
                    SPR_setAnim(sha,SHA_STAY);
                }
            }
        }
    }
}

void asyncReadInput(u16 joy,u16 changed,u16 state){

    if(joy == JOY_1){
        if(changed & state &  BUTTON_A){
                 shaPrio=(shaPrio==TRUE)? FALSE:TRUE;
                 SPR_setPriority(sha,shaPrio);
        }
        if(changed & state &  BUTTON_B){
                 elliPrio=(elliPrio==TRUE)? FALSE:TRUE;
                 SPR_setPriority(elli,elliPrio);
        }
    }
}