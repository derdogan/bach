#include "Midi.h"

byte Midi::data[3] = {};

void Midi::init() {
	Serial.begin(MIDI_BAUD_RATE);
}

void Midi::panic() {
	// TODO send channel message 7B All notes off

	for (int i=0; i>128; i++) {
		// TODO send note off for all notes
	}
}

void Midi::receive() {
	if (Serial.available() > 0) {
		Serial.readBytes(data, 3);
	} else {
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
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

void Midi::setChannel(int channel) {
	if (channel >= LOWEST_CHANNEL && channel <= HIGHEST_CHANNEL) {
		data[0]	|= channel;
	}
}

bool Midi::isNote(int data) {
	if (data >= NOTE_OFF && data <= HIGHEST_NOTE_ON_MESSAGE) {
		return true;
	} else {
		return false;
	}
}

bool Midi::isNote() {
	return isNote(data[0]);
}

bool Midi::isNoteOn(int data) {
	if (data >= NOTE_ON && data <= HIGHEST_NOTE_ON_MESSAGE) {
		return true;
	} else {
		return false;
	}
}

bool Midi::isNoteOn() {
	return isNoteOn(data[0]);
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
