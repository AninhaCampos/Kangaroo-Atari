/*
 * Player2.hpp
 *
 *  Created on: Oct 5, 2024
 *      Author: Ana Luiza
 */

#ifndef MINIKANGAROO_HPP_
#define MINIKANGAROO_HPP_

class MiniKangaroo {
private:
	sf::Vector2f pos;
	float velX;
	float tempoAnimacao;
	sf::Texture playerTexture2;
	sf::Sprite player2;
	std::vector<sf::IntRect> rightPlayer2;
	std::vector<sf::IntRect> leftPlayer2;
public:
	MiniKangaroo() {
		pos.x = 810;
		pos.y = 55;
		velX = 50;
		loadTexturePlayer();
		setSprite();
		setAnimation();
	}
	void loadTexturePlayer() {
		if (!playerTexture2.loadFromFile("assets/personagem2.png"))
			std::cout << "Erro ao carregar a textura do player 2" << std::endl;
	}
	void setSprite() {
		player2.setTexture(playerTexture2);
		player2.setTextureRect(sf::IntRect(0, 0, 38, 36));
		player2.setPosition(pos);
		player2.setScale(sf::Vector2f(0.9, 0.9));
		player2.setOrigin(19, 18);
	}
	void setAnimation() {
		rightPlayer2 =
				{ sf::IntRect(0, 0, 38, 36), sf::IntRect(39, 0, 38, 36) };
		leftPlayer2 =
				{ sf::IntRect(0, 37, 38, 36), sf::IntRect(39, 37, 38, 36) };
	}
	void printPlayer2(sf::RenderWindow *window) {
		window->draw(player2);
	}
	void movePlayer2(float tempo) {

		if (velX > 0) { //direita
			if (pos.x < 800 - (player2.getGlobalBounds().width / 2)) {
				tempoAnimacao += tempo;
				if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
					player2.setTextureRect(rightPlayer2[0]);
				} else if (tempoAnimacao > 0.3) {
					player2.setTextureRect(rightPlayer2[1]);
					tempoAnimacao = 0;
				}
				pos.x += velX * tempo;

			} else if (pos.x >= 800 - (player2.getGlobalBounds().width / 2)) {
				velX *= -1;
				player2.setTextureRect(leftPlayer2[0]);
			}

		}else if (velX < 0) { //esquerda
			if (pos.x > 650 + (player2.getGlobalBounds().width / 2)) {
				tempoAnimacao += tempo;
				if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
					player2.setTextureRect(leftPlayer2[0]);
				} else if (tempoAnimacao > 0.3) {
					player2.setTextureRect(leftPlayer2[1]);
					tempoAnimacao = 0;
				}
				pos.x += velX * tempo;

			} else if (pos.x <= 650 + (player2.getGlobalBounds().width / 2)) {
				velX *= -1;
				player2.setTextureRect(rightPlayer2[0]);
			}
		}
		player2.setPosition(pos);
	}
};

#endif /* MINIKANGAROO_HPP_ */
