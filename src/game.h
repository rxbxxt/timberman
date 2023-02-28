#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <array>

#include "world_object.h"
#include "tree_branch.h"
#include "timber.h"
#include "hud.h"

class Game {
public:
    Game();
    void run();

private:
    sf::Clock         clock;
    sf::Time          delta_time;
    sf::RenderWindow  window;
    sf::Vector2f      resolution;

    float             score;
    float             fps;
    bool              paused;
    bool              accept_input;

    void handleInput();
    void update();
    void draw();

    std::unique_ptr <Timber> timber;

    std::unique_ptr <HUD> hud;

    std::unique_ptr <WorldObject> background;
    std::unique_ptr <WorldObject> tree;
    std::unique_ptr <WorldObject> bee;

    std::array <std::unique_ptr <WorldObject>, 3> clouds;
    std::array <std::unique_ptr <TreeBranch>,  6> tree_branches;

    auto __initWorldObject(WorldObject::Type type,
                           const std::string &texture_file,
                           float sprite_x = 0,
                           float sprite_y = 0,
                           float speed    = 0) {
         return std::make_unique<WorldObject>(
             type, texture_file, sprite_x, sprite_y, speed);
    }

    auto __initTreeBranch(const std::string &texture_file, int multiplier) {
         return std::make_unique<TreeBranch>(texture_file, multiplier);
    }

    void __initAllObjects();
};
