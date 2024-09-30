/*
 * Fezes.hpp
 *
 *  Created on: Aug 23, 2024
 *      Author: Ana Luiza
 */

#ifndef FEZES_HPP_
#define FEZES_HPP_

class Fezes {
private:
	int posX = 640, posY = 0;
	//int velX = 1, velY = 2;
	sf::RectangleShape fezes;
public:
	Fezes(int posX, int posY) {

		this -> posX = posX;
		this -> posY = posY;

		fezes.setSize(sf::Vector2f(5, 5));
		fezes.setFillColor(sf::Color::Yellow);
		fezes.setOrigin(2.5, 2.5);
		fezes.setPosition(posX ,posY );
	}
	void printFezes(sf::RenderWindow *window) {

		window->draw(fezes);
	}

};

#endif /* FEZES_HPP_ */
