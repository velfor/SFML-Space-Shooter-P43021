#include "game.h"
#include <algorithm>
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
		meteor_sprites.emplace_back(std::make_unique<Meteor>());
	}

}
void Game::play() {
	while (window.isOpen()) {
		check_events();
		update();
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
					laser_sprites.emplace_back(std::make_unique<Laser>(
						player.getPosition().x + player.getWidth() / 2 - 5,
						player.getPosition().y));
					clock.restart();
				}
			}
			
	}
}
void Game::update() {
	switch (game_state) {
	case PLAY:
		player.update();
		for (auto &meteor : meteor_sprites) {
			meteor->update();
		}
		for (auto &laser : laser_sprites) {
			laser->update();
		}
		for (auto &bonus : bonus_sprites) {
			bonus->update();
		}
		for (auto &exp : exp_sprites) {
			exp->update();
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
		for (const auto &meteor : meteor_sprites) {
			meteor->draw(window);
		}
		for (const auto &laser : laser_sprites) {
			laser->draw(window);
		}
		for (const auto &bonus : bonus_sprites) {
			bonus->draw(window);
		}
		for (const auto &exp : exp_sprites) {
			exp->draw(window);
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
	//����� � ���������
	for (const auto &meteor : meteor_sprites) {
		if (player.getHitBox().intersects(meteor->getHitBox()))
		{
			player.reduceHp(meteor->getWidth()/3);
			meteor->spawn();
		}
	}
	//������� �����, �������������� � �������
	std::set<std::shared_ptr<Bonus>> active_bonus;
	copy_if(
		bonus_sprites.begin(),
		bonus_sprites.end(),
		inserter(active_bonus, active_bonus.end()),
		[this](const auto &bonus) {return player.getHitBox().intersects(bonus->getHitBox()); }
	);
	bonus_sprites.remove_if([&active_bonus](const auto &bonus) { return active_bonus.count(bonus) > 0; });
	std::for_each(active_bonus.begin(), active_bonus.end(), [this](const auto &bonus){ bonus->action(&player); });
	//����� ����
	if (player.isDead()) game_state = GAME_OVER;
	//�������� ���� �� ����� ������
	laser_sprites.remove_if([](const auto &laser) { return laser->getPosition().y < 0; });
	//�������� ������� �� ����� ������
	bonus_sprites.remove_if([](const auto &bonus) {
		return bonus->getPosition().y > WINDOW_HEIGHT; });
	//���� � ���������
	for (const auto &laser : laser_sprites) {
		for (const auto &meteor : meteor_sprites) {
			if (laser->getHitBox().intersects(meteor->getHitBox()))
			{
				exp_sprites.emplace_back(std::make_shared<Explosion>(meteor->getCenter()));

				meteor->spawn();
				//c ������ 10% �� ������� �������� �����
				size_t chance = rand() % 100;
				if (chance < 10) {
					//������������� ��������� ����� ��� ���� ������
					auto new_bonus = std::make_shared<Bonus>(static_cast<Bonus::BonusType>(0),
						meteor->getPosition());
					bonus_sprites.push_back(new_bonus);
				}
			}
		}
	}
	//������� ���������� �� �������� ������
	exp_sprites.remove_if([](const auto &exp) {return exp->getDel(); });
}
