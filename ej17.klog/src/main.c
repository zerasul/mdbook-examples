/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>

#define DEBUG 1

void handleAsyncInput(u16, u16, u16);

int main()
{
    VDP_drawText("Hello Sega!!", 10,13);
    JOY_setEventHandler(handleAsyncInput);
    while(1)
    {
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
    return (0);
}

void handleAsyncInput(u16 joy, u16 state, u16 changed){
    char button='\0';
    if(joy == JOY_1){
        if(state & changed & BUTTON_A){
            button='A';
        }else{
            if(state & changed & BUTTON_B){
             button='B';
            }else{
                if(state & changed & BUTTON_C){
                    button='C';
                }
            }
        }
        #ifdef DEBUG
        if(changed & state)
            kprintf("Button Pushed: %c \n",button);
        #endif
    }
}
