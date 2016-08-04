/*
 * Midi.h - Handle MIDI I/O.
 *
 * Created by Deniz Erdogan, 1. August 2016
 */

#ifndef BACH_MIDI_H
#define BACH_MIDI_H

#include "Arduino.h"
#include "Notes.h"

#define MIDI_BAUD_RATE				31250

// channel voice messages
#define NOTE_OFF					0x80
#define NOTE_ON						0x90
#define AFTERTOUCH					0xA0
#define CONTROL_CHANGE		 		0xB0
#define PROGRAM_CHANGE				0xC0
#define CHANNEL_PRESSURE			0xD0
#define PITCH_BEND					0xE0

#define SYSEX_START					0xF0
#define SYSEX_STOP					0xF7

// channel mode messages
#define RESET_ALL					0x79
#define LOCAL_CONTROL				0x7A
#define ALL_NOTES_OFF				0x7B
#define OMNI_MODE_OFF				0x7C
#define OMNI_MODE_ON				0x7D
#define MONO_MODE_ON				0x7E
#define POLY_MODE_ON				0x7F

// system real-time messages
#define TIMING_CLOCK				0xF8
#define START_SEQUENCE				0xFA
#define CONTINUE_SEQUENCE			0xFB
#define STOP_SEQUENCE				0xFC
#define ACTIVE_SENSING				0xFE
#define SYSTEM_RESET				0xFF

// system common messages
#define TIMING_CODE					0xF1
#define SONG_POSITION				0xF2
#define SONG_SELECT					0xF3
#define TUNE_REQUEST				0xF6

#define LOWEST_MODE_MESSAGE 		0x79
#define HIGHEST_MODE_MESSAGE 		0x7F
#define LOWEST_VOICE_MESSAGE 		0x80
#define HIGHEST_VOICE_MESSAGE 		0xEF
#define LOWEST_REALTIME_MESSAGE 	0xF8
#define HIGHEST_REALTIME_MESSAGE 	0xFF

#define LOWEST_CHANNEL				0
#define HIGHEST_CHANNEL				15

#define DEFAULT_CHANNEL				0

class Midi {
	private:
		Midi() {}

	public:
		byte static data[3];

		void static init();

		int static read();
		void static write(int output);

		void static sendMessage(byte* message);

		void static receive();
		void static send();

		bool static isNote(int data);
		bool static isNote();

		bool static isNoteOn(int data);
		bool static isNoteOn();

		bool static isNoteOff(int data);
		bool static isNoteOff();

		bool static isPitchBend(int data);
		bool static isPitchBend();

		bool static setChannel(int channel);

		int static getChannel();
		int static getNote();

		void static sendCC(int parameter, int value, int channel);

		void static sendStatusMessage(int status);
		void static sendClock();
		void static sendStartSequence();
		void static sendContinueSequence();
		void static sendStopSequence();
		void static sendActiveSensing();
		void static sendSystemReset();

		void static start();
		void static stop();
		
		void static discard();
		void static panic();
};

#endif
