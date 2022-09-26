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

typedef struct {
    s8 x;
    s8 y;
    s8 w;
    s8 h;
}BoxCollider;

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
                //Versions Prior to SGDK 1.80 use TILE_USERINDEX
    u16 index = TILE_USER_INDEX;
    VDP_drawImageEx(BG_B, &bg_b, TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index),0,0,TRUE,CPU);
    index+=bg_b.tileset->numTile;
    VDP_drawImageEx(BG_A, &bg_a, TILE_ATTR_FULL(PAL1,FALSE,FALSE,FALSE,index),0,0,TRUE,CPU);
    index+=bg_a.tileset->numTile;
    sha = SPR_addSprite(&shaSprt,sha_x,sha_y,TILE_ATTR(PAL2,TRUE,FALSE,FALSE));
    //versions prior to SGDK 1.80 use VDP_setPalette
    PAL_setPalette(PAL2, shaSprt.palette->data,DMA);
    elli = SPR_addSprite(&elliSprt,45, 155,TILE_ATTR(PAL3,FALSE,FALSE,FALSE));
    //versions prior to SGDK 1.80 use VDP_setPalette
    PAL_setPalette(PAL3, elliSprt.palette->data,DMA);
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

    BoxCollider sprt1Collider;
    sprt1Collider.x=sprt1->x+4;
    sprt1Collider.y=sprt1->y+4;
    sprt1Collider.w=20;
    sprt1Collider.h=26;

    BoxCollider sprt2Collider;
    sprt2Collider.x=sprt2->x+7;
    sprt2Collider.y=sprt2->y+6;
    sprt2Collider.w=18;
    sprt2Collider.h=21;
    
    s8 box1_x1 = sprt1Collider.x;
    s8 box1_y1 = sprt1Collider.y;
    s8 box1_x2 = sprt1Collider.x+sprt1Collider.w;
    s8 box1_y2 = sprt1Collider.y+sprt1Collider.h;

    s8 box2_x1 = sprt2Collider.x;
    s8 box2_y1 = sprt2Collider.y;
    s8 box2_x2 = sprt2Collider.x+sprt2Collider.w;
    s8 box2_y2 = sprt2Collider.y+sprt2Collider.h;

    if ((box1_x1 <= box2_x2) &&
            (box1_x2 >= box2_x1) &&
            (box1_y1 <= box2_y2) &&
            (box1_y2 >= box2_y1)){
                return TRUE;
            }else{
                return FALSE;
            }
}