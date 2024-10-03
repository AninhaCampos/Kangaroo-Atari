/*
 * Fruta.h
 *
 *  Created on: Sep 30, 2024
 *      Author: Ana Luiza
 */

#ifndef FRUTA_HPP_
#define FRUTA_HPP_
#include "Pontuacao.hpp"
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
public:
	Fruta(){
		coletada=false;
		textureRect = sf::IntRect (0, 0, 0, 0);
		pos.x = 0.0;
		pos.y = 0.0;
	}
	Fruta(sf::IntRect textureRect,sf::Vector2f pos) {
		loadTextureFruta();
		setSprite(textureRect, pos);
		coletada=false;

	};
	void loadTextureFruta() {
		if (!frutaTexture.loadFromFile("assets/Frutas.png"))
			std::cout << "Erro ao carregar a textura do player" << std::endl;
	}
	void setSprite(sf::IntRect textureRect, sf::Vector2f pos) {
		fruta.setTexture(frutaTexture);
		fruta.setTextureRect(textureRect);
		fruta.setPosition(pos);
		fruta.setScale(sf::Vector2f(1, 1));
		fruta.setOrigin(20, 20);
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
			std::cout<<"foi";
			}
		}
};
}
#endif /* FRUTA_HPP_ */
