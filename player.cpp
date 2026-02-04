#include <algorithm>
#include "const.h"
#include "player.h"

Player::Player(float x, float y, std::string texture_file_name){
	texture.loadFromFile(texture_file_name);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}
void Player::draw(sf::RenderWindow& window) const {
	window.draw(sprite);
}
void Player::update() {
	float speedx = PLAYER_SPEEDX;
	int direction = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		direction -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		direction += 1;
	}

	float next_x = sprite.getPosition().x + speedx * direction;
	next_x = clamp_to_bounds(next_x);
	sprite.setPosition(next_x, sprite.getPosition().y);
}
size_t Player::getWidth() const { return sprite.getLocalBounds().width; }
size_t Player::getHeight() const { return sprite.getLocalBounds().height; }
sf::FloatRect Player::getHitBox() const { return sprite.getGlobalBounds(); }
sf::Vector2f Player::getPosition() const { return sprite.getPosition(); }
void Player::reduceHp(float dmg) {	hp -= dmg; }
bool Player::isDead() const { return hp < 0; }
float Player::getHp() const { return hp; }

float Player::clamp_to_bounds(float x) const {
	float max_x = WINDOW_WIDTH - getWidth();
	return std::clamp(x, 0.0f, max_x);
}
