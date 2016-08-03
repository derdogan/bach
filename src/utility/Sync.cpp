#include "Sync.h"

int Sync::_bpm = DEFAULT_BPM;

void Sync::init() {
    Timer1.initialize();
    Timer1.attachInterrupt(Sync::timerCallback);

    updateTimer();
}

void Sync::timerCallback() {
    Midi::sendClock();
}

void Sync::updateTimer() {
    long clock = bpmToClock(_bpm);
    Timer1.setPeriod(clock);
}

long Sync::bpmToClock(int bpm) {
    long double n, clock;
    n = 1000000;
    n /= 24; // 24 ppqn

    clock = bpm;
    clock /= 60.0;
    clock = n/clock;

    return (long) clock;
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
