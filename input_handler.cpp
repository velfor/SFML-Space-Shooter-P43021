#include "input_handler.h"

void InputHandler::handle_events(sf::RenderWindow &window,
	Player &player,
	std::list<std::unique_ptr<Laser>> &lasers,
	sf::Clock &fire_clock) const
{
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) {
				try_fire(player, lasers, fire_clock);
			}
			break;
		default:
			break;
		}
	}
}

void InputHandler::try_fire(Player &player,
	std::list<std::unique_ptr<Laser>> &lasers,
	sf::Clock &fire_clock) const
{
	sf::Time elapsed = fire_clock.getElapsedTime();
	if (elapsed.asMilliseconds() <= 250) {
		return;
	}

	lasers.emplace_back(std::make_unique<Laser>(
		player.getPosition().x + player.getWidth() / 2 - 5,
		player.getPosition().y));
	fire_clock.restart();
}
