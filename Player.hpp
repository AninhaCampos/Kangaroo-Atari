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
	int posX = 25, posY = 768;
	int velX = 1, velY = 2;
	sf::RectangleShape Kangaroo;
public:
	Player() {
		Kangaroo.setSize(sf::Vector2f(50, 50));
		Kangaroo.setFillColor(sf::Color::Blue);
		Kangaroo.setOrigin(25, 25);
		Kangaroo.setPosition(posX, (posY - 25));

	}
	//desenha player
	void printPlayer(sf::RenderWindow *window) {
		window->draw(Kangaroo);
	}
	void movePlayer() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (posX <= 640 - (Kangaroo.getSize().x/2)) {
				posX += velX;
				Kangaroo.setPosition(posX, posY-25);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (posX >= 0 + (Kangaroo.getSize().x/2)) {
				posX -= velX;
				Kangaroo.setPosition(posX, posY-25);
			}
		}

	}

};

#endif /* PLAYER_HPP_ */
