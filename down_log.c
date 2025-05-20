/*
 * File:   down_log.c
 * Author: nihal
 *
 * Created on 13 June, 2024, 12:16 PM
 */





#include <xc.h>
#include "CBB_main.h"

extern int event_count;
char down_store[17];
extern char main_f;

void download_log() {
    
    
    init_uart();
    //int i = 1;
    int down_add = 0x05;
    
    
    clcd_print("DOWNLOADING....",LINE1(0));
    for (unsigned long int k = 900000; k--;);
    for(int j = 0 ; j < event_count ; j++)
    {
        for(int k = 0 ; k < 15 ; k++)
        {
            down_store[k] = read_external_eeprom(down_add + k);
        }
        down_store[15] = '\0';
        down_add = down_add + 15;
        //puts(i);
        puts( down_store);
        puts("\n\r");
        //i++;
    }
    CLEAR_DISP_SCREEN;
    clcd_print("DOWNLOADING....",LINE1(0));
    clcd_print("WAIT...",LINE2(4));
    for (unsigned long int k = 10000; k--;);
    //for (unsigned long int k = 900000; k--;);
    main_f = MENU;
    return;
}
 