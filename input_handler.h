#pragma once
#include <list>
#include <memory>
#include "SFML/Graphics.hpp"
#include "laser.h"
#include "player.h"

// Handles input events and player shooting behavior.
class InputHandler {
public:
	void handle_events(sf::RenderWindow &window,
		Player &player,
		std::list<std::unique_ptr<Laser>> &lasers,
		sf::Clock &fire_clock) const;

private:
	void try_fire(Player &player,
		std::list<std::unique_ptr<Laser>> &lasers,
		sf::Clock &fire_clock) const;
};
