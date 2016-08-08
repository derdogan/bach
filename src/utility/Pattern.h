/*
 * Patterns.h - Manage patterns containing MIDI notes.
 *
 * A pattern note consists only of the MIDI note value to save space.
 * One note is represented by one byte. As MIDI notes go from 0 to 127,
 * not the entire byte is needed. So the first bit of the note byte represents
 * the state of the note (on/off).
 *
 * See also: Notes.h
 *
 * Created by Deniz Erdogan, 27. July 2016
 */

#ifndef BACH_PATTERN_H
#define BACH_PATTERN_H

#include "Arduino.h"
#include "Memory.h"
#include "Notes.h"

#define PATTERN_LENGTH 		67 		// 64 bytes step notes + 2 bytes bpm + 1 byte velocity
#define DEFAULT_VELOCITY	127
#define DEFAULT_TEMPO		120

#define OFFSET_TEMPO		0
#define OFFSET_VELOCITY		2
#define OFFSET_NOTES		3

#define NOTE_MIN			0
#define NOTE_MAX			63

#define TEMPO_MIN			1
#define TEMPO_MAX			510

#define VELOCITY_MIN		0
#define VELOCITY_MAX		127

#define STEP_NOTES			4

class Pattern {
	private:
		Pattern() {}

	public:
		static bool validate(byte* pattern);
		static bool	clear(byte* pattern);
		static bool	dump(byte* pattern);

		static int  getVelocity(byte* pattern);
		static bool setVelocity(int velocity, byte* pattern);
		static int  sanitizeVelocity(int velocity);

		static int  getTempo(byte* pattern);
		static bool setTempo(int bpm, byte* pattern);

		static int  getNote(int offset, byte* pattern);
		static bool setNote(int offset, byte value, byte* pattern);

		static bool noteOn(int offset, int note, byte* pattern);
		static bool noteOff(int offset, int note, byte* pattern);

		static bool validNoteOffset(int offset);

		static bool getNotes(int step, byte* notes, byte* pattern);

		static bool isNoteMuted(int note);
		static bool turnNoteOn(int offset, byte* pattern);
		static bool turnNoteOff(int offset, byte* pattern);
};

#endif
