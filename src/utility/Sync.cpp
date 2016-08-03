#include "Sync.h"

int Sync::_bpm = DEFAULT_BPM;

void Sync::init() {
    Timer1.attachInterrupt(Sync::timerCallback);
    updateTimer();
}

void Sync::timerCallback() {
    Midi::sendClock();
}

void Sync::updateTimer() {
    long clock = bpmToClock(_bpm);
    Timer1.initialize(clock);
}

long Sync::bpmToClock(int bpm) {
    long clock = (long) bpm;
    clock /= 120;
    clock /= 25;

    return clock;
}

bool Sync::changeTempo(int bpm) {
    if (bpm >= MIN_BPM && bpm <= MAX_BPM) {
        _bpm = bpm;

        updateTimer();

        return true;
    } else {
        return false;
    }
}
