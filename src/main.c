/*
 ============================================================================
 Name        : RTTTLInterpreter.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "rtttl.h"
#include <unistd.h>


int main(void) {
	 Beep(523,500);
	puts("Running RTTTL test\n\a"); /* prints !!!Hello World!!! */
	while(1){
		vSoundProcess();
	};
	return EXIT_SUCCESS;
}

void vPlayNote(unsigned char note,unsigned char scale, unsigned char duration, unsigned char period){
	printf("%s note %d scale %d duration %d period %d\n",__FILE__,note,scale,duration,period);
}
void vPause(unsigned char duration, unsigned char period){
	printf("%s Pause duration %d period %d\n",__FILE__,duration,period);
}

void vSetBPM(unsigned int bpm){
	printf("%s Set BPM %d\n",__FILE__,bpm);
}
