#include "laser.h"
#include "const.h"

Laser::Laser(float x, float y) {
	texture.loadFromFile(IMAGES_FOLDER + LASER_FILE_NAME);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}
void Laser::update() {
	sprite.move(0.f, -LASER_SPEEDY);
}
size_t Laser::getWidth() const { return sprite.getLocalBounds().width; }
size_t Laser::getHeight() const { return sprite.getLocalBounds().height; }
sf::FloatRect Laser::getHitBox() const { return sprite.getGlobalBounds(); }
void Laser::draw(sf::RenderWindow& window) const { window.draw(sprite); }
sf::Vector2f Laser::getPosition() const { return sprite.getPosition(); }
