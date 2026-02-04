#include "game.h"
Game::Game() :
	window(	sf::VideoMode(
				static_cast<size_t> (WINDOW_WIDTH), 
				static_cast<size_t> (WINDOW_HEIGHT)
			),
			WINDOW_TITLE,
			sf::Style::Titlebar | sf::Style::Close
	),
	player(WINDOW_WIDTH / 2 - 112 / 2.f,
		WINDOW_HEIGHT - 75.f, "images/playerShip2_green.png"),
	hp_text(500, 5, 24, sf::Color::Yellow)
{
	window.setFramerateLimit(60);
	entities.spawn_meteors(METEORS_QTY);

}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
		draw();
	}
}
void Game::check_events() {
	input_handler.handle_events(window, player, entities.lasers(), clock);
}
void Game::update() {
	update_system.update(game_state, player, entities, collision_system, hp_text);
}
void Game::draw() {
	render_system.draw(game_state, window, player, entities, hp_text, game_over);
}
