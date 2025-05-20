#ifndef MAIN_H
#define MAIN_H

/* Inclusion of header files */
#include <xc.h> 
#if 0
#include "adc.h"
#include "clcd.h"
#include "eeprom.h"
#include "matrix_keypad.h"
#include "ds1307.h"
#include "i2c.h"
#endif


#include "CBB_adc.h"
#include "CBB_clcd.h"
#include "CBB_matrix_keypad.h"
#include "CBB_i2c.h"
//#include "CBB_ds1307.h"
#include "CBB_isr.h"
//#include "ext_eeprom.h"
#include "CBB__uart.h"

#define DASHBOARD               0
#define PASSWORD                1
#define MENU                    2
#define MENU_ENTER              3
#define VIEWLOG                 0
#define DOWNLOADLOG             1
#define CLEARLOG                2
#define SETTIME                 3
#define CHANGEPASS              4

void dashboard(char key);
void store_event(); /* Pass required parameters */
void password(char key);
void menu(char key);
void view_log(char key);
void download_log();
void clear_log(char key);
void settime(char key);
void change_pass(char key);

void display_time(void);
void get_time(void);

static char *event_status[] = {"ON","GN","GR","G1","G2","G3","G4","G5","C "};
int event_index = 0;

int event_store;

static char *menu_screen[] = {"VIEW LOG      ","DOWNLOAD LOG   ","CLEAR LOG     ","SET TIME          ","CHANGE PASS    "};
//int menu_index = 0;

void write_external_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);

void store_event();

//char store[17];

//void print(char store[]);

void print();
//void set_get_time();


#endif