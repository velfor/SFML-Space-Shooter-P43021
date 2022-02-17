#include "const.h"
#include "meteor.h"

Meteor::Meteor(float x, float y, std::string texture_file_name) {
	texture.loadFromFile(texture_file_name);
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
	speedx = rand() % 2 - 1;//getRandom(-1,1)
	speedy = rand() % 8 + 3;//getRandom(3,11)
}
void Meteor::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}
void Meteor::update() {
	sprite.move(speedx, speedy);
	if (sprite.getPosition().x < 0.f-getWidth() ||
		sprite.getPosition().x > WINDOW_WIDTH ||
		sprite.getPosition().y > WINDOW_HEIGHT
		)
	{
		float startx = rand() % (static_cast<size_t>(WINDOW_WIDTH) - getWidth() + 1);
		float starty = rand() % (static_cast<size_t>(WINDOW_HEIGHT) + 1) - WINDOW_HEIGHT;
		sprite.setPosition(startx, starty);
		speedx = rand() % 2 - 1;
		speedy = rand() % 8 + 3;
	}
}
size_t Meteor::getWidth() { return sprite.getLocalBounds().width; }
size_t Meteor::getHeight() { return sprite.getLocalBounds().height; }