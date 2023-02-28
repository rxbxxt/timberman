#pragma once

#include <SFML/Graphics.hpp>

class Timber {
public:
    enum Position {
        RIGHT,
        LEFT
    };

    Timber(const std::string &timber_texture_file,
           const std::string &timber_rip_texture_file,
           const std::string &timber_axe_texture_file);

    void update(float *score);
    void draw(sf::RenderWindow &window);

    void setPosition(Timber::Position position) {
        this->position = position;
    }

private:

    Timber::Position position;

    sf::Texture  timber_texture;
    sf::Sprite   timber_sprite;
    sf::Texture  axe_texture;
    sf::Sprite   axe_sprite;
    sf::Texture  rip_texture;
    sf::Sprite   rip_sprite;
};