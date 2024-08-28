/*
 * Kangaroo.hpp
 *
 *  Created on: Aug 23, 2024
 *      Author: Ana Luiza
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

class Player {
private:
	sf::Vector2f pos;
	int velX = 1, velY = 2;
	sf::Sprite player;

public:

	Player(sf::Texture& playerTexture) {
		pos.x= 5;
		pos.y=720;
		player.setTexture(playerTexture);
		player.setPosition(pos);
		player.setScale(sf::Vector2f(1.2f, 1.2f));


	}
	//desenha player
	void printPlayer(sf::RenderWindow *window) {
		window->draw(player);
	}
	void movePlayer() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (pos.x <= 640 - (player.getGlobalBounds().width / 2)) {
				pos.x += velX;
				player.setPosition(pos);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (pos.x >= 0 + (player.getGlobalBounds().width / 2)) {
				pos.x -= velX;
				player.setPosition(pos);
			}
		}

	}

};

#endif /* PLAYER_HPP_ */
