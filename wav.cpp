#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "wav.h"

int WavHeaderInit(WavHeader * wavh)
{
    strncpy(wavh->riff, "RIFF", 4);
    strncpy(wavh->wave, "WAVE", 4);
    strncpy(wavh->fmt,  "fmt ", 4);
    strncpy(wavh->data, "data", 4);

    wavh->chunk_size        = 16;
    wavh->format_tag        = 1;
    wavh->num_chans         = 1;
    wavh->sample_rate       = 8000;
    wavh->bits_per_sample   = 16;
    wavh->bytes_per_sample  = (wavh->bits_per_sample / 8) * wavh->num_chans;
    wavh->bytes_per_second  = wavh->sample_rate * wavh->bytes_per_sample;

    return 0;

}

int GenerateAudio(WavHeader * wavh, const char * fname, const int duration)
{
    FILE * wavf = fopen(fname, "w");
    const int buffer_size = wavh->sample_rate * duration;
    wavh->dlength = buffer_size * wavh->bytes_per_sample;
    wavh->flength = wavh->dlength + HEADER_LENGTH;

    int16_t * buffer = (int16_t*) calloc(buffer_size, sizeof(int16_t));
    if (!buffer) return -1;

    for (int i = 0; i < buffer_size; i++)
    {
        int t   = i/5;
        int val = (((t >> 7) | t | (t >> 6)) * 10 + 4 * ((t & (t >> 13)) | (t >> 6))) & 0xFF;
        buffer[i] = ((val/127.0 - 1) / (1 + pow (15, 17.0*i/buffer_size - 15)) * 200);
    }


    fwrite(wavh, 1, sizeof(WavHeader), wavf);
    fwrite(buffer, sizeof(int16_t), buffer_size, wavf);

    free(buffer);

    return 0;
}

