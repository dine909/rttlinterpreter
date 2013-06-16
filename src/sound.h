/*
 * sound.h
 *
 *  Created on: Aug 1, 2012
 *      Author: dine
 */

#ifndef SOUND_H_
#define SOUND_H_

void vSoundProcess(void);
void vPlayNote(unsigned char note,unsigned char scale, unsigned char duration, unsigned char period);
void vPause(unsigned char duration, unsigned char period);
void vSetBPM(unsigned int bpm);

#endif /* SOUND_H_ */
