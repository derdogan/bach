#include "Sequencer.h"

int Sequencer::_clock = SEQ_CLOCK_START;
bool Sequencer::_playing = false;

int Sequencer::_step = 0;
int Sequencer::_channel = 0;
int Sequencer::_velocity = 127;
int Sequencer::_noteModifier = 0;

byte Sequencer::_pattern[PATTERN_LENGTH]    = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte Sequencer::_stepNotes[STEP_NOTES]      = {0, 0, 0, 0};
byte Sequencer::_oldStepNotes[STEP_NOTES]   = {0, 0, 0, 0};

void Sequencer::tick() {
    // TODO real sync to MIDI clocj
    if (_clock < 11) {
        _clock++;
    } else {
        _clock = SEQ_CLOCK_START;

        if (_playing) {
            triggerStep();
        }
    }
}

void Sequencer::start() {
    _playing = true;
}

void Sequencer::stop() {
    _playing = false;
}

void Sequencer::triggerStep() {
    for (int i=0; i<STEP_NOTES; i++) {
        Midi::noteOff(_stepNotes[i], _velocity, _channel);
    }

    Pattern::getNotes(_step, _stepNotes, _pattern);

    for (int i=0; i<STEP_NOTES; i++) {
        if (! Pattern::isNoteMuted(_stepNotes[i])) {
            int note = _stepNotes[i] + _noteModifier;
            Midi::noteOn(note, _velocity, _channel);
        }
    }

    _step++;

    if (_step >= SEQ_STEPS) {
        _step = 0;
    }
}

bool Sequencer::loadPattern(int id) {
    if (Memory::loadPattern(id, _pattern)) {
        _velocity = Pattern::getVelocity(_pattern);

        int bpm = Pattern::getTempo(_pattern);
        Sync::changeTempo(bpm);

        return true;
    }

    return false;
}

int Sequencer::getVelocity() {
    return _velocity;
}

void Sequencer::setVelocity(int velocity) {
    _velocity = velocity;
}

int Sequencer::getNoteModifier() {
    return _noteModifier;
}

void Sequencer::setNoteModifier(int modifier) {
    _noteModifier = modifier;
}

int Sequencer::getStep() {
    return _step;
}
