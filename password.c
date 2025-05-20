/*
 * File:   password.c
 * Author: nihal
 *
 * Created on 5 June, 2024, 1:52 PM
 */


#include <xc.h>
#include <string.h>
#include "CBB_main.h"
#include "CBB_matrix_keypad.h"
#include "CBB_clcd.h"
#include "CBB_timer0.h"
#include "CBB_isr.h"


static int attempt = 3, i = 0, j = 0;
static unsigned long int delay, delay1;
char pass[5];
char enter[5];
extern char key;
extern unsigned int sec;
extern char main_f;
extern unsigned count0;
extern int pass_add = 0x00;
int dela;

void password(char key) {


    if (attempt != 0) {
        clcd_print("ENTER PASSWORD", LINE1(0));

        if (i < 4) {

            if (delay++ < 1000) {
                clcd_putch('_', LINE2(i));
                //clcd_print("ENTER PASSWORD", LINE2(1));
            } else if (delay >= 1000 && delay < 2000) {
                clcd_putch(' ', LINE2(i));
                //clcd_print("ENTER PASSWORD", LINE1(1));
            } else {
                delay = 0;
            }




            if (key == MK_SW5) {
                clcd_putch('*', LINE2(i));

                enter[i++] = '5';
                pass[j++] = read_external_eeprom(pass_add++);

            } else if (key == MK_SW6) {
                clcd_putch('*', LINE2(i));

                enter[i++] = '6';
                pass[j++] = read_external_eeprom(pass_add++);
            }
        } else {
            enter[i] = '\0';
            pass[j] = '\0';
            pass_add = 0x00;
            //CLEAR_DISP_SCREEN;
            if (strcmp(pass, enter) == 0) {
                CLEAR_DISP_SCREEN;
                clcd_print("PASSWORD MATCHED", LINE2(0));
                i = j = 0;
                for (unsigned long int k = 900000; k--;);

                main_f = MENU;
                CLEAR_DISP_SCREEN;
                //while (1);
            } else {
                i = 0;
                CLEAR_DISP_SCREEN;
                if(dela++ < 1000)
                clcd_print("ATTEMPT FAILED", LINE2(0));
                attempt--;
                //for (unsigned long int k = 900000; k--;);
                CLEAR_DISP_SCREEN;
                clcd_putch('0' + attempt, LINE1(0));
                
                clcd_print("ATTEMPT LEFT", LINE2(2));
                for (unsigned long int k = 900000; k--;);




                //for (unsigned long int k = 900000; k--;);
                CLEAR_DISP_SCREEN;

                if (attempt == 0) {
                    init_timer0();
                }

            }
        }
    } else {
        clcd_print("USER BLOCKED", LINE1(2));
        clcd_print("wait for", LINE2(1));
        clcd_putch((sec % 10) + 48, LINE2(12));
        clcd_putch((sec / 10) % 10 + 48, LINE2(11));
        clcd_print("sec", LINE2(13));
        if (sec == 0) {
            attempt = 3;
            count0 = 0;
            sec = 60;
            main_f = PASSWORD;
            TMR0ON = 0;
            CLEAR_DISP_SCREEN;
        }
    }


    if (key == MK_SW6LO) {
        main_f = DASHBOARD;
        CLEAR_DISP_SCREEN;
    }


}


