#include "const.h"
#include "explosion.h"

std::string Explosion::explosion_file_names[] =
{ 
	"regularExplosion00.png", "regularExplosion01.png",
	"regularExplosion02.png", "regularExplosion03.png",
	"regularExplosion04.png", "regularExplosion05.png",
	"regularExplosion06.png", "regularExplosion07.png",
	"regularExplosion08.png" 
};
Explosion::Explosion(sf::Vector2f position) {
	texture.loadFromFile(IMAGES_FOLDER + explosion_file_names[frame]);
	sprite.setTexture(texture);
	sprite.setOrigin(getWidth() / 2.0, getHeight() / 2.0);
	this->position = position;
	sprite.setPosition(position);
	
}
void Explosion::update() {
	sf::Time now = clock.getElapsedTime();
	if (now.asMilliseconds() > frame_delay) {
		clock.restart();
		frame++;
		if (frame < 9) {
			texture.loadFromFile(IMAGES_FOLDER + explosion_file_names[frame]);
			sprite.setTexture(texture);
			sprite.setOrigin(getWidth() / 2.0, getHeight() / 2.0);
			sprite.setPosition(this->position);
		}
		else {
			del = true;
		}
	}
}
void Explosion::draw(sf::RenderWindow& window) { window.draw(sprite); }
bool Explosion::getDel() { return del; }
void Explosion::setDel(bool x) { del = x; }
size_t Explosion::getWidth() { return sprite.getLocalBounds().width; }
size_t Explosion::getHeight() { return sprite.getLocalBounds().height; }