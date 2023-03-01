#include "timber.h"

Timber::Timber(const std::string &timber_texture_file,
               const std::string &timber_rip_texture_file,
               const std::string &timber_axe_texture_file) {
    timber_texture.loadFromFile(timber_texture_file);
    timber_sprite.setTexture(timber_texture);
    timber_sprite.setPosition(580, 720);

    rip_texture.loadFromFile(timber_rip_texture_file);
    rip_sprite.setTexture(rip_texture);
    rip_sprite.setPosition(-3000, 860);

    axe_texture.loadFromFile(timber_axe_texture_file);
    axe_sprite.setTexture(axe_texture);
    axe_sprite.setPosition(700, 830);

    position = Timber::Position::LEFT;
    alive = true;
}

void Timber::update() {
    if (!alive) return;

    if (position == Timber::Position::RIGHT) {
        timber_sprite.setPosition(1200, 720);
        axe_sprite.setPosition(1075, 830);
    }
    else {
        timber_sprite.setPosition(580, 720);
        axe_sprite.setPosition(700, 830);
    }
}

void Timber::draw(sf::RenderWindow &window) {
    window.draw(timber_sprite);
    window.draw(axe_sprite);
    window.draw(rip_sprite);
}

void Timber::rip() {
    // hide the Chopper and his axe
    timber_sprite.setPosition(-3000, 720);
    axe_sprite.setPosition(-3000, 830);

    // RIP
    alive = false;

    if (position == Timber::Position::RIGHT) {
        rip_sprite.setPosition(1145, 760);
    }
    else {
        rip_sprite.setPosition(525, 760);
    }
}

void Timber::revival() {
    alive = true;
    rip_sprite.setPosition(-3000, 760);
}
