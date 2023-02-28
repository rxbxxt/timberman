#pragma once

#include <SFML/Graphics.hpp>
#include "random.h"

class TreeBranch {
public:
    enum Position {
        RIGHT,
        LEFT,
        NONE
    };

    TreeBranch(const std::string &texture_file, int multiplier);

    void update();
    void draw(sf::RenderWindow &window);

    void setPosition(TreeBranch::Position position);

    auto getPosition() const { return position; }

private:
    TreeBranch::Position position;
    int multiplier;

    sf::Texture  texture;
    sf::Sprite   sprite;

    void __setRandomPosition();
    void __setSpritePosition();
};
