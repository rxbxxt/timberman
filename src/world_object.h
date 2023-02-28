#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "random.h"

class WorldObject {
public:
    enum Type {
        BACKGROUND,
        TREE,
        TREE_BRANCH,
        BEE,
        CLOUD
    };

    WorldObject(WorldObject::Type type,
               const std::string& texture_file,
               float sprite_x = 0,
               float sprite_y = 0,
               float speed = 0);

    void update(float fps, int window_width);
    void draw(sf::RenderWindow &window);

private:
    sf::Texture  texture;
    sf::Sprite   sprite;
    int          texture_x;
    float        x;
    float        y;
    float        speed;
    bool         is_active;

    WorldObject::Type type;

    enum Direction {
        RIGHT,
        LEFT
    };

    void __update(WorldObject::Direction direction,
                  float fps, int window_width);

    void __initUpdateVariables();
    void __initUpdateVariablesHelper();
    void __initUpdateVariablesHelper(int xs, int yrt, int yrb,
                                     int srt, int srb);

    int __x_start;
    int __y_rand_top;
    int __y_rand_bot;
    int __speed_rand_top;
    int __speed_rand_bot;

    void __moveUntilX(WorldObject::Direction direction,
                      float fps, int window_width);

    int __calculateSpeed(int rand_top, int rand_bot) noexcept;
    int __calculateY(int rand_top, int rand_bot) noexcept;
};