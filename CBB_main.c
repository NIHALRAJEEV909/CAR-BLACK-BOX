/*
 * File:   CBB_main.c
 * Author: nihal
 *
 * Created on 29 May, 2024, 8:26 AM
 */


#include <xc.h>
#include "CBB_main.h"
#include "CBB_ADC.h"
#include "CBB_clcd.h"
#include "CBB_matrix_keypad.h"
#include "CBB_i2c.h"
#include "CBB_ds1307.h"


char main_f = 0, menu_f = 0, key;

void init_config(void) {
   
    init_adc();
    init_clcd();
    init_matrix_keypad();
  
    init_i2c();
    init_ds1307();
    
    PEIE = 1;
    ADCON1 = 0x0F;
    GIE = 1;
    
    for(int x = 0 ; x < 4 ; x++)
    {
        write_external_eeprom(0x00 + x, '5');
    }
    
    
}

void main(void) {
    
    init_config();
    //store_event();

    while (1) {
        //main_f = MENU;
        /*
         * get the time 
         * based on switch press change the event
         */
        
        event_store = event_index;
        /* Reading key */
        key = read_switches(LEVEL_CHANGE);
        
        /*if(key == MK_SW9)
        {
            print();
        }*/
        
        if (main_f == DASHBOARD) {
            dashboard(key);
        } else if (main_f == PASSWORD) {
            password(key);
        } else if (main_f == MENU) {
            menu(key);
        } else if (main_f == MENU_ENTER) {
            if (menu_f == VIEWLOG) {
                view_log(key);
            } else if (menu_f == DOWNLOADLOG) {
                download_log();
            } else if (menu_f == CLEARLOG) {
                clear_log(key);
            } else if (menu_f == SETTIME) {
                settime(key);
            } else if (menu_f == CHANGEPASS) {
                change_pass(key);
            }
        }
        if(event_store != event_index)
        {
            store_event();
            //print();
        }

    }
    return;
}