#include "hud.h"

HUD::HUD(sf::Vector2f &resolution, bool *paused) {
    this->resolution.x = resolution.x;
    this->resolution.y = resolution.y;
    this->paused = paused;

    font.loadFromFile("fonts/KOMIKAP_.ttf");

    __initPauseMessage("Press ENTER to start!");
    __initScore();
    __initTimeBar();
}

void HUD::update(float fps, float *score) {
    __updateScore(score);
    __updateTimeBar(fps);

    if (time_remaining < 6.0f) {
        __initPauseMessage("Press ENTER to continue!");
    }

    if (time_remaining <= 0.0f) {
        *paused = true;
        *score = 0;
        __initPauseMessage("Out of Time!!!");
        __timeReset();
    }
}

void HUD::draw(sf::RenderWindow &window) {
    window.draw(text_score);
    if (*paused) {
        window.draw(text_pause);
    }
    window.draw(timebar);
}

void HUD::__initPauseMessage(const std::string &message) {
    text_pause.setString(message);
    text_pause.setFont(font);
    text_pause.setCharacterSize(75);
    text_pause.setFillColor(sf::Color::White);
    sf::FloatRect rectangle = text_pause.getLocalBounds();
    text_pause.setOrigin(rectangle.left + rectangle.width  / 2.0f,
                         rectangle.top  + rectangle.height / 2.0f);
    text_pause.setPosition(resolution.x / 2.0f, resolution.y / 2.0f);
}

void HUD::__initScore() {
    text_score.setFont(font);
    text_score.setString("Score = 0");
    text_score.setCharacterSize(30);
    text_score.setFillColor(sf::Color::White);
    text_score.setPosition(
        20, resolution.y - text_score.getCharacterSize() - 20);
}

void HUD::__initTimeBar() {
    timebar_width = 400;
    timebar_height = 30;

    timebar.setSize(sf::Vector2f(timebar_width, timebar_height));
    timebar.setFillColor(sf::Color::Red);

    timebar.setPosition(resolution.x / 2.0f - timebar_width / 2,
                        resolution.y - timebar_height - 20);

    __timeReset();
    timebar_width_per_second = timebar_width / time_remaining; 
}

void HUD::__updateTimeBar(float fps) {
    time_remaining -= fps;
    timebar.setSize(sf::Vector2f(timebar_width_per_second * time_remaining,
                                 timebar_height));
}

void HUD::__updateScore(float *score) {
    std::stringstream ss;
    ss << "Score = " << (*score)++;
    text_score.setString(ss.str());
}
