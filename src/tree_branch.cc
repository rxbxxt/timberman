#include "tree_branch.h"

TreeBranch::TreeBranch(const std::string &texture_file, int branch_index) {
    texture.loadFromFile(texture_file);
    sprite.setTexture(texture);
    sprite.setPosition(-2000, -2000);
    sprite.setOrigin(220, 20);

    this->branch_index = branch_index;
    __setRandomPosition();
}

void TreeBranch::update() {
    __setSpritePosition();
}

void TreeBranch::none() {
    position = TreeBranch::Position::NONE;
}

void TreeBranch::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void TreeBranch::setIndex(int branch_index) {
    this->branch_index = branch_index;

    if (branch_index == 0) {
        __setRandomPosition();
    }
}

void TreeBranch::__setRandomPosition() {
    int random = Random::randomNumber(0, 11, (int)this);
    random %= 5;

    switch (random) {
    case 0:  position = TreeBranch::Position::LEFT;  break;
    case 1:  position = TreeBranch::Position::RIGHT; break;
    default: position = TreeBranch::Position::NONE;
    }
}

void TreeBranch::__setSpritePosition() {
    float height = branch_index * 170;

    if (position == TreeBranch::Position::LEFT) {
        sprite.setPosition(610, height);
        sprite.setRotation(180); // Flip the sprite
    }
    else if (position == TreeBranch::Position::RIGHT) {
        sprite.setPosition(1330, height);
        sprite.setRotation(0);
    }
    else {
        sprite.setPosition(-3000, height); // Hide the branch
    }
}
