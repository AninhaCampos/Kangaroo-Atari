/*
 * Kangaroo.hpp
 *
 *  Created on: Aug 23, 2024
 *      Author: Ana Luiza
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <iostream>
class Player {
private:
	sf::Vector2f pos;
	float velX, velY;
	sf::Sprite player;
	bool pulo;
	float tempoPulo;
	bool abaixado;
	float delayPulo;

public:

	Player(sf::Texture &playerTexture) {
		pos.x = 115;
		pos.y = 465;
		delayPulo = 0;
		player.setTexture(playerTexture);
		player.setPosition(pos);
		player.setScale(sf::Vector2f(1.2f, 1.2f));
		player.setOrigin(12, 33);
		velX = 50;
		velY = 50;
		pulo = false;
		tempoPulo = 0.0;
		abaixado = false;

	}
	//desenha player
	void printPlayer(sf::RenderWindow *window) {
		window->draw(player);
	}
	void movePlayer(float tempo) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (abaixado == false) {
				if (pos.x <= 895 - (player.getGlobalBounds().width / 2)) {
					pos.x += velX * tempo;
					player.setPosition(pos);

				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (abaixado == false) {
				if (pos.x >= 107 + (player.getGlobalBounds().width / 2)) {
					pos.x -= velX * tempo;
					player.setPosition(pos);
				}
			}
		}

	}

	void puloPlayer(float tempo) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (delayPulo > 0.2) {
				if (abaixado == false) {
					if (pulo == false) {
						pos.y -= 30;
						tempoPulo = 0;
						pulo = true;
					}
				}
			}
		}
		tempoPulo += tempo;
		delayPulo += tempo;
		if (pulo == true) {
			if (tempoPulo > 0.5) {
				pos.y += 30;

				pulo = false;
				delayPulo = 0;

			}

		}
		player.setPosition(pos);

	}

	void abaixarPlayer() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (pulo == false) {
				player.setScale(sf::Vector2f(1.2f, 0.6f));
				//std::cout<<"baixado";
				abaixado = true;
			}
		} else {
			//std::cout<<"nao baixado";
			player.setScale(sf::Vector2f(1.2f, 1.2f));
			abaixado = false;
		}

	}

};

#endif /* PLAYER_HPP_ */
