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
    score  = 0;

    hud = std::make_unique <HUD>(resolution, &paused);

    background = initObject(GameObject::Type::BACKGROUND, "graphics/background.png");
    tree       = initObject(GameObject::Type::TREE, "graphics/tree.png", 810, 0);
    bee        = initObject(GameObject::Type::BEE, "graphics/bee.png");

    for (auto &cloud : clouds) {
        cloud = initObject(GameObject::Type::CLOUD, "graphics/cloud.png");
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
        score = 0;
    }
}

void Game::update() {
    if (paused) return;

    bee->update(fps, resolution.x);
    for (auto &cloud : clouds) {
        cloud->update(fps, resolution.x);
    }
    hud->update(fps, score);
}

void Game::draw() {
    window.clear();

    background->draw(window);
    for (auto &cloud : clouds) {
        cloud->draw(window);
    }
    tree->draw(window);
    bee->draw(window);

    hud->draw(window, paused);

    window.display();
}
