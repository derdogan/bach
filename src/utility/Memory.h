/*
 * Patterns.h - Manage user data in the persistent memory.
 *
 * The Arduino Uno got an EEPROM with a size of 1024 bytes.
 *
 * With this class you can store and load various user data from/to the memory, like:
 * - global settings
 * - the pattern chain
 * - individual patterns
 *
 * Created by Deniz Erdogan, 27. July 2016
 */

#ifndef BACH_MEMORY_H
#define BACH_MEMORY_H

#include "Arduino.h"
#include "EEPROM.h"

#include "Pattern.h"
#include "Notes.h"

#define PATTERN_COUNT  					15 // only 15 pattern slots due to memory limitation on the Arduino Uno

#define EEPROM_OFFSET_GLOBAL_PATTERN	1
#define EEPROM_OFFSET_GLOBAL_VELOCITY	2 // TODO misc bitmask
#define EEPROM_OFFSET_GLOBAL_KEYMODE	3

#define EEPROM_OFFSET_CHAIN  			4 	// 16 	bytes
#define EEPROM_OFFSET_PATTERNS  		20	// 1005	bytes
											// 1024 bytes total

#define KEYMODE_CHROMATIC 				1
#define KEYMODE_MAPPED					2

#define DEFAULT_KEYMODE 				KEYMODE_MAPPED
#define DEFAULT_PATTERN_ID				1

class Memory {
	private:
		Memory() {}

	public:
		static bool  validatePatternId(int id);

		static int   getPatternAddress(int id);

		static int	 loadActivePatternId();
		static bool	 saveActivePatternId(int id);

		static int	 loadKeyboardMode();
		static bool	 saveKeyboardMode(int mode);

		static int	 loadVelocity();
		static bool	 saveVelocity(int velocity);

		static bool  loadPattern(int id, byte* pattern);
		static bool  savePattern(int id, byte* pattern);
		static bool  copyPattern(int from_id, int to_id);
		static void	 resetPatterns();

		static bool  dumpPattern(int id);

		static void  clear();
		static void  reset();
		static void  dump();
};

#endif
