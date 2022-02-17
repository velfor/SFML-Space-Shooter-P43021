#pragma once
#include "SFML/Graphics.hpp"

class Meteor {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedx;
	float speedy;
public:
	Meteor(float x, float y, std::string texture_file_name);
	void draw(sf::RenderWindow& window);
	void update();
	size_t getWidth();
	size_t getHeight();
};
