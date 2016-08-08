#ifndef H_BACH_SEQUENCER
#define H_BACH_SEQUENCER

#include "Arduino.h"
#include "TimerOne.h"
#include "Midi.h"
#include "Sync.h"
#include "Pattern.h"

#define SEQ_STEPS           16

#define SEQ_CLOCK_START     0
#define SEQ_CLOCK_END       SEQ_STEPS

class Sequencer {
    private:
        Sequencer() {}

        int static  _clock;
        bool static _playing;

        int static _channel;
        int static _velocity;

        int static _noteModifier;

        int static  _step;
        byte static _stepNotes[STEP_NOTES];
        byte static _oldStepNotes[STEP_NOTES];

    public:
        byte static _pattern[PATTERN_LENGTH];

        void static tick();
        void static start();
        void static stop();

        void static triggerStep();

        bool static loadPattern(int id);

        int static getVelocity();
        void static setVelocity(int velocity);

        int static getNoteModifier();
        void static setNoteModifier(int modifier);

        int static getStep();
};

#endif
