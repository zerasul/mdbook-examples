/**
 * Example 15b: Sound and Music using XGM2
 * NOTE: You need SGDK 2.00 or later for this example.
 * 
 * Test Utility for testing Music and sound.
 * Press A or B to play Music.
 * Press left or right to select sound effect
 * Press C to play Sound Effect.
 * Press Start to Stop Music and Sound.
 * NOTE: Thanks to Diego Escudero for the Melodies.
 **/
#include <genesis.h>

#include "gfx.h"
#include "music.h"
#include "sounds.h"

void inputHandler(u16 joy, u16 changed, u16 state);

u8 sound;
const u8 *sounds[3];

int main()
{
    sound = 1;
    sounds[0] = sound1;
    sounds[1] = sound2;
    sounds[2] = sound3;
    // Set volumes (new feature of XGM2 Driver)
    XGM2_setFMVolume(70);
    XGM2_setPSGVolume(60);
    u16 ind = TILE_USER_INDEX;
    VDP_drawImageEx(BG_B, &background, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, DMA);
    ind += background.tileset->numTile;
    VDP_loadTileSet(&numbers, ind, DMA);
    PAL_setPalette(PAL1, numbersPal.data, DMA);
    JOY_setEventHandler(inputHandler);

    while (1)
    {
        VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind + (sound - 1)), 19, 17);
        // For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void inputHandler(u16 joy, u16 changed, u16 state)
{

    if (joy == JOY_1)
    {
        if (changed & state & BUTTON_A)
        {

            if (XGM2_isPlaying())
            {
                XGM2_stop();
            }
            XGM2_play(music1);
        }
        else
        {
            if (changed & state & BUTTON_B)
            {
                if (XGM2_isPlaying())
                {
                    XGM2_stop();
                }
                XGM2_play(music2);
            }
            else
            {

                if (changed & state & BUTTON_C)
                {
                    XGM2_playPCM(sounds[sound - 1], sizeof(sounds[sound - 1]), SOUND_PCM_CH_AUTO);
                }
                else
                {
                    if (changed & state & BUTTON_START)
                    {
                        XGM2_stop();
                        XGM2_stopPCM(SOUND_PCM_CH_AUTO);
                    }
                    else
                    {
                        if (changed & state & BUTTON_RIGHT)
                        {
                            sound++;
                            if (sound == 4)
                                sound = 1;
                        }
                        else if (changed & state & BUTTON_LEFT)
                        {
                            sound--;
                            if (sound == 0)
                                sound = 3;
                        }
                    }
                }
            }
        }
    }
}
