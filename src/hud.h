#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

class HUD {
public:
    HUD(sf::Vector2f &resolution, bool *paused);

    void update(float fps, int &score);

    void draw(sf::RenderWindow &window, bool paused);

    void timeReset() { time_remaining = 6.0f; }

private:
    sf::RectangleShape timebar;
    float              timebar_width;
    float              timebar_height;
    float              timebar_width_per_second;

    sf::Time           time_to_survive;
    float              time_remaining;

    sf::Vector2f       resolution;
    sf::Text           text_pause; 
    sf::Text           text_score;
    sf::Font           font;

    bool              *paused;

    void __initPauseMessage(const std::string &message);
    void __initScore();
    void __initTimeBar();

    void __updateTimeBar(float fps);
    void __updateScore(int &score);
};
