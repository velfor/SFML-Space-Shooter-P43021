#pragma once
#include "SFML/Graphics.hpp"

class Bonus {
public:
	enum BonusType {HP, SHIELD, FIRE_RATE};
	Bonus(BonusType type, sf::Vector2f position);
	void update();
	void draw(sf::RenderWindow& window);
	size_t getWidth();
	size_t getHeight();
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
	bool getDel();
	void setDel(bool x);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	BonusType type;
	bool del = false;
};
