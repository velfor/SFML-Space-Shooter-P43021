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
	for (size_t i = 0; i < METEORS_QTY; i++) {
		if (player.getHitBox().intersects(
			meteor_sprites[i]->getHitBox()))
		{
			player.reduceHp(meteor_sprites[i]->getWidth()/3);
			meteor_sprites[i]->spawn();
		}
	}
	//����� � ��������
	for (auto it = bonus_sprites.begin(); it != bonus_sprites.end(); it++) {
		if (player.getHitBox().intersects((*it)->getHitBox())) {
			player.reduceHp(-50);
		}
	}
	//������� �����, �������������� � �������
	//bonus_sprites.remove_if([](Bonus* bonus, Player player) {return player.getHitBox().intersects(bonus->getHitBox()); });
	//����� ����
	if (player.isDead()) game_state = GAME_OVER;
	//�������� ���� �� ����� ������
	laser_sprites.remove_if([](Laser* laser) {return laser->getPosition().y < 0; });
	//�������� ������� �� ����� ������
	bonus_sprites.remove_if([](Bonus* bonus) {
		return bonus->getPosition().y > WINDOW_HEIGHT; });
	//���� � ���������
	for (auto it = laser_sprites.begin(); it != laser_sprites.end(); it++) {
		for (size_t i = 0; i < METEORS_QTY; i++) {
			if ((*it)->getHitBox().intersects(meteor_sprites[i]->getHitBox()))
			{
				meteor_sprites[i]->spawn();
				//c ������ 10% �� ������� �������� �����
				size_t chance = rand() % 100;
				if (chance < 10) {
					//������������� ��������� ����� ��� ���� ������
					Bonus* new_bonus = new Bonus(static_cast<Bonus::BonusType>(0),
						meteor_sprites[i]->getPosition());
					bonus_sprites.push_back(new_bonus);
				}
			}
		}
	}
}