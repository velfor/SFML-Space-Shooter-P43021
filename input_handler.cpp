#include "input_handler.h"

void InputHandler::handle_events(sf::RenderWindow &window,
	Player &player,
	std::list<std::unique_ptr<Laser>> &lasers,
	sf::Clock &fire_clock) const
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		} else if (event.type == sf::Event::MouseButtonPressed &&
			event.mouseButton.button == sf::Mouse::Left) {
			sf::Time elapsed = fire_clock.getElapsedTime();
			if (elapsed.asMilliseconds() > 250) {
				lasers.emplace_back(std::make_unique<Laser>(
					player.getPosition().x + player.getWidth() / 2 - 5,
					player.getPosition().y));
				fire_clock.restart();
			}
		}
	}
}
