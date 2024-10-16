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

namespace primata{

class Macaco {
private:
	sf::RectangleShape coco;
	sf::Vector2f pos;
	sf::Vector2f posCoco;
	int velX = 0;
	int velY = 80;
	sf::Sprite monkey;
	float anguloDescendo;
	float anguloAndando;
	float tempoAnimacao;
	//sf::Texture monkeyTexture;
	std::vector<sf::IntRect> downMacaco;
	std::vector<sf::IntRect> leftMacaco;
	std::vector<sf::IntRect> rightMacaco;
	std::vector<sf::IntRect> jogandoCoco;
	bool paradeAndar;
	bool CocoEscolhido;
	bool CocoJogado;
	float delayCoco;

public:

	Macaco(sf::Texture *monkeyTexture) {
		coco.setSize(sf::Vector2f(5, 5));
		coco.setFillColor(sf::Color(156, 90, 60));
		coco.setOrigin(5 / 2, 5 / 2);
		//loadTextureMacaco();
		setAnimation();
		setSprite(downMacaco,monkeyTexture);
		pos.x = 955;
		pos.y = 7;
		posCoco.x = -1;
		posCoco.y = -1;
		anguloDescendo = 180.0;
		anguloAndando = 0.0;
		tempoAnimacao = 0.0;
		paradeAndar = false;
		CocoEscolhido = false;
		CocoJogado = false;
		delayCoco = 0;

	}

	void setSprite(std::vector<sf::IntRect> downMacaco,sf::Texture *monkeyTexture ) {
		monkey.setTexture(*monkeyTexture);
		monkey.setTextureRect(downMacaco[0]);
		monkey.setPosition(pos);
		monkey.setOrigin(6.5, 17);
		monkey.setScale(sf::Vector2f(2.0f, 2.0f));
		monkey.setRotation(anguloDescendo);

	}
	void setAnimation() {
		downMacaco = { sf::IntRect(0, 0, 13, 21), sf::IntRect(14, 0, 14, 21) };
		leftMacaco =
				{ sf::IntRect(45, 15, 17, 17), sf::IntRect(64, 15, 17, 17) };
		rightMacaco =
				{ sf::IntRect(0, 22, 17, 18), sf::IntRect(18, 22, 17, 18) };
		jogandoCoco = { sf::IntRect(0, 60, 18, 14), sf::IntRect(0, 41, 20, 17) };
	}
	void printMacaco(sf::RenderWindow *window) {
		window->draw(monkey);
	}
	void moveMacaco(float tempo) {

		pos.y += velY * tempo;
		if (pos.y > 478) {
			pos.y = 0;
		}
		if (velY != 0) {
			tempoAnimacao += tempo;
			if (tempoAnimacao > 0.1 && tempoAnimacao < 0.3) {
				monkey.setTextureRect(downMacaco[1]);
			} else if (tempoAnimacao > 0.4) {
				monkey.setTextureRect(downMacaco[0]);
				//monkey.setRotation(angulo);
				tempoAnimacao = 0;
			}
		}
		pos.x += velX * tempo;
		monkey.setPosition(pos);

	}

