// music.c
// Author: BP Rimal and Kara Olson
// Date created: 4/1/2020
//************************************************

// Timer0A.c
// Runs on LM4F120/TM4C123
// Use Timer0A in periodic mode to request interrupts at a particular
// period.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers"
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015
   Volume 1, Program 9.8

  "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2014
   Volume 2, Program 7.5, example 7.6

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
#include <stdint.h>
#include "..//inc//tm4c123gh6pm.h"
#include "Music.h"
#include "Sound.h"

uint32_t play;
uint8_t song_index;
note_t *ptsong;



// ***************** Timer0A_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq), 32 bits
// Outputs: none


long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value


void Timer0A_Init(void){long sr;
  sr = StartCritical(); 
	volatile int delay1;
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
	volatile int delay;
	delay = 69;
  TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
//  TIMER0_TAILR_R = period-1;    // 4) reload value
	TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
  NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
//TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
	EndCritical(sr);
}

void stop_song(void){

}

void Music_Init(){
		Timer0A_Init();
		song_index = 0;
}
void Music_Play(note_t song[]){
			ptsong = song;
			TIMER0_TAILR_R = 0x80; 			// random initialization
			TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A			
			}

			

	

void Timer0A_Handler(void){
	TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge timer0A timeout
	play = (ptsong[song_index].duration);
	if(play){ 												// check if the duration is 0; song array is null terminated
			Sound_Play(ptsong[song_index].pitch);
			TIMER0_TAILR_R = ptsong[song_index].duration;
			TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A	
			song_index++;
	}else{																// stop song
				TIMER0_CTL_R = 0x00;						// disable timer
				song_index = 0x00;							// reinitialize song_index
					}
	return;
	}
