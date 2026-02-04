#pragma once
#include "entity_manager.h"
#include "game_state.h"
#include "player.h"

// Resolves collisions and related side effects between entities.
class CollisionSystem {
public:
	void process(Player &player,
		EntityManager &entities,
		GameState &game_state) const;

private:
	void handle_player_meteor(Player &player,
		EntityManager &entities,
		GameState &game_state) const;
	void handle_player_bonus(Player &player, EntityManager &entities) const;
	void handle_laser_meteor(EntityManager &entities) const;
	void cleanup_offscreen_entities(EntityManager &entities) const;
};
