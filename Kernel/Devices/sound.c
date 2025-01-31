#include <stdio.h>
#include <Kernel/Devices/sound.h>

void sound_play(enum waveform_t wave, int freq, int dur, int vol) {
    if (vol < VOLUME_MIN) {
        vol = VOLUME_MIN;
    }

    if (vol > VOLUME_MAX) {
        vol = VOLUME_MAX;
    }

    printf("\e_S%d;%d;%d;%d$", wave, freq, dur, vol);
}
