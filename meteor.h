#pragma once
#include "SFML/Graphics.hpp"

class Meteor {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedx;
	float speedy;
	static std::string meteor_file_names[];
public:
	Meteor();
	void draw(sf::RenderWindow& window) const;
	void update();
	size_t getWidth() const;
	size_t getHeight() const;
	sf::FloatRect getHitBox() const;
	sf::Vector2f getPosition() const;
	sf::Vector2f getCenter() const;
	void spawn();
};
