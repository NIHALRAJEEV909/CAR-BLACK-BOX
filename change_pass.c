/*
 * File:   change_pass.c
 * Author: nihal
 *
 * Created on 7 June, 2024, 10:45 PM
 */


#include <xc.h>
#include "CBB_main.h"

char new_pass[5];
char re_pass[5];

extern int pass_add = 0x00;

extern char main_f;

unsigned long int delay = 0, delay1 = 0, delay2 = 0, delay3 = 0, delay4 = 0;
static int i, j;

void change_pass(char key) {


    if (i < 4) {
        clcd_print("NEW PASSWORD", LINE1(0));



        if (delay++ < 1000) {
            clcd_putch('_', LINE2(i));

        } else if (delay >= 1000 && delay < 2000) {
            clcd_putch(' ', LINE2(i));

        } else if (delay == 2000) {
            delay = 0;
        }

        if (key == MK_SW5) {

            clcd_putch('*', LINE2(i));
            new_pass[i++] = '5';

        } else if (key == MK_SW6) {
            clcd_putch('*', LINE2(i));
            new_pass[i++] = '6';

        }

    } else if (i == 4) {
        new_pass[4] = '\0';
        i++;
        CLEAR_DISP_SCREEN;
        //clcd_print("", LINE2(0));

    }

    if (i == 5 && j < 4) {




        //if (delay3++ < 20000) {
        clcd_print("RE-ENTER PASS", LINE1(0));
        //}
        //for (unsigned long int k = 900000; k--;);

        //clcd_print("RE-ENTER PASS", LINE2(0));

        if (delay1++ < 1000) {
            clcd_putch('_', LINE2(j));

        } else if (delay1 >= 1000 && delay1 < 2000) {
            clcd_putch(' ', LINE2(j));

        } else if (delay1 == 2000) {
            delay1 = 0;
        }

        if (key == MK_SW5) {
            clcd_putch('*', LINE2(j));
            re_pass[j++] = '5';

        } else if (key == MK_SW6) {
            clcd_putch('*', LINE2(j));
            re_pass[j++] = '6';

        }

    } else if (j == 4) {
        re_pass[4] = '\0';
        j++;
        CLEAR_DISP_SCREEN;
    }


    if (i == 5 && j == 5) {

        if (strcmp(new_pass, re_pass) == 0) {
            //CLEAR_DISP_SCREEN;
            //delay2 = 0;
            //for (unsigned long int k = 90000; k--;);


            if (delay2++ == 0) {
                for (int r = 0; r < 4; r++) 
                {
                    write_external_eeprom(pass_add, new_pass[r]);
                    pass_add++;
                 }
                pass_add = 0x00;

            } else if (delay2 < 2000) {
                clcd_print("PASS UPDATED", LINE1(0));
            } else {
                i = 0;
                j = 0;
                main_f = MENU;
                delay2 = 0;
            }



        } else {
            //CLEAR_DISP_SCREEN;
            if (delay4++ < 20000) {

                clcd_print("PASS NOT UPDATED", LINE1(0));
            }
            else
            {
            delay4 = 0;
            //for (unsigned long int k = 900000; k--;);

            i = 0;
            j = 0;
            main_f = MENU;
            }

        }

    }

}