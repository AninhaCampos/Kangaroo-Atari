/*
 * Fruta.h
 *
 *  Created on: Sep 30, 2024
 *      Author: Ana Luiza
 */

#ifndef FRUTA_HPP_
#define FRUTA_HPP_

class Fruta {
private:
	sf::Texture frutaTexture;
	sf::Sprite fruta;
public:
	Fruta(sf::IntRect textureRect,sf::Vector2f pos) {
		loadTextureFruta();
		setSprite(textureRect, pos);

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
		window->draw(fruta);
	}
};

#endif /* FRUTA_HPP_ */
