/*
 * Macaco.hpp
 *
 *  Created on: Aug 23, 2024
 *      Author: Ana Luiza
 */

#ifndef MACACO_HPP_
#define MACACO_HPP_
//#include "Fezes.hpp"
#include <cstdlib>
#include <ctime>

class Macaco {
private:
	sf::Vector2f pos;
	int velX = 1, velY = 80;
	sf::Sprite monkey;
	float angulo;
	float tempoAnimacao;

public:
	Macaco(sf::Texture &monkeyTexture,std::vector<sf::IntRect> downMacaco ) {
		pos.x = 955;
		pos.y = 7;
		angulo = 180.0;
		tempoAnimacao = 0.0;
		monkey.setTexture(monkeyTexture);
		monkey.setTextureRect(downMacaco[0]);
		monkey.setPosition(pos);
		monkey.setOrigin(6.5,10.5);
		monkey.setScale(sf::Vector2f(2.0f, 2.0f));
		monkey.setRotation(angulo);

	}
	void printMacaco(sf::RenderWindow *window) {
			window->draw(monkey);
		}
	void moveMacaco(float tempo, std::vector<sf::IntRect> downMacaco) {

		pos.y+=velY * tempo;
		if(pos.y > 478){
			pos.y = 0;
		}
		tempoAnimacao += tempo;
						if (tempoAnimacao > 0.1 && tempoAnimacao < 0.3) {
							monkey.setTextureRect(downMacaco[1]);
						} else if (tempoAnimacao > 0.4) {
							monkey.setTextureRect(downMacaco[0]);
							//monkey.setRotation(angulo);
							tempoAnimacao = 0;
						}
		monkey.setPosition(pos);

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
