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

    void setIndex(int branch_index);

    void none();
    
    auto getIndex() const { return branch_index; }
    auto getPosition() const { return position; }

private:
    TreeBranch::Position position;
    int branch_index;

    sf::Texture  texture;
    sf::Sprite   sprite;

    void __setSpritePosition();
    void __setRandomPosition();
};
