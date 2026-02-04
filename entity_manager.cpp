#include "entity_manager.h"
#include "const.h"

void EntityManager::spawn_meteors(size_t count) {
	meteor_sprites.reserve(count);
	for (size_t i = 0; i < count; i++) {
		meteor_sprites.emplace_back(std::make_unique<Meteor>());
	}
}

void EntityManager::update_all() {
	for (auto &meteor : meteor_sprites) {
		meteor->update();
	}
	for (auto &laser : laser_sprites) {
		laser->update();
	}
	for (auto &bonus : bonus_sprites) {
		bonus->update();
	}
	for (auto &exp : exp_sprites) {
		exp->update();
	}
}

void EntityManager::draw_all(sf::RenderWindow &window) const {
	for (const auto &meteor : meteor_sprites) {
		meteor->draw(window);
	}
	for (const auto &laser : laser_sprites) {
		laser->draw(window);
	}
	for (const auto &bonus : bonus_sprites) {
		bonus->draw(window);
	}
	for (const auto &exp : exp_sprites) {
		exp->draw(window);
	}
}

void EntityManager::cleanup_offscreen() {
	laser_sprites.remove_if([](const auto &laser) { return laser->getPosition().y < 0; });
	bonus_sprites.remove_if([](const auto &bonus) {
		return bonus->getPosition().y > WINDOW_HEIGHT; });
	exp_sprites.remove_if([](const auto &exp) { return exp->getDel(); });
}

std::vector<std::unique_ptr<Meteor>> &EntityManager::meteors() { return meteor_sprites; }
std::list<std::unique_ptr<Laser>> &EntityManager::lasers() { return laser_sprites; }
std::list<std::shared_ptr<Bonus>> &EntityManager::bonuses() { return bonus_sprites; }
std::list<std::shared_ptr<Explosion>> &EntityManager::explosions() { return exp_sprites; }

const std::vector<std::unique_ptr<Meteor>> &EntityManager::meteors() const { return meteor_sprites; }
const std::list<std::unique_ptr<Laser>> &EntityManager::lasers() const { return laser_sprites; }
const std::list<std::shared_ptr<Bonus>> &EntityManager::bonuses() const { return bonus_sprites; }
const std::list<std::shared_ptr<Explosion>> &EntityManager::explosions() const { return exp_sprites; }
