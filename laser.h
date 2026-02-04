#pragma once
#include "SFML/Graphics.hpp"

class Laser {
private:
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Laser(float, float);
	void draw(sf::RenderWindow& window) const;
	void update();
	size_t getWidth() const;
	size_t getHeight() const;
	sf::FloatRect getHitBox() const;
	sf::Vector2f getPosition() const;
};
