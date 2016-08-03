#include "Memory.h"

bool Memory::validatePatternId(int id) {
	if (id > 0 && id < PATTERN_COUNT+1) { // pattern ids are between 1-15
		return true;
	} else {
		return false;
	}
}

int Memory::getPatternAddress(int id) {
	int adr;

	adr = id * PATTERN_LENGTH; // pattern offset
	adr -= PATTERN_LENGTH;
	adr += EEPROM_OFFSET_PATTERNS;

	return adr;
}

bool Memory::loadPattern(int id, byte* pattern) {
	if (! validatePatternId(id)) {
		id = DEFAULT_PATTERN_ID;
		//return false;
	}

	if (! Pattern::validate(pattern)) {
		return false;
	}

	int adr = getPatternAddress(id);

	for (int i=0; i<PATTERN_LENGTH; i++) {
		pattern[i] = EEPROM.read(adr + i);
	}

	return true;
}

bool Memory::savePattern(int id, byte* pattern) {
	if (! validatePatternId(id)) {
		return false;
	}

	if (! Pattern::validate(pattern)) {
		return false;
	}

	int adr = getPatternAddress(id);

	for (int i=0; i<PATTERN_LENGTH; i++) {
		EEPROM.update(adr + i, pattern[i]);
	}

	return true;
}

int Memory::loadActivePatternId() {
	int id;
	id = (int) EEPROM.read(EEPROM_OFFSET_GLOBAL_PATTERN);

	if (! validatePatternId(id)) {
		id = DEFAULT_PATTERN_ID;
	}

	return id;
}

bool Memory::saveActivePatternId(int id) {
	EEPROM.update(EEPROM_OFFSET_GLOBAL_PATTERN, id);

	return true;
}

int Memory::loadKeyboardMode() {
	int mode;
	mode = EEPROM.read(EEPROM_OFFSET_GLOBAL_KEYMODE);

	return mode;
}

bool Memory::saveKeyboardMode(int mode) {
	EEPROM.update(EEPROM_OFFSET_GLOBAL_KEYMODE, mode);

	return true;
}

int Memory::loadVelocity() {
	int velocity;
	velocity = EEPROM.read(EEPROM_OFFSET_GLOBAL_VELOCITY);

	if (velocity < 0 || velocity > 127) {
		velocity = 127;
	}

	return velocity;
}

bool Memory::saveVelocity(int velocity) {
	EEPROM.update(EEPROM_OFFSET_GLOBAL_VELOCITY, velocity);

	return true;
}

void Memory::clear() {
	for (int i=1; i<=EEPROM.length(); i++) {
		EEPROM.update(i, 0);
	}
}

void Memory::reset() {
	clear();

	saveActivePatternId(DEFAULT_PATTERN_ID);
	saveKeyboardMode(DEFAULT_KEYMODE);
	saveVelocity(DEFAULT_VELOCITY);

	resetPatterns();
}

void Memory::resetPatterns() {
	byte pattern[PATTERN_LENGTH];

	Pattern::clear(pattern);

	for (int i=1; i<=PATTERN_COUNT; i++) {
		savePattern(i, pattern);
	}
}

bool Memory::copyPattern(int from_id, int to_id) {
	if (! validatePatternId(from_id) || ! validatePatternId(to_id)) {
		return false;
	}

	byte pattern[PATTERN_LENGTH];

	if (! loadPattern(from_id, pattern)) {
		return false;
	}

	if (savePattern(to_id, pattern)) {
		return true;
	} else {
		return false;
	}
}

void Memory::dump() { // debug
	Serial.println("dumping EEPROM");

	for (int i=1; i<=EEPROM.length(); i++) {
		Serial.print(i);
		Serial.print("\t");
		Serial.println(EEPROM.read(i));
	}
}

bool Memory::dumpPattern(int id) { // debug
	if (! validatePatternId(id)) {
		return false;
	}

	int adr = getPatternAddress(id);

	Serial.print("dumping pattern ");
	Serial.print(id);
	Serial.println(" from EEPROM");

	for (int i=0; i<PATTERN_LENGTH; i++) {
		byte x = EEPROM.read(adr + i);

		Serial.print(adr + i);
		Serial.print("\t");
		Serial.println(x);
	}

	return true;
}
