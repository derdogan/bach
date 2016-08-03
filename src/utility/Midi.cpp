#include "Midi.h"

byte Midi::data[3] = {};

void Midi::init() {
	Serial.begin(MIDI_BAUD_RATE);
}

void Midi::discard() {
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
}

void Midi::panic() {
	// TODO testing
	for (int i=0; i<HIGHEST_CHANNEL; i++) {
		int status = ALL_NOTES_OFF | i;
		sendStatusMessage(status);
	}
}

void Midi::receive() {
	if (Serial.available() > 0) {
		Serial.readBytes(data, 3);
	} else {
		discard();
	}
}

void Midi::sendMessage(byte* message) {
	for (int i=0; i<3; i++) {
		Serial.write(message[i]);
	}
}

void Midi::send() {
	if (data[0] > 0) {
		sendMessage(data);
	}
}

bool Midi::setChannel(int channel) {
	if (channel >= LOWEST_CHANNEL && channel <= HIGHEST_CHANNEL) {
		data[0] &= 0xF0;
		data[0]	|= channel;

		return true;
	} else {
		return false;
	}
}

int Midi::getChannel() {
	int channel = data[0];
	channel &= 0xF;

	return channel;
}

bool Midi::isNote(int data) {
	if (data >= NOTE_OFF && data <= (NOTE_ON | 0x0F)) {
		return true;
	} else {
		return false;
	}
}

bool Midi::isNote() {
	return isNote(data[0]);
}

bool Midi::isNoteOn(int data) {
	if (data >= NOTE_ON && data <= (NOTE_ON | 0x0F)) {
		return true;
	} else {
		return false;
	}
}

bool Midi::isNoteOn() {
	return isNoteOn(data[0]);
}

bool Midi::isNoteOff(int data) {
	if (data >= NOTE_OFF && data <= (NOTE_OFF | 0x0F)) {
		return true;
	} else {
		return false;
	}
}

bool Midi::isNoteOff() {
	return isNoteOff(data[0]);
}

bool Midi::isPitchBend(int data) {
	if (data >= PITCH_BEND && data <= (PITCH_BEND | 0x0F)) {
		return true;
	} else {
		return false;
	}
}

bool Midi::isPitchBend() {
	return isPitchBend(data[0]);
}

int Midi::getNote() {
	return data[1];
}

void Midi::sendCC(int parameter, int value, int channel=DEFAULT_CHANNEL) {
	byte message[3];

	message[0] = CONTROL_CHANGE;
	message[0] |= channel;

	message[1] = parameter;
	message[2] = value;

	sendMessage(message);
}

void Midi::sendStatusMessage(int status) {
	byte message[3];

	message[0] = status;

	sendMessage(message);
}

void Midi::sendClock() {
	sendStatusMessage(TIMING_CLOCK);
}

void Midi::sendStartSequence() {
	sendStatusMessage(START_SEQUENCE);
}

void Midi::sendContinueSequence() {
	sendStatusMessage(CONTINUE_SEQUENCE);
}

void Midi::sendStopSequence() {
	sendStatusMessage(STOP_SEQUENCE);
}

void Midi::sendActiveSensing() {
	sendStatusMessage(ACTIVE_SENSING);
}

void Midi::sendSystemReset() {
	sendStatusMessage(SYSTEM_RESET);
}
