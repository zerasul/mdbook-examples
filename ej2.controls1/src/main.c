/**
 * Example 2: 
 * Syncrhonous controls.
 **/
#include <genesis.h>
#include "constants.h"

void printChar(char *, u16, u16);
void readInput();

int main()
{
   
    while(1)
    {
        readInput();

        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void printChar(char * text, u16 tilex, u16 tiley){
    VDP_drawText(text,tilex,tiley);
}

void readInput(){

    int value = JOY_readJoypad(JOY_1);

    
    if (value & BUTTON_UP)
        printChar(UP_TEXT, POSX_UP, POSY_UP);
    else
        printChar(EMPTY_TEXT, POSX_UP, POSY_UP);

    if (value & BUTTON_LEFT)
        printChar(LEFT_TEXT, POSX_LEFT, POSY_LEFT);
    else
        printChar(EMPTY_TEXT, POSX_LEFT, POSY_LEFT);
    if (value & BUTTON_RIGHT)
        printChar(RIGTH_TEXT, POSX_RIGHT, POSY_RIGHT);
    else
        printChar(EMPTY_TEXT, POSX_RIGHT, POSY_RIGHT);
    if( value & BUTTON_DOWN)
         printChar(DOWN_TEXT, POSX_DOWN, POSY_DOWN);
    else
        printChar(EMPTY_TEXT, POSX_DOWN, POSY_DOWN);

    if (value & BUTTON_A)
        printChar(A_TEXT, POSX_A, POSY_RIGHT);
    else
        printChar(EMPTY_TEXT, POSX_A, POSY_RIGHT);
    
    if(value & BUTTON_B)
        printChar(B_TEXT, POSX_B, POSY_RIGHT);
    else
        printChar(EMPTY_TEXT, POSX_B, POSY_RIGHT);
    
    if(value & BUTTON_C)
        printChar(C_TEXT, POSX_C, POSY_RIGHT);
    else
        printChar(EMPTY_TEXT, POSX_C, POSY_RIGHT);
    
    if(value & BUTTON_START)
        printChar(START_TEXT, POSX_START, POSY_RIGHT);
    else
        printChar(EMPTY_TEXT, POSX_START, POSY_RIGHT);
    
}