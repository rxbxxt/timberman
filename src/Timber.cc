#include <SFML/Graphics.hpp>

int main() {
	sf::VideoMode window_resolution(1920, 1080);
	sf::RenderWindow game_window(window_resolution, "Timber", sf::Style::Fullscreen);

	sf::Texture texture_background;
	texture_background.loadFromFile("graphics/background.png");

	sf::Texture texture_tree;
	texture_tree.loadFromFile("graphics/tree.png");

	sf::Texture texture_bee;
	texture_bee.loadFromFile("graphics/bee.png");

	sf::Texture texture_cloud;
	texture_cloud.loadFromFile("graphics/cloud.png");

	sf::Sprite sprite_background;
	sprite_background.setTexture(texture_background);
	sprite_background.setPosition(0, 0);

	sf::Sprite sprite_tree;
	sprite_tree.setTexture(texture_tree);
	sprite_tree.setPosition(810, 0);

	bool bee_active = false;
	float bee_speed = 0.0f;
	float bee_height = 800;
	sf::Sprite sprite_bee;
	sprite_bee.setTexture(texture_bee);
	sprite_bee.setPosition(0, bee_height);

	const int CLOUD_COUNT = 3;
	float cloud_speed[CLOUD_COUNT];
	bool cloud_active[CLOUD_COUNT];
	float cloud_height[CLOUD_COUNT];
	sf::Sprite sprite_cloud[CLOUD_COUNT];

	for (int i = 0; i < CLOUD_COUNT; ++i) {
		sprite_cloud[i].setTexture(texture_cloud);
		sprite_cloud[i].setPosition(0, i * 150.0f);
		cloud_speed[i] = 0.0f;
		cloud_active[i] = false;
	}

	sf::Clock clock;

	while (game_window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			game_window.close();
		}
		game_window.clear();

		// For the same speed on any PC (seems to be...)
		sf::Time cycle_time = clock.restart();

		if (!bee_active) {
			srand((int)time(0));
			bee_speed = rand() % 200 + 200.0f;

			srand((int)time(0) * 10);
			bee_height = rand() % 500 + 500.0f;

			sprite_bee.setPosition(2000, bee_height);
			bee_active = true;
		}
		else { // Move the bee
			sprite_bee.setPosition(
				sprite_bee.getPosition().x -
					(bee_speed * cycle_time.asSeconds()),
				sprite_bee.getPosition().y);

			if (sprite_bee.getPosition().x < -100) {
				bee_active = false;
			}
		}

		for (int i = 0; i < CLOUD_COUNT; ++i) {
			if (!cloud_active[i]) {
				srand((int)time(0) * (i + 1));
				cloud_speed[i] = rand() % 150 + 50.0f;

				srand((int)time(0) * i * 10);
				cloud_height[i] = (rand() % 125) + (125 * i);

				sprite_cloud[i].setPosition(-200, cloud_height[i]);
				cloud_active[i] = true;
			}
			else { // Move clouds
				sprite_cloud[i].setPosition(
					sprite_cloud[i].getPosition().x +
						(cloud_speed[i] * cycle_time.asSeconds()),
					sprite_cloud[i].getPosition().y);
				
				if (sprite_cloud[i].getPosition().x > 1920) {
					cloud_active[i] = false;
				}
			}
		}

		game_window.draw(sprite_background);
		for (const auto& cloud : sprite_cloud) {
			game_window.draw(cloud);
		}
		game_window.draw(sprite_tree);
		game_window.draw(sprite_bee);

		game_window.display();
	}

	return 0;
}
