#include <stdio.h>

#include "wav.h"

int main(int argc, char * argv[])
{
    WavHeader wavh = {};
    WavHeaderInit(&wavh);
    GenerateAudio(&wavh, "note.wav", 10);

}
