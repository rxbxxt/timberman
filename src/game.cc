#include "game.h"

Game::Game() {
    resolution.x = (float)sf::VideoMode::getDesktopMode().width;
    resolution.y = (float)sf::VideoMode::getDesktopMode().height;

    window.create(
        sf::VideoMode((unsigned)resolution.x, (unsigned)resolution.y),
        "Timberman",
        sf::Style::Fullscreen);

    paused = true;
    fps    = 0;

    hud = std::make_unique<HUD>(resolution, &paused);

    background = __initWorldObject(
        WorldObject::Type::BACKGROUND, "graphics/background.png");

    tree = __initWorldObject(
        WorldObject::Type::TREE, "graphics/tree.png", 810, 0);

    bee = __initWorldObject(
        WorldObject::Type::BEE, "graphics/bee.png");

    for (auto &cloud : clouds) {
        cloud = __initWorldObject(
            WorldObject::Type::CLOUD, "graphics/cloud.png");
    }

    // ------------- TO REFACTOR ------------- 
    for (auto &branch : tree_branches) {
        branch = __initTreeBranch("graphics/branch.png");
    }
}

void Game::run() {
    while (window.isOpen()) {
        delta_time = clock.restart();
        fps = delta_time.asSeconds();

        handleInput();
        update();
        draw();
    }
}

void Game::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        paused = !paused;
    }
}

void Game::update() {
    if (paused) return;

    bee->update(fps, resolution.x);
    for (auto &cloud : clouds) {
        cloud->update(fps, resolution.x);
    }
    for (int i = 0; i < tree_branches.size(); ++i) {
        tree_branches[i]->update(i);
    }
    hud->update(fps);
}

void Game::draw() {
    window.clear();

    background->draw(window);
    for (auto &cloud : clouds) {
        cloud->draw(window);
    }
    tree->draw(window);
    for (auto &branch: tree_branches) {
        branch->draw(window);
    }
    bee->draw(window);

    hud->draw(window, paused);

    window.display();
}
