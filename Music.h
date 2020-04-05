
// music.h
#include <stdint.h>
#include "sound.h"
// timer0A is 32 bits
#ifndef MUSIC_H
#define MUSIC_H

#define bus 80000000
//cut time is quarter note is 250 ms
#define q (bus) //quarter note
#define h (q*2)	//half note
#define w (q*4)	// whole note
#define g (q/10)	// gap note
#define e	(q/2)	// eigth note
#define s	(q/4)	//sixteenth note

struct note{
		uint32_t pitch;
		uint32_t duration;
};
typedef const struct note note_t;



void Music_Init(void);
void Music_Play(note_t song[]);

#endif

