#include "game_object.h"

GameObject::GameObject(GameObject::Type type,
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

void GameObject::update(float fps, int window_width) {
    if (type == GameObject::Type::BEE) {
        __update(GameObject::Direction::LEFT, fps, window_width);
    }
    else if (type == GameObject::Type::CLOUD) {
        __update(GameObject::Direction::RIGHT, fps, window_width);
    } 
}

void GameObject::__update(GameObject::Direction direction,
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

void GameObject::__moveUntilX(GameObject::Direction direction, 
                              float fps, int window_width) {
    x = (direction == GameObject::Direction::LEFT)
        ? (x - speed * fps) 
        : (x + speed * fps);

    sprite.setPosition(x, y);

    if (((direction == GameObject::Direction::LEFT) && (x < -texture_x)) ||
        ((direction == GameObject::Direction::RIGHT) && (x > window_width))) {
        is_active = false;
    }
}

int GameObject::__calculateSpeed(int rand_top, int rand_bot) noexcept {
    return ___randomNumber(rand_bot, rand_top);
}

int GameObject::__calculateY(int rand_top, int rand_bot) noexcept {
    return ___randomNumber(rand_bot, rand_top);
}

void GameObject::__initUpdateVariables() {
    if (type == GameObject::Type::BEE) {
        __initUpdateVariablesHelper(2000, 1000, 500, 400, 200);
    }
    else if (type == GameObject::Type::CLOUD) {
        __initUpdateVariablesHelper(-400, 300, 50, 100, 50);
    }
    else {
        __initUpdateVariablesHelper(0, 0, 0, 0, 0);
    }
}

void GameObject::__initUpdateVariablesHelper(int xs, int yrt, int yrb, 
                                             int srt, int srb) {
    __x_start        = xs;
    __y_rand_top     = yrt;
    __y_rand_bot     = yrb;
    __speed_rand_top = srt;
    __speed_rand_bot = srb;
}

int GameObject::___randomNumber(int min, int max) {
    typedef std::mt19937 range_t;
    std::uniform_int_distribution<range_t::result_type> udist(min, max);
    range_t range;

    range_t::result_type seed = (int)this;
    range.seed(seed);

    range_t::result_type result = udist(range);

    return result;
}
