#pragma once
#include "const.h"
#include "SFML/Graphics.hpp"
#include "collision_system.h"
#include "entity_manager.h"
#include "game_state.h"
#include "input_handler.h"
#include "player.h"
#include "render_system.h"
#include "splash.h"
#include "text.h"
#include "update_system.h"

// Orchestrates the high-level game loop and state transitions.
class Game {
public:
	Game();
	void play();
private:
	void check_events();
	void update();
	void draw();

	sf::RenderWindow window;
	Player player;
	GameState game_state = GameState::PLAY;
	Splash game_over;
	TextObj hp_text;
	sf::Clock clock;
	EntityManager entities;
	InputHandler input_handler;
	UpdateSystem update_system;
	RenderSystem render_system;
	CollisionSystem collision_system;
};

