#pragma once
#include "SFML/Graphics.hpp"

class Explosion {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	static std::string explosion_file_names[];
	bool del = false;
	size_t frame = 0;
	size_t frame_delay = 42;
	sf::Clock clock;
	sf::Vector2f position;
public:
	Explosion(sf::Vector2f position);
	void draw(sf::RenderWindow& window);
	void update();
	size_t getWidth();
	size_t getHeight();
	//sf::FloatRect getHitBox();
	//sf::Vector2f getPosition();
	bool getDel();
	void setDel(bool x);
};

