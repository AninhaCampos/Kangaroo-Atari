/*
 * Fruta.h
 *
 *  Created on: Sep 30, 2024
 *      Author: Ana Luiza
 */

#ifndef FRUTA_HPP_
#define FRUTA_HPP_
#include "Pontuacao.hpp"
#include <vector>

using namespace points;
namespace berry{
class Fruta {
private:
	sf::Texture frutaTexture;
	sf::Sprite fruta;
	//bool coletada;
	sf::IntRect textureRect;
	sf::Vector2f pos;
	bool coletada;
	std::vector<sf::IntRect> spriteFrutas;
	int contador;

public:
	Fruta(){
		coletada=false;
		//textureRect = sf::IntRect (0, 0, 0, 0);
		pos.x = 0.0;
		pos.y = 0.0;
	}
	Fruta(sf::Vector2f pos) {
		loadTextureFruta();
		setSprite(sf::IntRect(0, 0, 44, 44), pos);
		coletada=false;
		contador = 0;

	};
	void loadTextureFruta() {
		if (!frutaTexture.loadFromFile("assets/frutas.png"))
			std::cerr << "Erro ao carregar a textura do player" << std::endl;
	}
	void setSprite(sf::IntRect textureRect, sf::Vector2f pos) {
		fruta.setTexture(frutaTexture);
		fruta.setTextureRect(textureRect);
		fruta.setPosition(pos);
		fruta.setScale(sf::Vector2f(1, 1));
		fruta.setOrigin(22, 22);
	}
	void printFruta(sf::RenderWindow *window){
		if(coletada==false){
			window->draw(fruta);
		}
	}

	sf::FloatRect retornaHitBoxFruta() {
				sf::FloatRect hitboxFruta = fruta.getGlobalBounds();
				return hitboxFruta;
			}

	void frutaColetada(points::Pontuacao *pontos){
			if(coletada==false){
			pontos->adicionarPontos();
			coletada=true;
			//std::cout<<"foi";
			}
		}
	void resetColetada(){
		coletada=false;
	}
	void setSpriteFrutas(){

		spriteFrutas[0] = sf::IntRect(57,0,43,43); //maca
		spriteFrutas[1] = sf::IntRect(1,53,47,45); //uva
		spriteFrutas[2] = sf::IntRect(56,50,42,46); //abacaxi

		fruta.setTextureRect(spriteFrutas[contador]);

		contador ++;
	}
};
}
#endif /* FRUTA_HPP_ */
