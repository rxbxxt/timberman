#pragma once

#include <SFML/Audio.hpp>
#include <assert.h>

namespace tmb {

class Sound {
public:
    Sound();

    static void playOutOfTime();
    static void playChop();
    static void playRIP();

private:
    sf::SoundBuffer buffer_outoftime;
    sf::SoundBuffer buffer_chop;
    sf::SoundBuffer buffer_rip;

    sf::Sound       sound_outoftime;
    sf::Sound       sound_chop;
    sf::Sound       sound_rip;

    static tmb::Sound *instance;
};

} // namespace tmb

