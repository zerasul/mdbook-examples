/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>

#include "gfx.h"
#include "music.h"
#include "sounds.h"

void inputHandler(u16 joy, u16 changed, u16 state);

u8 sound;
const u8* sounds[3];

int main()
{
    sound=1;
    sounds[0]=sound1;
    sounds[1]=sound2;
    sounds[2]=sound3;
    u16 ind = TILE_USER_INDEX;
    VDP_drawImageEx(BG_B,&background,TILE_ATTR_FULL(PAL0,FALSE,FALSE,FALSE,ind),0,0,TRUE,DMA);
    JOY_setEventHandler(inputHandler);
    
    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void inputHandler(u16 joy, u16 changed, u16 state){

    if(joy == JOY_1){
        if(changed & state & BUTTON_A){

            if(XGM_isPlaying()){
                XGM_stopPlay();
            }
           XGM_startPlay(music1);
            
        }else{
            if(changed & state & BUTTON_B){
                if(XGM_isPlaying()){
                    XGM_stopPlay();
                }
                XGM_startPlay(music2);
            }else{

                if(changed & state & BUTTON_C){
                    XGM_setPCM(sound,sounds[sound-1],sizeof(sounds[sound-1]));
                    XGM_startPlayPCM(sound,14,SOUND_PCM_CH4);
                }else{
                    if(changed & state & BUTTON_START){
                        XGM_stopPlay();
                        XGM_stopPlayPCM(3);
                    }else{
                        if(changed & state & BUTTON_RIGHT){
                            sound++;
                            if(sound==4) sound=1;
                        }else if (changed & state & BUTTON_RIGHT)
                        {
                            if(sound==0) sound=3;
                        }
                    }

                }
                
            }
        }
    }
}

