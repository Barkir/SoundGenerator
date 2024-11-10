#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

const int HEADER_LENGTH = 44;

struct WavHeader
{
    char riff[4];
    int32_t flength;
    char wave[4];
    char fmt[4];
    int32_t chunk_size;
    int16_t format_tag;
    int16_t num_chans;
    int32_t sample_rate;
    int32_t bytes_per_second;
    int16_t bytes_per_sample;
    int16_t bits_per_sample;
    char data[4];
    int32_t dlength;


};

int WavHeaderInit(WavHeader * wavh);
int GenerateAudio(WavHeader * wavh, const char * fname, const int duration);

#endif
