#include "Pattern.h"

bool Pattern::validate(byte* pattern) {
	return true;
	
	// TODO; sizeof doesnt work as expected
	Serial.print("pattern size\t");
	Serial.println(PATTERN_LENGTH);
	
	Serial.print("actual size\t");
	Serial.println(sizeof(pattern));
	
	
	if (sizeof(pattern) == PATTERN_LENGTH) {
		return true;
	} else {
		return false;
	}
}

bool Pattern::clear(byte* pattern) {
	if (! validate(pattern))
		return false;
	
	setTempo(DEFAULT_TEMPO, pattern);
	setVelocity(DEFAULT_VELOCITY, pattern);
		
	for (int i=OFFSET_NOTES; i<PATTERN_LENGTH; i++) {
		pattern[i] = NOTE_BLANK;
	}
	
	return true;
}

int Pattern::getTempo(byte* pattern) {
	int bpm;
	byte a, b;
	
	a = pattern[OFFSET_TEMPO];
	b = pattern[OFFSET_TEMPO+1];
	
	bpm = (int) a;
		
	if (b > 0) {
		bpm += (int) b;
	}
	
	return bpm;
}

bool Pattern::setTempo(int bpm, byte* pattern) {
	byte a, b;
	
	if (bpm < TEMPO_MIN) {
		bpm = TEMPO_MIN;
	}
		
	if (bpm > TEMPO_MAX) {
		bpm = TEMPO_MAX;
	}
	
	if (bpm > 255) {
		a = 255;
		b = bpm - 255;
	} else {
		a = bpm;
		b = 0;
	}
	
	pattern[OFFSET_TEMPO]	= a;
	pattern[OFFSET_TEMPO+1]	= b;
	
	return true;
}

int Pattern::getVelocity(byte* pattern) {
	int velocity;
	
	velocity = pattern[OFFSET_VELOCITY];
	velocity = sanitizeVelocity(velocity);
	
	return velocity;
}

int Pattern::sanitizeVelocity(int velocity) {
	if (velocity < VELOCITY_MIN) {
		velocity = VELOCITY_MIN;
	}
	
	if (velocity > VELOCITY_MAX) {
		velocity = VELOCITY_MAX;
	}
	
	return velocity;
}

bool Pattern::setVelocity(int velocity, byte* pattern) {
	byte v;
	
	v = sanitizeVelocity(velocity);
	
	pattern[OFFSET_VELOCITY] = v;
	
	return true;
}

bool Pattern::validNoteOffset(int offset) {
	if (offset >= NOTE_MIN && offset <= NOTE_MAX) {
		return true;
	} else {
		return false;
	}
}

int Pattern::getNote(int offset, byte* pattern) {
	if (! validNoteOffset(offset)) {
		return 0;
	}
	
	offset += OFFSET_NOTES;
	
	int note = pattern[offset];
	
	return note;
}

bool Pattern::setNote(int offset, byte value, byte* pattern) {
	if (! validNoteOffset(offset)) {
		return false;
	}
	
	offset += OFFSET_NOTES;
	
	pattern[offset] = value;
		
	return true;
}

bool Pattern::noteOn(int offset, int note, byte* pattern) {
	byte value;
	
	value = 128;
	value |= note;
	
	return setNote(offset, value, pattern);
}

bool Pattern::noteOff(int offset, int note, byte* pattern) {
	byte value;
	
	value = 0;
	value |= note;
	
	return setNote(offset, value, pattern);
}

bool Pattern::getNotes(int step, byte* notes, byte* pattern) {
	// TODO validate step
	
	for (int i=0; i<STEP_NOTES; i++) {
		int offset = step;
		offset += i;
		
		notes[i] = Pattern::getNote(offset, pattern);
	}
	
	return true;
}

bool Pattern::dump(byte* pattern) { // debug
	if (! validate(pattern)) {
		Serial.println("ERROR Pattern::dump: validate pattern failed");
		return false;
	}
	
	Serial.println("dumping pattern from SRAM");
	for (int i=0; i<PATTERN_LENGTH; i++) {
		Serial.print(i);
		Serial.print("\t");
		Serial.println(pattern[i]);
	}
	
	return true;
}
