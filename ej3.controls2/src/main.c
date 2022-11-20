/**
 * Example 3: Asynchronous Controls
 * 
 * Uses and Input Handler Function when a button is Pressed
 **/
#include <genesis.h>
#include "constants.h"

void inputHandler(u16,u16,u16);
void printChar(char*, u16, u16);

int main()
{
    JOY_init();
	//Sets Input Event Handler
    JOY_setEventHandler(inputHandler);

    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void printChar(char* text, u16 tilex, u16 tiley){
    VDP_drawText(text,tilex,tiley);
}

void inputHandler(u16 joy,u16 changed,u16 state){


        if (changed & state & BUTTON_START)
		{
			printChar(START_TEXT, POSX_START, POSY_RIGHT);
		}
		else 
		{
			printChar(EMPTY_TEXT, POSX_START, POSY_RIGHT);	
		}

        if (changed & state & BUTTON_UP)
		{
			printChar(UP_TEXT, POSX_UP, POSY_UP);
		}
		else 
		{
			printChar(EMPTY_TEXT, POSX_UP, POSY_UP);	
		}

        if (changed & state & BUTTON_LEFT)
		{
			printChar(LEFT_TEXT, POSX_LEFT, POSY_LEFT);
		}
		else 
		{
			printChar(EMPTY_TEXT, POSX_LEFT, POSY_LEFT);	
		}

        if (changed & state & BUTTON_DOWN)
		{
			printChar(DOWN_TEXT, POSX_DOWN, POSY_DOWN);
		}
		else 
		{
			printChar(EMPTY_TEXT, POSX_DOWN, POSY_DOWN);	
		}

        if (changed & state & BUTTON_RIGHT)
		{
			printChar(RIGTH_TEXT, POSX_RIGHT, POSY_RIGHT);
		}
		else 
		{
			printChar(EMPTY_TEXT, POSX_RIGHT, POSY_RIGHT);	
		}


        if (changed & state & BUTTON_A)
		{
			printChar(A_TEXT, POSX_A, POSY_RIGHT);
		}
		else 
		{
			printChar(EMPTY_TEXT, POSX_A, POSY_RIGHT);	
		}

        if (changed & state & BUTTON_B)
		{
			printChar(B_TEXT, POSX_B, POSY_RIGHT);
		}
		else 
		{
			printChar(EMPTY_TEXT, POSX_B, POSY_RIGHT);	
		}

        if (changed & state & BUTTON_C)
		{
			printChar(C_TEXT, POSX_C, POSY_RIGHT);
		}
		else 
		{
			printChar(EMPTY_TEXT, POSX_C, POSY_RIGHT);	
		}
}