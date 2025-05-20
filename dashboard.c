/*
 * File:   dashboard.c
 * Author: nihal
 *
 * Created on 29 May, 2024, 8:26 AM
 */


#include <xc.h>
#include <stdio.h>
#include "CBB_main.h"
#include "CBB_adc.h"
#include "CBB_clcd.h"
#include "CBB_matrix_keypad.h"
#include "CBB_i2c.h"
#include "CBB_ds1307.h"
#include "CBB_isr.h"

unsigned char time[9];
unsigned char clock_reg[9];
unsigned int speed;
int real_speed;

extern char main_f;

char store[17];
void dashboard(char key) {
    
    get_time();
    display_time();
    
    clcd_print("  TIME    EV SP ", LINE1(0));
    speed = read_adc(CHANNEL4);
    //real_speed = speed / 10.23;
    
    
    
    if(key == MK_SW1)
    {
        event_index = 8;
    }
    else if(key == MK_SW2)
    {
        if(event_index < 7)
        {
            ++event_index;
        }
        if(event_index == 8)
        {
            event_index = 1;
        }
    }
    else if(key == MK_SW3)
    {
        if(event_index == 8)
        {
            event_index = 1;
        }
        if(event_index > 1)
        {
            --event_index;
        }
    } 
    
    clcd_print(event_status[event_index],LINE2(10));
    
    if(event_index == 2)
    {
        real_speed = speed / 40.92;
        clcd_putch(real_speed % 10 + '0',LINE2(14));
        clcd_putch(real_speed / 10 % 10 + '0',LINE2(13));
      
    }
    else if(event_index == 3)
    {
        real_speed = speed / 40.92 ;
        clcd_putch(real_speed % 10 + '0',LINE2(14));
        clcd_putch(real_speed / 10 % 10 + '0',LINE2(13));
      
    }
    else if(event_index == 4)
    {
        real_speed = speed / 25.575;
        clcd_putch(real_speed % 10 + '0',LINE2(14));
        clcd_putch(real_speed / 10 % 10 + '0',LINE2(13));
      
    }
    else if(event_index == 5)
    {
        real_speed = speed / 17.05;
        clcd_putch(real_speed % 10 + '0',LINE2(14));
        clcd_putch(real_speed / 10 % 10 + '0',LINE2(13));
      
    }
    else if(event_index == 6)
    {
        real_speed = speed / 12.7875;
        clcd_putch(real_speed % 10 + '0',LINE2(14));
        clcd_putch(real_speed / 10 % 10 + '0',LINE2(13));
      
    }
    else if(event_index == 7)
    {
        real_speed = speed / 10.333333333333;
        clcd_putch(real_speed % 10 + '0',LINE2(14));
        clcd_putch(real_speed / 10 % 10 + '0',LINE2(13));
      
    }
    else if(event_index == 0 || event_index == 1 || event_index == 8)
    {
        real_speed = 0;
        clcd_putch(real_speed %10 + '0',LINE2(14));
        clcd_putch(real_speed / 10 % 10 + '0',LINE2(13));
      
    }
    
    
    
    if(key == MK_SW5)
    {
        main_f = PASSWORD;
    }
    
    if(main_f == PASSWORD)
    {
        CLEAR_DISP_SCREEN;
    }
    
  
    sprintf(store,"%s  %s %d",time,event_status[event_index],real_speed);
    
    //store_event(store);
    return;
}

void get_time(void)
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
}
void display_time(void)
{
	clcd_print(time, LINE2(0));
}
