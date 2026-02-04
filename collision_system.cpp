#include "collision_system.h"
#include <algorithm>
#include <vector>
#include "const.h"

namespace {
struct LaserMeteorHit {
	Laser *laser;
	Meteor *meteor;
};
} // namespace

void CollisionSystem::process(Player &player,
	EntityManager &entities,
	GameState &game_state) const
{
	handle_player_meteor(player, entities, game_state);
	handle_player_bonus(player, entities);
	handle_laser_meteor(entities);
	cleanup_offscreen_entities(entities);
}

void CollisionSystem::handle_player_meteor(Player &player,
	EntityManager &entities,
	GameState &game_state) const
{
	for (const auto &meteor : entities.meteors()) {
		if (player.getHitBox().intersects(meteor->getHitBox())) {
			player.reduceHp(meteor->getWidth() / 3);
			meteor->spawn();
		}
	}

	if (player.isDead()) {
		game_state = GameState::GAME_OVER;
	}
}

void CollisionSystem::handle_player_bonus(Player &player, EntityManager &entities) const {
	auto &bonuses = entities.bonuses();
	for (auto it = bonuses.begin(); it != bonuses.end();) {
		if (player.getHitBox().intersects((*it)->getHitBox())) {
			(*it)->action(&player);
			it = bonuses.erase(it);
		} else {
			++it;
		}
	}
}

void CollisionSystem::handle_laser_meteor(EntityManager &entities) const {
	handle_laser_meteor_collisions(entities);
}

void CollisionSystem::handle_laser_meteor_collisions(EntityManager &entities) const {
	std::vector<LaserMeteorHit> hits;
	hits.reserve(entities.lasers().size() * entities.meteors().size());
	for (const auto &laser : entities.lasers()) {
		for (const auto &meteor : entities.meteors()) {
			if (laser->getHitBox().intersects(meteor->getHitBox())) {
				hits.push_back({laser.get(), meteor.get()});
			}
		}
	}

	for (const auto &hit : hits) {
		on_laser_hit_meteor(*hit.laser, *hit.meteor, entities);
	}
}

void CollisionSystem::on_laser_hit_meteor(const Laser &laser,
	Meteor &meteor,
	EntityManager &entities) const {
	(void)laser;
	entities.explosions().emplace_back(
		std::make_shared<Explosion>(meteor.getCenter()));

	meteor.spawn();
	size_t chance = rand() % 100;
	if (chance < 10) {
		auto new_bonus = std::make_shared<Bonus>(
			static_cast<Bonus::BonusType>(0),
			meteor.getPosition());
		entities.bonuses().push_back(new_bonus);
	}
}

void CollisionSystem::cleanup_offscreen_entities(EntityManager &entities) const {
	entities.cleanup_offscreen();
}
