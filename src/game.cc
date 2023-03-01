#include "game.h"

Game::Game() {
    resolution.x = (float)sf::VideoMode::getDesktopMode().width;
    resolution.y = (float)sf::VideoMode::getDesktopMode().height;

    window.create(
        sf::VideoMode((unsigned)resolution.x, (unsigned)resolution.y),
        "Timberman",
        sf::Style::Fullscreen);

    accept_input = false;
    paused = true;
    lost   = false;
    fps    = 0;
    score  = 0;

    __initAllObjects();
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
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyReleased && !paused) {
            accept_input = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        paused = !paused;
    }

    if (!accept_input) return;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        timber->setPosition(Timber::Position::RIGHT);
        __handleChop();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        timber->setPosition(Timber::Position::LEFT);
        __handleChop();
    }
}

void Game::update() {
    bool alive = true;

    if (paused) return;

    bee->update(fps, resolution.x);
    for (auto &cloud : clouds) {
        cloud->update(fps, resolution.x);
    }

    if (lost) {
        __newRound(); 
    }
    else {
        for (auto &branch : tree_branches) {
            branch->update();
        }
    }

    if (timber->getPosition() == __lastBranchPosition()) {
        alive = false;
        timber->rip();
    }
    timber->update();

    hud->update(fps, score, alive);
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
    timber->draw(window);

    bee->draw(window);
    hud->draw(window);

    window.display();
}

void Game::__initAllObjects() {
    timber = std::make_unique<Timber>("graphics/player.png",
                                      "graphics/rip.png",
                                      "graphics/axe.png");

    hud = std::make_unique<HUD>(resolution, &paused, &lost);

    background = __initWorldObject(
        WorldObject::Type::BACKGROUND, "graphics/background.png");

    tree = __initWorldObject(
        WorldObject::Type::TREE, "graphics/tree.png", 810, 0);

    bee = __initWorldObject(
        WorldObject::Type::BEE, "graphics/bee.png", -3000, 0);

    for (auto &cloud : clouds) {
        cloud = __initWorldObject(
            WorldObject::Type::CLOUD, "graphics/cloud.png", -3000, 0);
    }

    int i = 0;
    for (auto &branch : tree_branches) {
        branch = __initTreeBranch("graphics/branch.png", i);
        ++i;
    }
}

void Game::__handleChop() {
    ++score;
    tmb::Sound::playChop();

    hud->addTime(score);

    for (auto &branch : tree_branches) {
        branch->setIndex(branch->getIndex() + 1);
        if (branch->getIndex() == tree_branches.size()) {
            branch->setIndex(0);
        }
    }
    accept_input = false;
}

const TreeBranch &Game::__lastBranch() const {
    for (auto &branch : tree_branches) {
        if (branch->getIndex() == tree_branches.size() - 1) {
            return *branch;
        }
    }
}

TreeBranch::Position Game::__lastBranchPosition() {
    return __lastBranch().getPosition();
}

void Game::__newRound() {
    lost = false;
    score = 0;

    for (const auto &branch : tree_branches) {
        if (branch->getIndex() != tree_branches.size() - 1) {
            branch->update();
        }
        else {
            branch->none();
        }
    }
    timber->revival();
}
