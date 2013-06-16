/*
 * rtttl.c
 *
 *  Created on: Aug 1, 2012
 *      Author: dine
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "rtttl.h"
#include "tones.h"


#define STATE_DUR		1
#define STATE_NOTE		2
#define STATE_SCALE		3
#define STATE_SPECIAL	4
#define STATE_DELIM		5

const char RTTTL[] = TONES;
const char *pRTTTL = RTTTL;

unsigned char state = STATE_DUR;

unsigned char def_duration = 4, def_scale = 5, def_bpm = 1;

unsigned int catoi(const char *p) {
	unsigned char i = 0;
	for (i = 0; *p >= '0' && *p <= '9'; i = (i * 10) + (*p - '0'), p++)
		;
	return i;
}

void rtc(void) {
	if (*pRTTTL == 0){
		pRTTTL = RTTTL;
	}else{
		while ((*pRTTTL) != ',' && (*pRTTTL) != ':'){
			pRTTTL++;
		}
		pRTTTL++;
	}
	state = STATE_DUR;
}

void vRTTTLProcess(void) {

	unsigned char duration = def_duration, scale = def_scale, note = 0, period = 0;
	char pnote;

	lback: ;
	while (*pRTTTL == ' ') {
		pRTTTL++;
	}

	if (state == STATE_DUR) {
		if (!isalpha(*pRTTTL)) {
			duration = catoi(pRTTTL);
			pRTTTL += (duration > 9 ? 2 : 1);
		}
		state = STATE_NOTE;
		goto lback;

	} else if (state == STATE_NOTE) {
		pnote = *pRTTTL++;
		if ((*pRTTTL) == '=') {
			if (pnote == 'o') {
				pRTTTL++;
				scale = def_scale = catoi(pRTTTL);

			} else if (pnote == 'd') {
				pRTTTL++;
				duration = def_duration = catoi(pRTTTL);

			} else if (pnote == 'b') {
				pRTTTL++;
				def_bpm = catoi(pRTTTL);
				vSetBPM(def_bpm);
			}
			rtc();
			goto lback;
		}else if ((*pRTTTL) == '#') {
			note = 1;
			pRTTTL++;
		} else {
			note = 0;
		}

		if (pnote == 'a') {
			note += 9;
		} else if (pnote == 'b') {
			note = 11;
		} else if (pnote == 'c') {
			note += 0;
		} else if (pnote == 'd') {
			note += 2;
		} else if (pnote == 'e') {
			note = 4;
		} else if (pnote == 'f') {
			note += 5;
		} else if (pnote == 'g') {
			note += 7;
		} else if (pnote == 'p') {
			note = 100;
		} else {
			rtc();
			return;
		}

		state = STATE_SPECIAL;
		goto lback;

	} else if (state == STATE_SPECIAL) {
		if (*pRTTTL == '.') {
			period = 1;
			pRTTTL++;
		}
		state = STATE_SCALE;
		goto lback;
	} else if (state == STATE_SCALE) {
		if (isdigit(*pRTTTL)) {
			scale = catoi(pRTTTL);
		}

		if (note == 100) {
			vPause(duration, period);
		} else {
			vPlayNote(note, scale, duration, period);
		}
		rtc();

	}

}
