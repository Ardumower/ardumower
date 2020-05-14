#ifndef BUZZER_H
#define BUZZER_H

#include <inttypes.h>

enum SoundSelect {
    SND_READY,
    SND_PROGRESS,
    SND_OVERCURRENT,
    SND_TILT,
    SND_PERIMETER_TIMEOUT
};

class Buzzer
{
public:
    void begin();
    void sound(SoundSelect idx, bool async = true);
    void run();
    void tone(uint16_t freq);
    void noTone();

protected:
    SoundSelect soundIdx;
    int toneIdx;
    unsigned long nextToneTime;
};

extern Buzzer buzzer;

#endif
