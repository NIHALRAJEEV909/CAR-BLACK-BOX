/*
 * File:   clear_log.c
 * Author: nihal
 *
 * Created on 13 June, 2024, 1:40 PM
 */


#include <xc.h>
#include "CBB_main.h"

extern int event_count;
extern char main_f;
int delay10;
int del;

void clear_log(char key) {
    
    event_count = 0;
    
    if(delay10++ <1000)
    {
        clcd_print("LOGS CLEARED",LINE1(0));
    }
    
    if(key == MK_SW6LO)
    {
       main_f = MENU;
       for(unsigned long int k = 90000; k--;);
    CLEAR_DISP_SCREEN;
    if(del++ < 200)
    key = 0x00;
    }
  
    return;
}
