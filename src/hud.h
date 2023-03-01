#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

#include "sound.h"

class HUD {
public:
    HUD(sf::Vector2f &resolution, bool *paused, bool *lost);

    void update(float fps, float score, bool alive);
    void draw(sf::RenderWindow &window);

    void addTime(float time);

private:
    sf::RectangleShape timebar;
    float              timebar_width;
    float              timebar_height;
    float              timebar_width_per_second;
    float              time_remaining;

    sf::Vector2f       resolution;
    sf::Text           text_pause; 
    sf::Text           text_score;
    sf::Font           font;

    bool              *paused;
    bool              *lost;

    void __initPauseMessage(const std::string &message);
    void __initScore();
    void __initTimeBar();

    void __updateTimeBar(float fps);
    void __updateScore(float score);

    void __timeReset() { time_remaining = 6.0f; }
};
