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
	bool verificaAbaixado;
	sf::Texture playerTexture;
	std::vector<sf::IntRect> rightPlayer;
	std::vector<sf::IntRect> leftPlayer;
	std::vector<sf::IntRect> upPlayer;
	std::vector<sf::IntRect> lowerPlayer;

public:

	Player() {
		loadTexturePlayer();
		setSprite();
		setAnimation();
		pos.x = 125;
		pos.y = 468;
		delayPulo = 0;
		velX = 80;
		velY = 50;
		pulo = false;
		tempoPulo = 0.0;
		abaixado = false;
		tempoAnimacao = 0;
		subindoEscada = false;
		verificaAbaixado = false;

	}
	void loadTexturePlayer(){
		if (!playerTexture.loadFromFile("assets/personagem.png"))
			std::cout << "Erro ao carregar a textura do player" << std::endl;
	}
	void setSprite(){
		player.setTexture(playerTexture);
		player.setTextureRect(sf::IntRect(0, 0, 27, 26));
		player.setPosition(pos);
		player.setScale(sf::Vector2f(2, 2));
		player.setOrigin(13.5, 26);
	}
	void setAnimation(){
		rightPlayer = { sf::IntRect(0, 0, 27, 26), sf::IntRect(27, 0, 27, 26) };
		leftPlayer = { sf::IntRect(106, 27, 26, 26), sf::IntRect(133, 27, 27, 26) };
		upPlayer = { sf::IntRect(132, 0, 26, 26), sf::IntRect(107, 0, 25, 26) };
		lowerPlayer = { sf::IntRect(55, 0, 25, 26), sf::IntRect(80, 0, 26, 26) };
	}
	//desenha player
	void printPlayer(sf::RenderWindow *window) {
		window->draw(player);
	}
	void movePlayer(float tempo,  sf::FloatRect bounds) {
		//subindo escada
		if (bounds.intersects(player.getGlobalBounds())) {

			subirEscada(tempo, rightPlayer, bounds);
			descerEscada(tempo, rightPlayer, bounds);
			subindoEscada = true;

		} else {
			subindoEscada = false;
		}

		if (subindoEscada == false) {

			andarDireita(tempo, rightPlayer);
			andarEsquerda(tempo, leftPlayer);

			pular(tempo, upPlayer, rightPlayer);
			abaixar(tempo, lowerPlayer, rightPlayer);

		}
	}

	//move player::
	void andarDireita(float tempo, std::vector<sf::IntRect> right) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			tempoAnimacao += tempo;
			if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
				player.setTextureRect(right[0]);
			} else if (tempoAnimacao > 0.3) {
				player.setTextureRect(right[1]);
				tempoAnimacao = 0;
			}

			if (abaixado == false) {
				if (pos.x <= 898 - (player.getGlobalBounds().width / 2)) {
					pos.x += velX * tempo;
					player.setPosition(pos);

				}
			}
		}
	}
	void andarEsquerda(float tempo, std::vector<sf::IntRect> left) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			tempoAnimacao += tempo;
			if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
				player.setTextureRect(left[0]);
			} else if (tempoAnimacao > 0.3) {
				player.setTextureRect(left[1]);
				tempoAnimacao = 0;
			}
			if (abaixado == false) {
				if (pos.x >= 102 + (player.getGlobalBounds().width / 2)) {
					pos.x -= velX * tempo;
					player.setPosition(pos);
				}
			}
		}
	}
	void pular(float tempo, std::vector<sf::IntRect> up,
			std::vector<sf::IntRect> right) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			tempoAnimacao += tempo;
			if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
				player.setTextureRect(up[0]);
			} else if (tempoAnimacao > 0.3) {
				player.setTextureRect(up[1]);
				tempoAnimacao = 0;
			}
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
				player.setTextureRect(right[0]);
			}

		}
		player.setPosition(pos);
	}
	void abaixar(float tempo, std::vector<sf::IntRect> lower,std::vector<sf::IntRect> right) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (pulo == false) {
					player.setTextureRect(lower[0]);
				//player.setScale(sf::Vector2f(2, 1));
				//std::cout<<"baixado";
				abaixado = true;
				verificaAbaixado = true;
			}
		} else {
			if(verificaAbaixado == true){

				player.setTextureRect(right[0]);
				verificaAbaixado = false;
			}
			//std::cout<<"nao baixado";
			//player.setScale(sf::Vector2f(2, 2));
			abaixado = false;
		}
	}
	void subirEscada(float tempo, std::vector<sf::IntRect> right,
			sf::FloatRect bounds) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			pos.y -= 30 * tempo;
			player.setPosition(pos);

		}
	}
	void descerEscada(float tempo, std::vector<sf::IntRect> right,
			sf::FloatRect bounds) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			pos.y += 30 * tempo;
			player.setPosition(pos);

		}
	}
};

#endif /* PLAYER_HPP_ */
