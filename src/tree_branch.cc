#include "tree_branch.h"

TreeBranch::TreeBranch(const std::string &texture_file, int multiplier) {
    texture.loadFromFile(texture_file);
    sprite.setTexture(texture);
    sprite.setPosition(-2000, -2000);
    sprite.setOrigin(220, 20);

    this->multiplier = multiplier;
    update();
}

void TreeBranch::update() {
   __setRandomPosition(); 
   __setSpritePosition();
}

void TreeBranch::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void TreeBranch::setPosition(TreeBranch::Position position) {
    this->position = position;
    __setSpritePosition();
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
    float height = multiplier * 150;

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
