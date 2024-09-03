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
	float tempoAnimacao;
	bool subindoEscada;

public:

	Player(sf::Texture &playerTexture) {
		pos.x = 125;
		pos.y = 468;
		delayPulo = 0;
		player.setTexture(playerTexture);
		player.setTextureRect(sf::IntRect(2, 0, 100, 93));
		player.setPosition(pos);
		player.setScale(sf::Vector2f(0.5f, 0.5f));
		player.setOrigin(50, 93);
		velX = 80;
		velY = 50;
		pulo = false;
		tempoPulo = 0.0;
		abaixado = false;
		tempoAnimacao = 0;
		subindoEscada = false;

	}
	//desenha player
	void printPlayer(sf::RenderWindow *window) {
		window->draw(player);
	}
	void movePlayer(float tempo, std::vector<sf::IntRect> right,sf::FloatRect bounds) {
		//subindo escada
		if (bounds.intersects(player.getGlobalBounds())) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				pos.y -= 30 * tempo;
				player.setPosition(pos);
				subindoEscada = true;

			}
		//descendo escada
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
							pos.y += 30 * tempo;
							player.setPosition(pos);
							subindoEscada = true;

						}
		} else {
			subindoEscada = false;
		}

		if (subindoEscada == false) {

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				tempoAnimacao += tempo;
				if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
					player.setTextureRect(right[1]);
				} else if (tempoAnimacao > 0.2 && tempoAnimacao < 0.3) {
					player.setTextureRect(right[2]);
				} else if (tempoAnimacao > 0.4) {
					player.setTextureRect(right[0]);
					tempoAnimacao = 0;
				}
				//std::cout << tempoAnimacao ;


				if (abaixado == false) {
					if (pos.x <= 898 - (player.getGlobalBounds().width / 2)) {
						pos.x += velX * tempo;
						player.setPosition(pos);

					}
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if (abaixado == false) {
					if (pos.x >= 102 + (player.getGlobalBounds().width / 2)) {
						pos.x -= velX * tempo;
						player.setPosition(pos);
					}
				}
			}

			//pulo

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

			//abaixar

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (pulo == false) {
					player.setScale(sf::Vector2f(0.5f, 0.25f));
					//std::cout<<"baixado";
					abaixado = true;
				}
			} else {
				//std::cout<<"nao baixado";
				player.setScale(sf::Vector2f(0.5f, 0.5f));
				abaixado = false;
			}

		}
	}

};

#endif /* PLAYER_HPP_ */
