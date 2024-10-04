/*
 * Sino.hpp
 *
 *  Created on: Oct 3, 2024
 *      Author: Ana Luiza
 */

#ifndef SINO_HPP_
#define SINO_HPP_
#include "Player.hpp"
#include "Fruta.hpp"
#include <iostream>
#include "Escada.hpp"
#include "Pontuacao.hpp"


//using namespace p1;
using namespace berry;
namespace bell{
class Sino {
private:
	sf::Texture sinoTexture;
	sf::Sprite sino;
	sf::IntRect rightSino;
	sf::IntRect normalSino;
	sf::IntRect leftSino;
	sf::Vector2f pos;
	bool tocado;
	int spriteFruta;
	int tempoContado;

public:
	Sino() {
		pos.x = 750;
		pos.y = 120;
		tocado = false;
		setAnimation();
		loadTextureSino();
		setSprite();
		spriteFruta=0;
		int tempoContado=0;

	}
	void loadTextureSino() {
		if (!sinoTexture.loadFromFile("assets/Sino.png"))
			std::cerr << "Erro ao carregar a textura do Sino" << std::endl;
	}
	void setAnimation() {
		rightSino = sf::IntRect(0, 48, 44, 44);
		normalSino = sf::IntRect(0, 0, 44, 44);
		leftSino = sf::IntRect(56, 0, 44, 44);
	}
	void setSprite() {
		sino.setTexture(sinoTexture);
		sino.setTextureRect(normalSino);
		sino.setPosition(pos);
		sino.setScale(sf::Vector2f(1, 1));
		sino.setOrigin(22, 22);
	}
	void printSino(sf::RenderWindow *window) {
		window->draw(sino);
	}
	sf::FloatRect retornaHitBoxSino() {
		sf::FloatRect hitboxSino = sino.getGlobalBounds();
		return hitboxSino;
	}

	void tocouSino(sf::FloatRect player, Fruta frutas[],float tempo){
		std::cout<<tempoContado;
		if(retornaHitBoxSino().intersects(player) && tocado==false){

			for(int i=0; i<3 ; i++){
				frutas[i].resetColetada();

		}
			spriteFruta ++;
			tocado=true;
			tempoContado=0;
		}
		tempoContado += tempo;
		if(tempoContado>=1.2){
			tocado=false;
		}



	}


};
}
#endif /* SINO_HPP_ */