	void pegaCanguru(int andar, float tempo) {

		switch (andar) {
		case 1:
			if (pos.y > 469 && pos.y < 470) {
				if (paradeAndar == false && CocoJogado == false) {
					animacaoAndandoEsquerda(tempo);
					velX = -50;
					velY = 0;
				}
				testaLimiteX(tempo);
			}
			break;

		case 2:
			if (pos.y > 336 && pos.y < 337) {
				if (paradeAndar == false && CocoJogado == false) {
					animacaoAndandoEsquerda(tempo);
					velX = -50;
					velY = 0;
				}
				testaLimiteX(tempo);
			}

			break;

		case 3:
			if (pos.y > 203 && pos.y < 204) {
				if (paradeAndar == false && CocoJogado == false) {
					animacaoAndandoEsquerda(tempo);
					velX = -50;
					velY = 0;
				}
				testaLimiteX(tempo);
			}
			break;
		}
	}
	void animacaoAndandoEsquerda(float tempo) {
		tempoAnimacao += tempo;
		monkey.setRotation(anguloAndando);
		if (tempoAnimacao > 0.1 && tempoAnimacao < 0.3) {
			monkey.setTextureRect(leftMacaco[0]);
		} else if (tempoAnimacao > 0.4) {
			monkey.setTextureRect(leftMacaco[1]);
			tempoAnimacao = 0;
		}
	}
	void animacaoAndandoDireita(float tempo) {
		tempoAnimacao += tempo;
		monkey.setRotation(anguloAndando);
		if (tempoAnimacao > 0.1 && tempoAnimacao < 0.3) {
			monkey.setTextureRect(rightMacaco[1]);
		} else if (tempoAnimacao > 0.4) {
			monkey.setTextureRect(rightMacaco[0]);
			tempoAnimacao = 0;
		}
	}
	void animacaoJogandoCoco(float tempo) {
		tempoAnimacao += tempo;
		monkey.setRotation(anguloAndando);
		if (tempoAnimacao > 0.1 && tempoAnimacao < 0.4) {
			monkey.setTextureRect(jogandoCoco[1]);
		} else if (tempoAnimacao > 0.5  ) {
			monkey.setTextureRect(jogandoCoco[0]);

		}
		if (tempoAnimacao >= 1.0) {
			delayCoco = 0;
			//tempoAnimacao = 0;
		}
	}

	sf::FloatRect retornaHitBoxMacaco() {
		return monkey.getGlobalBounds();

	}

	void testaLimiteX(float tempo) {
		if (pos.x <= 750 && CocoJogado == false) {
			velX = 0;
			paradeAndar = true;
			animacaoJogandoCoco(tempo);
			if (CocoEscolhido == false) {

				randomizaCoco();
				CocoEscolhido = true;
				CocoJogado = true;
				delayCoco = 1.5;
			}
			//voltaMacaco();
		} else if (CocoJogado == true) {
			if (delayCoco > 0) {
				delayCoco -= tempo;
			} else {
				voltaMacaco();
				animacaoAndandoDireita(tempo);
			}
		}

	}

	void randomizaCoco() {

		srand(time(NULL));
		int posicao = (rand() % 3);

		switch (posicao) {
		case 0:
			posCoco.y = pos.y - 2.5;
			posCoco.x = pos.x;
			coco.setPosition(posCoco);

			break;

		case 1:
			posCoco.y = pos.y - 25;
			posCoco.x = pos.x;
			coco.setPosition(posCoco);
			break;

		case 2:
			posCoco.y = pos.y - 55;
			posCoco.x = pos.x;
			coco.setPosition(posCoco);
			break;
		}

	}

	void atualizaCoco(float tempo) {

		if (CocoJogado) {
			posCoco.x -= tempo * 60;
			coco.setPosition(posCoco);

		}

	}

	void someCoco(sf::FloatRect HitBoxKangaroo) {
			if(coco.getGlobalBounds().intersects(HitBoxKangaroo)){
				posCoco.y=1500;
				coco.setPosition(posCoco);
			}
	}

	void voltaMacaco() {
		velX = 50;
		coco.setPosition(posCoco);
		/*if (pos.x > 900) {
			velX = 0;
			velY = 60;

		}*/

	}

	void printCoco(sf::RenderWindow *window) {
		window->draw(coco);
	}

	sf::FloatRect retornaHitBoxCoco() {
		return coco.getGlobalBounds();
	}

	bool morreMacaco(sf::FloatRect HitBoxKangaroo){
		if(monkey.getGlobalBounds().intersects(HitBoxKangaroo)){
			return true;
		}
		else{
			return false;
		}
	}

	sf::Vector2f retornaPosMacaco(){

	        return pos;
	    }
};
}

#endif /* MACACO_HPP_ */
