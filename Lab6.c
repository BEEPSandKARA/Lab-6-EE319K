// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 4-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: BP Rimal and Kara Olson
// Date Created: 3/6/17 
// Last Modified: 1/17/2020 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"
#include "Music.h"
/////////////
#include "DAC.h"
#include "texas.h"

//////////////

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
//void delay(void);		// testing
//uint16_t data = 0;   				// testing
extern uint32_t play;

note_t StarWarsThemeSong[110] = {
	//NOTES
{A0, q-g},
{Q, g},
{A0, q-g},
{Q, g},
{A0, q-g},
{Q, g},
{A0, q+g},
{Q, g},
{F0, e},
{C0, s},
{A0, q},
{Q, g},
{F0, e},
{C0, s},
{A0, h},
{E, q-g},
{Q, g},
{E, q-g},
{Q, g},
{E, q},
{F, e},
{C0, s},
{A0, q},
{Q, g},
{F0, e},
{C0, s},
{A0, h},
{Q, g},
{A, q},
{Q, g},
{A0, e+g},
{Q, g},
{A0, s},
{AF, e+g},
{G, s},
{Q, (g/2)},
{EF, s},
{D, s+g},
{EF, e},
{Q, e},
{A0, e+g},
{EF, q},
{D, e+g},
{DF, s+g},
{C0, s},
{B0, s},
{C0, s},
{Q, e},
{F0, e},
{AF0, q},
{F0, e+g},
{A0, s+g},
{C0, q},
{A0, e+g},
{C0, s},
{E, h},
{0,0}
};




int main(void){      
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
	Music_Init();
  // other initialization
																												// global flag for playing the song
	uint32_t hearbeat = 0;
//	uint8_t Button_Pressed = 0;													// Button_Pressed is a GLOBAL VARIABLE
	SYSCTL_RCGCGPIO_R |= 0x20;
	volatile uint16_t noop;
	noop = 69;
	GPIO_PORTF_DIR_R |= 0x02;
	GPIO_PORTF_DEN_R |= 0x02;
  EnableInterrupts();
  while(1){ 
		if(hearbeat == 0) GPIO_PORTF_DATA_R ^= 0x02;
		hearbeat = (hearbeat + 1) % 200000;
//		Button_Pressed = Piano_In();
		switch(Piano_In()){
			case 0x00:	
								Sound_Play(0);
								break;
			case 0x01: 
								Sound_Play(A);
								break;
			case 0x02:
								Sound_Play(B);
								break;
			case 0x04:
								Sound_Play(C);
								break;
			case 0x08:
								Sound_Play(D);
								break;	
			case 0x0C:
								Music_Play(StarWarsThemeSong);
								while(play){}
								break;
			default:
								break;
  }    
}
}
/////////////////////////////////testing///////////////////////////////////////////////////
/******************************************************************************
TESTING-TESTING-TESTING-TESTING-TESTING-TESTING-TESTING-TESTING-TESTING-TESTING-TESTING-TESTING-TESTING
*////////////////////////////////////////////////////////////////////////////////
/*
if(Piano_In() == 0x08){
			DAC_Out(data);
			data = (data+1)% 16;
			delay();
		}}}

void delay(void){
	for(int i = 0; i < 8000000; i++){
	}}
*/
///////////////////////////////////////////////////////////////////////////////
//oscilloscope testing

/*

void Delay1ms(int time);  	// blind wait
void LaunchPad_Init(void);
void delay(void);
// lab video Lab6_static
uint16_t data = 0;
uint16_t last;
int main(void){  
  TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);	// bus clock at 80 MHz
  LaunchPad_Init();
  DAC_Init(); // your lab 6 solution
  Piano_Init();
  Sound_Init();
  EnableInterrupts();
  while(1){ 
		switch(Piano_In()){
			case 0x00:
								Sound_Play(0);
								break;
			case 0x01: 
								Sound_Play(A);
								break;
			case 0x02:
								Sound_Play(B);
								break;
			case 0x04:
								Sound_Play(C);
								break;
			case 0x08:
								Sound_Play(D);
								break;	
			default:
								break;
  }    
}
}
*/


