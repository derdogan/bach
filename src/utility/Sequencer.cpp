#include "Sequencer.h"

int Sequencer::_clock = SEQ_CLOCK_START;
bool Sequencer::_playing = false;

int Sequencer::_step = 0;
int Sequencer::_channel = 0;
int Sequencer::_velocity = 127;

byte Sequencer::_pattern[PATTERN_LENGTH] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte Sequencer::_stepNotes[STEP_NOTES] = {0, 0, 0, 0};
byte Sequencer::_oldStepNotes[STEP_NOTES] = {0, 0, 0, 0};

void Sequencer::tick() {
    if (_clock < SEQ_CLOCK_END) {
        _clock++;
    } else {
        _clock = SEQ_CLOCK_START;
        triggerStep();
    }
}

void Sequencer::start() {
    _playing = true;
}

void Sequencer::stop() {
    _playing = false;
}

void Sequencer::triggerStep() {
    Pattern::getNotes(_step, _stepNotes, _pattern);

    for (int i=0; i<STEP_NOTES; i++) {
        if (_stepNotes[i] != _oldStepNotes[i]) {
            Midi::noteOn(_stepNotes[i], _velocity, _channel);
        } else {
            // TODO
        }
    }
}

bool Sequencer::loadPattern(int id) {
    if (Memory::loadPattern(id, _pattern)) {
        _velocity = Pattern::getVelocity(_pattern);
    }

    return false;
}
