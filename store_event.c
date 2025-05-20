/*
 * File:   store_event.c
 * Author: nihal
 *
 * Created on 7 June, 2024, 2:52 PM
 */


#include <xc.h>
#include "CBB_main.h"

int event_count;
unsigned char str[15];
int *arr[10];
unsigned int event_add = 0x05;
unsigned int addr = 0x05;
char read[15];


extern char store[17];

void store_event() {
    
  
    if(event_count < 10)
    {
        event_count++;
        for(int i = 0 ; i < 15 ; i++)
        {
            write_external_eeprom(event_add + i , store[i]);
        }
        
        event_add = event_add + 15;
        
        /*for(int i = 0 ; i < 15 ; i++)
        {
            store[i] = read_external_eeprom(event_add+i);
        }
        store[15] = '\0';*/
        
        
       // clcd_print(store,LINE1(0));
        //for(unsigned long int j = 10000 ; j;);
        //for(unsigned long int j = 500000 ; j;);
        //for(unsigned long int j = 500000 ; j;);
        //for(unsigned long int j = 500000 ; j;);
        //for(unsigned long int j = 500000 ; j;);
           
    }
    else
    {
        event_add = 0x05;
        for(int i = 0 ; i < 9 ; i++)
        {
            for(int j = 0  ; j < 15 ; j++)
            {
                read[j] = read_external_eeprom(event_add + 15 + j);
            
                write_external_eeprom(event_add + j, read[j]);
            }
            event_add = event_add + 15;
            
        }
        for(int j = 0  ; j < 15 ; j++)
        {
           write_external_eeprom(event_add + j, store[j]);
            event_count = 10; 
        }
    }
    
    
}
/*void print()
{
    int event_add = 0x05, i = 10;
    while(i--)
    {
        for(int k = 0 ; k < 15 ; k++)
        {
            store[k] = read_external_eeprom(event_add + k);
        }
        store[15] = '\0';
        
        clcd_print(store,LINE1(0));
        for (unsigned long int k = 900000; k--;);
        //for (unsigned long int k = 900000; k--;);
        //for (unsigned long int k = 900000; k--;);
        //for (unsigned long int k = 900000; k--;);
        
        event_add = event_add + 15;
        
    }
}*/
