#include "bonus.h"
#include "const.h"

Bonus::Bonus(BonusType type, sf::Vector2f position) {
	switch (type) {
	case HP:
		this->type = type;
		texture.loadFromFile(IMAGES_FOLDER + HP_BONUS_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(position);
		break;
	}
}
void Bonus::update() {sprite.move(0.f, 10.f);}
void Bonus::draw(sf::RenderWindow& window) { window.draw(sprite); }
size_t Bonus::getWidth() { return sprite.getLocalBounds().width; }
size_t Bonus::getHeight() { return sprite.getLocalBounds().height; }
sf::FloatRect Bonus::getHitBox() { return sprite.getGlobalBounds(); }
sf::Vector2f Bonus::getPosition() { return sprite.getPosition(); }
bool Bonus::getDel() { return del; }
void Bonus::setDel(bool x) { del = x; }