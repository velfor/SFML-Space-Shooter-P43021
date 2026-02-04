#pragma once
#include "collision_system.h"
#include "entity_manager.h"
#include "game_state.h"
#include "player.h"
#include "text.h"

// Updates player, entities, and UI state each frame.
class UpdateSystem {
public:
	void update(GameState &game_state,
		Player &player,
		EntityManager &entities,
		CollisionSystem &collisions,
		TextObj &hp_text) const;
};
