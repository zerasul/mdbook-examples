/**
 * Example 8: Highlight and Shadow
 **/
#include <genesis.h>

#include "sprt.h"
#include "gfx.h"


#define MAP_WITH 40
#define MAP_HEIGHT 28
#define MAXTILES MAP_WITH*MAP_HEIGHT

#define ZERA_RIGHT 1
#define ZERA_IDLE 3

#define FIRE_SPEED 4

#define MAX_WITH 320


Sprite * zera;
u16 zera_x;
u16 zera_y;

Sprite * fire;
u16 fire_x;
u16 fire_y;

void drawPriorityMap(Image *);
void handleInput();
void input_callback(u16 ,u16 ,u16 );
void handle_fire();

int main()
{
    SPR_init();
    JOY_setEventHandler(input_callback);
    u16 index=TILE_USERINDEX;
    drawPriorityMap(&bg_prio);
    index+=bg_prio.tileset->numTile;
    VDP_drawImageEx(BG_B, &bg_color1,
    TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,index), 0,0,TRUE,CPU);
    index+=bg_color1.tileset->numTile;
    zera_x=5;
    zera_y=134;
    zera = SPR_addSprite(&zera_spr,zera_x,zera_y,TILE_ATTR(PAL1,TRUE,FALSE,FALSE));
    VDP_setPalette(PAL1,zera_spr.palette->data);
    SPR_setAnim(zera,ZERA_IDLE);
    fire_x=321;
    fire_y=20;
    fire = SPR_addSprite(&fire_spr,fire_x,fire_y, TILE_ATTR(PAL3,TRUE,FALSE,FALSE));
    VDP_setPalette(PAL3,fire_spr.palette->data);
    VDP_setHilightShadow(1);
    while(1)
    {
        handleInput();
        handle_fire();
        SPR_update();
        SPR_setPosition(zera,zera_x,zera_y);
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void drawPriorityMap(Image * bg_map){
    u16 tilemap_buff[MAXTILES];
    u16* priority_map_pointer = &tilemap_buff[0];

    //init default priority Data
    for(int j=0; j<MAXTILES;j++) tilemap_buff[j]=0;

    u16 *shadow_tilemap = bg_map->tilemap->tilemap;
    u16 numTiles = MAXTILES;
    while(numTiles--){
        if(*shadow_tilemap){
            *priority_map_pointer |= TILE_ATTR_PRIORITY_MASK;
        }
        priority_map_pointer++;
        shadow_tilemap++;
    }
    VDP_setTileMapDataRectEx(BG_A,&tilemap_buff[0],0,
    0,0,MAP_WITH,MAP_HEIGHT,MAP_WITH,CPU);
}

void handleInput(){
    u16 value = JOY_readJoypad(JOY_1);

    if(value & BUTTON_RIGHT){
        zera_x++;
        SPR_setAnim(zera,ZERA_RIGHT);
        SPR_setHFlip(zera,FALSE);
    }
    if(value & BUTTON_LEFT){
        zera_x--;
        SPR_setAnim(zera,ZERA_RIGHT);
        SPR_setHFlip(zera,TRUE);
    }

    if(!(value & BUTTON_LEFT) && !(value & BUTTON_RIGHT)){
        SPR_setAnim(zera,ZERA_IDLE);
    }
}

void input_callback(u16 joy,u16 changed,u16 state){
    if (joy == JOY_1){
        if(changed & state & BUTTON_B){
            if(fire_x>MAX_WITH){
                fire_x = zera_x+16;
                fire_y = zera_y-8;
            }
        }
    }
}

void handle_fire(){
    if(fire_x<MAX_WITH){
        fire_x += FIRE_SPEED;
        SPR_setPosition(fire,fire_x,fire_y);
    }
}