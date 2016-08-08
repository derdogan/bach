/*
 * Sync.h - Synchronize the internal sequencer and external devices (through MIDI clock signals) via a BPM value
 *
 * Created by Deniz Erdogan, 3. August 2016
 */

#ifndef BACH_SYNC_H
#define BACH_SYNC_H

#include "Arduino.h"
#include "TimerOne.h"
#include "Midi.h"
#include "Sequencer.h"

#define MIN_BPM         10
#define MAX_BPM         510
#define DEFAULT_BPM     120

class Sync {
    private:
        Sync() {};

        int static _bpm;

    public:
        void static init();
        void static updateTimer();
        void static timerCallback();

        long static bpmToClock(int bpm);
        bool static changeTempo(int bpm);

        int static getTempo();
};

#endif
