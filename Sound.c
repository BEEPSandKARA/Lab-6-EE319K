// Sound.c
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: BP Rimal and Kara Olson
// Date Created: 3/6/17 
// Last Modified: 1/17/2020 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "dac.h"
#include "../inc/tm4c123gh6pm.h"

// 4-bit 32-element sine wave
const unsigned short wave[32] = {
  8,9,11,12,13,14,14,15,15,15,14,
  14,13,12,11,9,8,7,5,4,3,2,
  2,1,1,1,2,2,3,4,5,7};
	uint16_t index_w;

// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none

void Sound_Init(void){
  //systick
	//flags, counters, indices, any global variables
	// start with quiet
	// also call DAC_init
	DAC_Init();
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_SYS_PRI3_R = ((NVIC_SYS_PRI3_R & 0x00FFFFFF) | (0x20000000));
	NVIC_ST_CTRL_R = 0x07;
	index_w = 0;
	
}
 

// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Play called again
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
void Sound_Play(uint32_t period){
			NVIC_ST_RELOAD_R = period;
			return;
			
}

void SysTick_Handler(void){
			DAC_Out(wave[index_w]);
			index_w = (index_w+1) % 32;
			GPIO_PORTF_DATA_R ^= 0x01;
			return;
	
/*
			DAC_Out(index_w);
			index_w = (index_w + 1) % 16;
			
	*/
}

