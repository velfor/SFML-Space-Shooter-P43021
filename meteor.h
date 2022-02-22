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
	void draw(sf::RenderWindow& window);
	void update();
	size_t getWidth();
	size_t getHeight();
};
std::string Meteor::meteor_file_names[] = 
{ "meteorBrown_big1.png", "meteorBrown_big2.png",
"meteorBrown_big3.png", "meteorBrown_big4.png", 
"meteorBrown_med1.png", "meteorBrown_med3.png", 
"meteorBrown_small1.png", "meteorBrown_small2.png", 
"meteorBrown_tiny1.png", "meteorBrown_tiny2.png" };
