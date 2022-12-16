#include "game.h"
#include <set>

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
	meteor_sprites.reserve(METEORS_QTY);
	for (size_t i = 0; i < METEORS_QTY; i++) {
		meteor_sprites.push_back(new Meteor());
	}

}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
		check_collisions();
		draw();
	}
}
void Game::check_events() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) window.close();
		else 
			if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Time elapsed = clock.getElapsedTime();
				if (elapsed.asMilliseconds() > 250) {
					laser_sprites.push_back(new Laser(player.getPosition().x +
						player.getWidth() / 2 - 5, player.getPosition().y));
					clock.restart();
				}
			}
			
	}
}
void Game::update() {
	switch (game_state) {
	case PLAY:
		player.update();
		for (size_t i = 0; i < METEORS_QTY; i++) {
			meteor_sprites[i]->update();
		}
		for (auto it = laser_sprites.begin(); it != laser_sprites.end(); it++) {
			(*it)->update();
		}
		for (auto it = bonus_sprites.begin(); it != bonus_sprites.end(); it++) {
			(*it)->update();
		}
		for (auto it = exp_sprites.begin(); it != exp_sprites.end(); it++) {
			(*it)->update();
		}
		check_collisions();
		hp_text.update(std::to_string(static_cast<int>(player.getHp())));
		break;
	case GAME_OVER:
		break;
	}
}
void Game::draw() {

	window.clear();
	switch (game_state) {

	case PLAY:
		for (size_t i = 0; i < METEORS_QTY; i++) {
			meteor_sprites[i]->draw(window);
		}
		for (auto it = laser_sprites.begin(); it != laser_sprites.end(); it++) {
			(*it)->draw(window);
		}
		for (auto it = bonus_sprites.begin(); it != bonus_sprites.end(); it++) {
			(*it)->draw(window);
		}
		for (auto it = exp_sprites.begin(); it != exp_sprites.end(); it++) {
			(*it)->draw(window);
		}
		player.draw(window);
		hp_text.draw(window);
		break;
	case GAME_OVER:
		window.draw(game_over.getSprite());
	}
	window.display();
}
void Game::check_collisions() {
	//игрок с метеорами
	for (size_t i = 0; i < METEORS_QTY; i++) {
		if (player.getHitBox().intersects(
			meteor_sprites[i]->getHitBox()))
		{
			player.reduceHp(meteor_sprites[i]->getWidth()/3);
			meteor_sprites[i]->spawn();
		}
	}
	//удалить бонус, пересекающийся с игроком
	std::set<std::shared_ptr<Bonus>> active_bonus;
	copy_if(
		bonus_sprites.begin(),
		bonus_sprites.end(),
		inserter(active_bonus, active_bonus.end()),
		[this](const auto &bonus) {return player.getHitBox().intersects(bonus->getHitBox()); }
	);
	bonus_sprites.remove_if([&active_bonus](const auto &bonus) { return active_bonus.count(bonus) > 0; });
	std::for_each(active_bonus.begin(), active_bonus.end(), [this](const auto &bonus){ bonus->action(&player); });
	//конец игры
	if (player.isDead()) game_state = GAME_OVER;
	//удаление пуль за краем экрана
	laser_sprites.remove_if([](Laser* laser) {return laser->getPosition().y < 0; });
	//удаление бонусов за краем экрана
	bonus_sprites.remove_if([](const auto &bonus) {
		return bonus->getPosition().y > WINDOW_HEIGHT; });
	//пули с метеорами
	for (auto it = laser_sprites.begin(); it != laser_sprites.end(); it++) {
		for (size_t i = 0; i < METEORS_QTY; i++) {
			if ((*it)->getHitBox().intersects(meteor_sprites[i]->getHitBox()))
			{
				exp_sprites.emplace_back(std::make_shared<Explosion>(meteor_sprites[i]->getCenter()));

				meteor_sprites[i]->spawn();
				//c шансом 10% из метеора выпадает бонус
				size_t chance = rand() % 100;
				if (chance < 10) {
					//сгенерировать случайное число для типа бонуса
					auto new_bonus = std::make_shared<Bonus>(static_cast<Bonus::BonusType>(0),
						meteor_sprites[i]->getPosition());
					bonus_sprites.push_back(new_bonus);
				}
			}
		}
	}
	//удаляем помеченные на удаление взрывы
	exp_sprites.remove_if([](const auto &exp) {return exp->getDel(); });
}
