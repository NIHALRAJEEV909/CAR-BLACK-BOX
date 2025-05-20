/*
 * File:   menu.c
 * Author: nihal
 *
 * Created on 6 June, 2024, 10:20 PM
 */


#include <xc.h>
#include "CBB_main.h"
//#include "CBB_ds1307.h"

static int count;
extern char main_f, menu_f;
static int flag, m_index;
extern unsigned char clock_reg[3],time[9];
unsigned char h = 0 , m = 0, s = 0;

void menu(char key) {


    if (key == MK_SW6 && count != 4) {
        count++;
        if (flag == 1)
            m_index++;
        //clcd_print("ENTER PASSWORD", LINE2(2));
        flag = 1;
    } else if (key == MK_SW5 && count != 0) {
        count--;
        if (flag == 3) {
            m_index--;
        }
        flag = 3;
    }

    if (count == 0 || flag == 3) {
        clcd_print("=>", LINE1(0));
        clcd_print("  ", LINE2(0));
    } else {
        clcd_print("  ", LINE1(0));
        clcd_print("=>", LINE2(0));
    }

    clcd_print(menu_screen[m_index], LINE1(2));
    clcd_print(menu_screen[m_index + 1], LINE2(2));



    if (key == MK_SW5LO) {

        main_f = MENU_ENTER;
        switch (count) {
            case 0:
                CLEAR_DISP_SCREEN;
                menu_f = VIEWLOG;
                break;
            case 1:
                CLEAR_DISP_SCREEN;
                menu_f = DOWNLOADLOG;
                break;
            case 2:
                CLEAR_DISP_SCREEN;
                menu_f = CLEARLOG;
                break;
            case 3:
                CLEAR_DISP_SCREEN;
                menu_f = SETTIME;
                //set_get_time();
                break;
            case 4:
                CLEAR_DISP_SCREEN;
                menu_f = CHANGEPASS;
                break;
        }
    }
   if (key == MK_SW6LO) {
        main_f = DASHBOARD;
        CLEAR_DISP_SCREEN;
    }

    
    


}

/*void set_get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
    
    h = (10 * (time[0] - 48)) + time[1] - 48;
    m = (10 * (time[3] - 48)) + time[4] - 48;
    s = (10 * (time[6] - 48)) + time[7] - 48;
}*/
