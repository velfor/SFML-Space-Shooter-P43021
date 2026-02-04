#include "render_system.h"

void RenderSystem::draw(GameState game_state,
	sf::RenderWindow &window,
	const Player &player,
	const EntityManager &entities,
	const TextObj &hp_text,
	const Splash &game_over) const
{
	window.clear();
	switch (game_state) {
	case GameState::PLAY:
		entities.draw_all(window);
		player.draw(window);
		hp_text.draw(window);
		break;
	case GameState::GAME_OVER:
		window.draw(game_over.getSprite());
		break;
	default:
		break;
	}
	window.display();
}
