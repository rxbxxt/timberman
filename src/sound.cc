#include "sound.h"

namespace tmb {

Sound *Sound::instance = nullptr;

Sound::Sound() {
    assert(instance == nullptr);
    instance = this;

    buffer_outoftime.loadFromFile("sound/out_of_time.wav");
    buffer_chop.loadFromFile("sound/chop.wav");
    buffer_rip.loadFromFile("sound/death.wav");

    sound_outoftime.setBuffer(buffer_outoftime);
    sound_chop.setBuffer(buffer_chop);
    sound_rip.setBuffer(buffer_rip);
}

void Sound::playOutOfTime() {
    instance->sound_outoftime.play();
}

void Sound::playChop() {
    instance->sound_chop.play();
}

void Sound::playRIP() {
    instance->sound_rip.play();
}

} // namespace tmb
