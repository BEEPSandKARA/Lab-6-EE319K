// music.h
#include <stdint.h>
#include "sound.h"
// timer0A is 32 bits
#define bus 80000000
//cut time is quarter note is 250 ms
#define q (bus/4)
#define h (q*2)
#define w (q*4)
#define g (q/10)

struct note{
		uint16_t pitch;
		uint32_t duration;
};
typedef const struct note note_t;

note_t StarWarsThemeSong[20]{
	//notes
};

void Music_Init(void);
void Music_Play(note_t song[]);
