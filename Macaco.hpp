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
	sf::RectangleShape coco;
	sf::Vector2f pos;
	sf::Vector2f posCoco;
	int velX = 0;
	int velY = 80;
	sf::Sprite monkey;
	float anguloDescendo;
	float anguloAndando;
	float tempoAnimacao;
	sf::Texture monkeyTexture;
	std::vector<sf::IntRect> downMacaco;
	std::vector<sf::IntRect> leftMacaco;
	bool paradeAndar;
	bool CocoEscolhido;
	bool CocoJogado;
	float delayCoco;

public:

	Macaco() {
		coco.setSize(sf::Vector2f(5, 5));
		coco.setFillColor(sf::Color::Black);
		coco.setOrigin(5 / 2, 5/2);
		loadTextureMacaco();
		setAnimation();
		setSprite(downMacaco);
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
	void loadTextureMacaco() {
		if (!monkeyTexture.loadFromFile("assets/macaco.png"))
			std::cout << "Erro ao carregar a textura do macaco" << std::endl;
	}
	void setSprite(std::vector<sf::IntRect> downMacaco) {
		monkey.setTexture(monkeyTexture);
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
	void JogarFezes() {
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

	void pegaCanguru(int andar, float tempo) {

		switch (andar) {
		case 1:
			if (pos.y > 469 && pos.y < 470) {
				if(paradeAndar==false){
				animacaoAndandoEsquerda(tempo);
				velX = -50;
				velY = 0;
				}
				testaLimiteX();
			}
			break;

		case 2:
			if (pos.y > 336 && pos.y < 337) {
				if(paradeAndar==false){
				animacaoAndandoEsquerda(tempo);
				velX = -50;
				velY = 0;
				}
				testaLimiteX();
			}

			break;

		case 3:
			if (pos.y > 203 && pos.y < 204) {
				if(paradeAndar==false){
				animacaoAndandoEsquerda(tempo);
				velX = -50;
				velY = 0;
				}
				testaLimiteX();
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
	sf::FloatRect retornaHitBoxMacaco(){
		return monkey.getGlobalBounds();

	}

	void testaLimiteX(){
		if( pos.x <= 750){
			velX=0;
			paradeAndar=true;
			if(CocoEscolhido==false){

			randomizaCoco();
			CocoEscolhido=true;
			CocoJogado=true;
			}
			voltaMacaco();
		}

	}

	void randomizaCoco(){

		 srand (time(NULL));
		 int posicao = (rand() % 3);
		 posicao=2;
		 switch (posicao){
		 case 0:
			 posCoco.y = pos.y-2.5;
			 posCoco.x = pos.x;
			 coco.setPosition(posCoco);

		 break ;

		 case 1:
			 posCoco.y = pos.y-25;
			 posCoco.x = pos.x;
			 coco.setPosition(posCoco);
		 break ;

		 case 2:
			 posCoco.y = pos.y-55;
			 posCoco.x = pos.x;
			 coco.setPosition(posCoco);
		 break ;
		 }



	}

	void atualizaCoco(float tempo ){
		if(CocoJogado){
		posCoco.x -= tempo*60;
		coco.setPosition(posCoco);

		}

	}

	void voltaMacaco(){
		velX = 50;
		 coco.setPosition(posCoco);
		 if(pos.x>900){
			 velX=0;
			 velY=60;

		 }

	}

	void printCoco(sf::RenderWindow *window){
		window->draw(coco);
	}

	sf::FloatRect retornaHitBoxCoco(){
		return coco.getGlobalBounds();
	}



};

#endif /* MACACO_HPP_ */
