#include "const.h"
#include "player.h"

Player::Player(float x, float y, std::string texture_file_name){
	texture.loadFromFile(texture_file_name);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}
void Player::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
void Player::update() {
	float speedx = 5.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && 
		sprite.getPosition().x > 0
		)
	{
		sprite.move(-speedx, 0);
	}
	else 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
			sprite.getPosition().x < WINDOW_WIDTH - getWidth()
			)
		{
			sprite.move(speedx, 0);
		}
}
size_t Player::getWidth() { return sprite.getLocalBounds().width; }
size_t Player::getHeight() { return sprite.getLocalBounds().height; }