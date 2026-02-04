#include "entity_manager.h"
#include "const.h"

namespace {
template <typename Container, typename Fn>
void for_each_entity(Container &container, Fn &&fn) {
	for (auto &entity : container) {
		fn(entity);
	}
}
} // namespace

void EntityManager::spawn_meteors(size_t count) {
	meteor_sprites.reserve(count);
	for (size_t i = 0; i < count; i++) {
		meteor_sprites.emplace_back(std::make_unique<Meteor>());
	}
}

void EntityManager::update_all() {
	for_each_entity(meteor_sprites, [](auto &meteor) { meteor->update(); });
	for_each_entity(laser_sprites, [](auto &laser) { laser->update(); });
	for_each_entity(bonus_sprites, [](auto &bonus) { bonus->update(); });
	for_each_entity(exp_sprites, [](auto &exp) { exp->update(); });
}

void EntityManager::draw_all(sf::RenderWindow &window) const {
	for_each_entity(meteor_sprites, [&window](const auto &meteor) { meteor->draw(window); });
	for_each_entity(laser_sprites, [&window](const auto &laser) { laser->draw(window); });
	for_each_entity(bonus_sprites, [&window](const auto &bonus) { bonus->draw(window); });
	for_each_entity(exp_sprites, [&window](const auto &exp) { exp->draw(window); });
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
