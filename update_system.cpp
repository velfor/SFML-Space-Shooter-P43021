#include "update_system.h"
#include <string>

void UpdateSystem::update(GameState &game_state,
	Player &player,
	EntityManager &entities,
	CollisionSystem &collisions,
	TextObj &hp_text) const
{
	if (game_state != GameState::PLAY) {
		return;
	}

	player.update();
	entities.update_all();
	collisions.process(player, entities, game_state);
	hp_text.update(std::to_string(static_cast<int>(player.getHp())));
}
