/*
 * Mapa.hpp
 *
 *  Created on: Sep 30, 2024
 *      Author: Ana Luiza
 */

#ifndef MAPA_HPP_
#define MAPA_HPP_
#include <iostream>

class Mapa {
private:
	sf::Texture mapaTexture;
	sf::Sprite mapa;
public:
	Mapa(){
		loadTextureMap();
		setSprite();
	}
	void loadTextureMap(){
		if (!mapaTexture.loadFromFile("assets/mapa.png"))
		std::cout << "Erro ao carregar a textura do mapa" << std::endl;
	}
	void setSprite(){
		mapa.setTexture(mapaTexture);
		mapa.setOrigin(0, 0);
		mapa.setPosition(sf::Vector2f(0, 0));
	}
	void printMapa(sf::RenderWindow *window){
		window->draw(mapa);
	}
};

#endif /* MAPA_HPP_ */
