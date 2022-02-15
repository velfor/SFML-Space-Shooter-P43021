#pragma once
#include "const.h"
#include "SFML/Graphics.hpp"

class Game {
public:
	enum GameState {INTRO, PLAY, PAUSE, GAME_OVER};
	Game();
	void play();
private:
	void check_events();
	void update();
	void draw();
	void check_collisions();

	sf::RenderWindow window;
};

