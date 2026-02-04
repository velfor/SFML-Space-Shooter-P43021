#pragma once
#include <list>
#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include "bonus.h"
#include "explosion.h"
#include "laser.h"
#include "meteor.h"

// Stores and manages all game entities except the player.
class EntityManager {
public:
	void spawn_meteors(size_t count);
	void update_all();
	void draw_all(sf::RenderWindow &window) const;
	void cleanup_offscreen();

	std::vector<std::unique_ptr<Meteor>> &meteors();
	std::list<std::unique_ptr<Laser>> &lasers();
	std::list<std::shared_ptr<Bonus>> &bonuses();
	std::list<std::shared_ptr<Explosion>> &explosions();

	const std::vector<std::unique_ptr<Meteor>> &meteors() const;
	const std::list<std::unique_ptr<Laser>> &lasers() const;
	const std::list<std::shared_ptr<Bonus>> &bonuses() const;
	const std::list<std::shared_ptr<Explosion>> &explosions() const;

private:
	std::vector<std::unique_ptr<Meteor>> meteor_sprites;
	std::list<std::unique_ptr<Laser>> laser_sprites;
	std::list<std::shared_ptr<Bonus>> bonus_sprites;
	std::list<std::shared_ptr<Explosion>> exp_sprites;
};
