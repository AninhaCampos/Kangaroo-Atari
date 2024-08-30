/*
 * Macaco.hpp
 *
 *  Created on: Aug 23, 2024
 *      Author: Ana Luiza
 */

#ifndef MACACO_HPP_
#define MACACO_HPP_
#include "Fezes.hpp"
#include <cstdlib>
#include <ctime>

class Macaco {
private:
	sf::Vector2f pos;
	int velX = 1, velY = 50;
	sf::RectangleShape macaco;
public:
	Macaco() {
		pos.x = 955;
		pos.y = 7;
		macaco.setSize(sf::Vector2f(50, 50));
		macaco.setFillColor(sf::Color::Blue);
		macaco.setOrigin(25, 25);
		macaco.setPosition(pos);
	}
	void printMacaco(sf::RenderWindow *window) {
			window->draw(macaco);
		}
	void moveMacaco(float tempo) {

		pos.y+=velY * tempo;
		if(pos.y > 492){
			pos.y = 0;
		}
		macaco.setPosition(pos);

		}
	void JogarFezes(){
		srand(time(NULL));

		/*int posicaoPoop = rand() % 3;

		Fezes bosta;

		switch (posicaoPoop){
		case 0:
			Fezes bosta(posX-25,posY+25);
			break;
		case 1:
			Fezes bosta(posX-25,posY);
			break;
		case 2:
			Fezes bosta(posX-25,posY-25);
			break;
		}*/

	}
};

#endif /* MACACO_HPP_ */
