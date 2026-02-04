#pragma once
#include "SFML/Graphics.hpp"
#include "const.h"

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float hp = PLAYER_HP;

	float clamp_to_bounds(float x) const;
public:
	Player(float x, float y, std::string texture_file_name);
	void draw(sf::RenderWindow& window) const;
	void update();
	size_t getWidth() const;
	size_t getHeight() const;
	sf::FloatRect getHitBox() const;
	sf::Vector2f getPosition() const;
	void reduceHp(float dmg);
	bool isDead() const;
	float getHp() const;
};

