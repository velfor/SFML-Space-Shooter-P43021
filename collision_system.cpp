#include "collision_system.h"
#include <algorithm>
#include <set>
#include "const.h"

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
	std::set<std::shared_ptr<Bonus>> active_bonus;
	copy_if(
		entities.bonuses().begin(),
		entities.bonuses().end(),
		inserter(active_bonus, active_bonus.end()),
		[&player](const auto &bonus) {
			return player.getHitBox().intersects(bonus->getHitBox());
		});
	entities.bonuses().remove_if([&active_bonus](const auto &bonus) {
		return active_bonus.count(bonus) > 0;
	});
	std::for_each(active_bonus.begin(), active_bonus.end(),
		[&player](const auto &bonus) { bonus->action(&player); });
}

void CollisionSystem::handle_laser_meteor(EntityManager &entities) const {
	for (const auto &laser : entities.lasers()) {
		for (const auto &meteor : entities.meteors()) {
			if (laser->getHitBox().intersects(meteor->getHitBox())) {
				entities.explosions().emplace_back(
					std::make_shared<Explosion>(meteor->getCenter()));

				meteor->spawn();
				size_t chance = rand() % 100;
				if (chance < 10) {
					auto new_bonus = std::make_shared<Bonus>(
						static_cast<Bonus::BonusType>(0),
						meteor->getPosition());
					entities.bonuses().push_back(new_bonus);
				}
			}
		}
	}
}

void CollisionSystem::cleanup_offscreen_entities(EntityManager &entities) const {
	entities.cleanup_offscreen();
}
