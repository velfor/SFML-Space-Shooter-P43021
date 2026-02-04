#pragma once
#include "entity_manager.h"
#include "game_state.h"
#include "player.h"
#include "splash.h"
#include "text.h"

// Renders entities and UI based on the current game state.
class RenderSystem {
public:
	void draw(GameState game_state,
		sf::RenderWindow &window,
		const Player &player,
		const EntityManager &entities,
		const TextObj &hp_text,
		const Splash &game_over) const;
};
