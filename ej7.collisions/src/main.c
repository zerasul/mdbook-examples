/**
 * Example 7. Collisions
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
int checkCollision(Sprite*, Sprite*);



int main()
{
    char buffer[30];

    JOY_init();
    JOY_setEventHandler(asyncReadInput);
    SPR_init();
    
    VDP_setScreenWidth320();
    u16 index = TILE_USERINDEX;
    VDP_drawImageEx(BG_B, &bg_b, TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),0,0,TRUE,CPU);
    index+=bg_b.tileset->numTile;
    VDP_drawImageEx(BG_A, &bg_a, TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,index),0,0,TRUE,CPU);
    index+=bg_a.tileset->numTile;
    sha = SPR_addSprite(&shaSprt,sha_x,sha_y,TILE_ATTR(PAL2,TRUE,FALSE,FALSE));
    VDP_setPalette(PAL2,shaSprt.palette->data);
    elli = SPR_addSprite(&elliSprt,45, 155,TILE_ATTR(PAL3,FALSE,FALSE,FALSE));
    VDP_setPalette(PAL3,elliSprt.palette->data);
    SPR_setAnim(sha,SHA_STAY);
    SPR_setAnim(elli,4);
    while(1)
    {

        readInput();
        SPR_setPosition(sha,sha_x,sha_y);
        SPR_update();
        int collision = checkCollision(sha, elli);
        sprintf(buffer, "Collision: %d", collision);
        VDP_drawText(buffer,3,3);
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
                 shaPrio=TRUE;
                 elliPrio=FALSE;
                 SPR_setZ(sha,shaPrio);
                 SPR_setZ(elli,elliPrio);
        }
        if(changed & state &  BUTTON_B){
                 shaPrio=FALSE;
                 elliPrio=TRUE;
                 SPR_setZ(sha,shaPrio);
                 SPR_setZ(elli,elliPrio);
        }
    }
}

int checkCollision(Sprite* sprt1, Sprite* sprt2){

    BoxCollision collision1 =
        sprt1->frame->collision->hit.box;
    BoxCollision collision2 = 
        sprt2->frame->collision->hit.box;
    
    s8 box1_x1 = collision1.x;
    s8 box1_y1 = collision1.y;
    s8 box1_x2 = collision1.x+collision1.w;
    s8 box1_y2 = collision1.y+collision1.h;

    s8 box2_x1 = collision2.x;
    s8 box2_y1 = collision2.y;
    s8 box2_x2 = collision2.x+collision2.w;
    s8 box2_y2 = collision2.y+collision2.h;

    if ((box1_x1 <= box2_x2) &&
            (box1_x2 >= box2_x1) &&
            (box1_y1 <= box2_y2) &&
            (box1_y2 >= box2_y1)){
                return TRUE;
            }else{
                return FALSE;
            }
}