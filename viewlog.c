/*
 * File:   viewlog.c
 * Author: nihal
 *
 * Created on 11 June, 2024, 6:08 PM
 */


#include <xc.h>
#include "CBB_main.h"


extern int event_count;
extern char store[17];

int de;
char str4[17];
extern unsigned char main_f;
void view_log(char key) {
    
    static int event_add= 0x05;
    static int event_c;
    
    if(event_count != 0)
    {
        clcd_print("#VIEW LOG       ",LINE1(0));
        if(key == ALL_RELEASED)
        {
            for(int j = 0 ; j < 15 ; j++)
            {
                str4[j] = read_external_eeprom(event_add + j);
            }
            str4[15] = '\0';
            clcd_print(str4 ,LINE2(0));
        }
        /*else
    {
        clcd_print(store,LINE2(0));
    }*/
       
        if(key == MK_SW6 && event_c < event_count - 1)
        {
            CLEAR_DISP_SCREEN;
            event_add = event_add + 15;
            event_c++;
        }
        else if(key == MK_SW5 && event_c > 0)
        {
            CLEAR_DISP_SCREEN;
            event_add = event_add - 15;
            event_c--;
        }
        for(int i = 0 ; i < 15 ; i++)
        {
            str4[i] = read_external_eeprom(event_add + i);
            
        }
        str4[15] = '\0';
        clcd_print(str4, LINE2(0));
    }
    else
    {
        clcd_print("EMPTY",LINE2(4));
    }
    
    if(key == MK_SW6LO)
    {
        main_f = MENU;
        //if(de++ < 200)
        key = 0x00;
    }
    
    
    return;
}
