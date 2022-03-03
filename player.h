#pragma once
#include "SFML/Graphics.hpp"
#include "const.h"

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float hp = PLAYER_HP;
public:
	Player(float x, float y, std::string texture_file_name);
	void draw(sf::RenderWindow& window);
	void update();
	size_t getWidth();
	size_t getHeight();
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
	void reduceHp(float dmg);
	bool isDead();
	float getHp();
};

