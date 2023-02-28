#pragma once

#include <SFML/Graphics.hpp>
#include "random.h"

class TreeBranch {
public:
    TreeBranch(const std::string &texture_file);

    void update(int multiplier);
    void draw(sf::RenderWindow &window);

private:
    enum Position {
        RIGHT,
        LEFT,
        NONE
    };

    TreeBranch::Position position;

    sf::Texture  texture;
    sf::Sprite   sprite;

    void __setRandomPosition();

};
