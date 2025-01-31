#ifndef _SOUND_H_
#define _SOUND_H_

#define VOLUME_MIN 0
#define VOLUME_MAX 127

enum waveform_t {
    WAVEFORM_SINE = 0,
    WAVEFORM_SQUARE = 1,
    WAVEFORM_TRIANGLE = 2,
    WAVEFORM_SAWTOOTH = 3,
    WAVEFORM_NOISE = 4,
    WAVEFORM_VIC_NOISE = 5
};

void sound_play(enum waveform_t wave, int freq, int dur, int vol);

#endif