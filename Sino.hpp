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
namespace bell {
class Sino {
private:
	sf::Texture sinoTexture;
	sf::Sprite sino;
	sf::IntRect rightSino;
	sf::IntRect normalSino;
	sf::IntRect leftSino;
	sf::Vector2f pos;
	float tempoAnimacao;
	bool tocado;
	int spriteFruta;
	float tempoContado;
	int quantidadeMaxima;
	sf::SoundBuffer bufferSino;
	sf::Sound somSino;

public:
	Sino() {
		pos.x = 750;
		pos.y = 120;
		tocado = false;
		setAnimation();
		loadTextureSino();
		setSprite();
		carregaSomSino();
		spriteFruta = 0;
		quantidadeMaxima = 0;
		tempoAnimacao = 0;
		//int tempoContado=0;

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
		if (quantidadeMaxima != 3) {
			window->draw(sino);
		}
	}
	sf::FloatRect retornaHitBoxSino() {
		sf::FloatRect hitboxSino = sino.getGlobalBounds();
		return hitboxSino;
	}

	void tocouSino(sf::FloatRect player, Fruta frutas[], float tempo) {

		//std::cout<<tempoContado<<";";
		if (retornaHitBoxSino().intersects(player) && tocado == false
				&& quantidadeMaxima != 3) {

			somSino.play();

			for (int i = 0; i < 3; i++) {
				frutas[i].setSpriteFrutas();
				frutas[i].resetColetada();

			}

			spriteFruta++;
			tocado = true;
			tempoContado = 0;
			quantidadeMaxima++;

		}
		tempoContado = tempo + tempoContado;

		if (tempoContado < 2 && tocado == true) { //anima sino
			animacaoSino(tempo);

		} else {
			sino.setTextureRect(normalSino);
		}

		if (tempoContado >= 3) {
			tocado = false;
		}

	}
	void animacaoSino(float tempo) {
		tempoAnimacao += tempo;

		if (tempoAnimacao > 0.1 && tempoAnimacao < 0.3) {
			sino.setTextureRect(rightSino);
		} else if (tempoAnimacao >= 0.3 && tempoAnimacao < 0.5) {
			sino.setTextureRect(leftSino);
		} else if (tempoAnimacao >= 0.5 && tempoAnimacao < 0.7) {
			sino.setTextureRect(rightSino);
		} else if (tempoAnimacao >= 0.7 && tempoAnimacao < 1.0) {
			sino.setTextureRect(leftSino);
		} else if (tempoAnimacao > 1.0) {
			tempoAnimacao = 0;
		}
	}
	void carregaSomSino() {
		if (!bufferSino.loadFromFile("assets/Sounds/Sino.wav")) {
			std::cout << "Erro ao carregar o som do sino" << std::endl;
		}
		somSino.setBuffer(bufferSino);
	}

};
}
#endif /* SINO_HPP_ */
