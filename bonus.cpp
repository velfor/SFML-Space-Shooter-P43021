#include "bonus.h"
#include "const.h"
#include "player.h"

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
void Bonus::draw(sf::RenderWindow& window) const { window.draw(sprite); }
size_t Bonus::getWidth() const { return sprite.getLocalBounds().width; }
size_t Bonus::getHeight() const { return sprite.getLocalBounds().height; }
sf::FloatRect Bonus::getHitBox() const { return sprite.getGlobalBounds(); }
sf::Vector2f Bonus::getPosition() const { return sprite.getPosition(); }
bool Bonus::getDel() const { return del; }
void Bonus::setDel(bool x) { del = x; }

void Bonus::action(Player *player) const
{
	player->reduceHp(-50);
}
