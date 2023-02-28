#include "world_object.h"

WorldObject::WorldObject(WorldObject::Type type,
                         const std::string &texture_file,
                         float sprite_x,
                         float sprite_y,
                         float speed) {
    this->type = type;
    __initUpdateVariables();

    x           = sprite_x;
    y           = sprite_y;
    this->speed = speed;
    is_active   = false;

    texture.loadFromFile(texture_file);
    texture_x = texture.getSize().x;

    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void WorldObject::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void WorldObject::update(float fps, int window_width) {
    if (type == WorldObject::Type::BEE) {
        __update(WorldObject::Direction::LEFT, fps, window_width);
    }
    else if (type == WorldObject::Type::CLOUD) {
        __update(WorldObject::Direction::RIGHT, fps, window_width);
    } 
}

void WorldObject::__update(WorldObject::Direction direction,
                          float fps, int window_width) {
    if (!is_active) {
        x = __x_start;
        y = __calculateY(__y_rand_top, __y_rand_bot);

        speed = __calculateSpeed(__speed_rand_top, __speed_rand_bot);

        sprite.setPosition(x, y);
        is_active = true;
    }
    else {
        __moveUntilX(direction, fps, window_width);
    }
}

void WorldObject::__moveUntilX(WorldObject::Direction direction, 
                              float fps, int window_width) {
    x = (direction == WorldObject::Direction::LEFT)
        ? (x - speed * fps) 
        : (x + speed * fps);

    sprite.setPosition(x, y);

    if (((direction == WorldObject::Direction::LEFT) && (x < -texture_x)) ||
        ((direction == WorldObject::Direction::RIGHT) && (x > window_width))) {
        is_active = false;
    }
}

int WorldObject::__calculateSpeed(int rand_top, int rand_bot) noexcept {
    return Random::randomNumber(rand_bot, rand_top, (int)this);
}

int WorldObject::__calculateY(int rand_top, int rand_bot) noexcept {
    return Random::randomNumber(rand_bot, rand_top, (int)this);
}

void WorldObject::__initUpdateVariables() {
    if (type == WorldObject::Type::BEE) {
        __initUpdateVariablesHelper(2000, 1000, 500, 400, 200);
    }
    else if (type == WorldObject::Type::CLOUD) {
        __initUpdateVariablesHelper(-400, 300, 50, 100, 50);
    }
    else {
        __initUpdateVariablesHelper(0, 0, 0, 0, 0);
    }
}

void WorldObject::__initUpdateVariablesHelper(int xs, int yrt, int yrb, 
                                             int srt, int srb) {
    __x_start        = xs;
    __y_rand_top     = yrt;
    __y_rand_bot     = yrb;
    __speed_rand_top = srt;
    __speed_rand_bot = srb;
}
