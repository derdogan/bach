#include "Notes.h"

int Notes::getRootNote(int note) {
    int octave = note/12;
    int sub = 12*octave;
    int root = note - sub;

    return root;
}
