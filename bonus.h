#pragma once
#include "SFML/Graphics.hpp"

class Player;

class Bonus {
public:
	enum BonusType {HP, SHIELD, FIRE_RATE};
	Bonus(BonusType type, sf::Vector2f position);
	void update();
	void draw(sf::RenderWindow& window) const;

	void action(Player *player) const;

	size_t getWidth() const;
	size_t getHeight() const;
	sf::FloatRect getHitBox() const;
	sf::Vector2f getPosition() const;
	bool getDel() const;
	void setDel(bool x);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	BonusType type;
	bool del = false;
};
