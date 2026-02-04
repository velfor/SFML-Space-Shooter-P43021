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
size_t Player::getWidth() const { return sprite.getLocalBounds().width; }
size_t Player::getHeight() const { return sprite.getLocalBounds().height; }
sf::FloatRect Player::getHitBox() const { return sprite.getGlobalBounds(); }
sf::Vector2f Player::getPosition() const { return sprite.getPosition(); }
void Player::reduceHp(float dmg) {	hp -= dmg; }
bool Player::isDead() const { return hp < 0; }
float Player::getHp() const { return hp; }
