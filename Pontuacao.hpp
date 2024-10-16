/*
 * Pontuacao.h
 *
 *  Created on: Oct 1, 2024
 *      Author: Ana Luiza
 */

#ifndef PONTUACAO_HPP_
#define PONTUACAO_HPP_

#include <string>
#include <cmath>

namespace points{
class Pontuacao {
private:
	sf::Font fonte;
	sf::Text texto;
	int pontos;
	std::string palavra;
	sf::Vector2f pos;
	int vidas;

public:
	Pontuacao() { //Construtor padrao
		pontos = 0;
		pos.x = 0.0;
		pos.y = 0.0;
		vidas = 3;
	}
	Pontuacao(std::string palavra, sf::Vector2f pos){
		if (!fonte.loadFromFile("assets/Fonts/AtariSmall.ttf"))
			std::cout << "Erro ao carregar a fonte do jogo" << std::endl;
		texto.setFont(fonte);
		texto.setString(palavra);
		texto.setCharacterSize(22);
		setPosition(pos);
		vidas = 3;
	};

	Pontuacao(int pontos,sf::Vector2f pos){
		if (!fonte.loadFromFile("assets/Fonts/AtariSmall.ttf"))
			std::cout << "Erro ao carregar a fonte do jogo" << std::endl;
		texto.setFont(fonte);
		texto.setString(std::to_string(pontos));
		texto.setCharacterSize(22);
		setPosition(pos);
	};
	void setPosition(sf::Vector2f pos){
		texto.setPosition(pos);
	}
	void printText(sf::RenderWindow *window){
		window->draw(texto);
	}
	void setPontosZero(){
		pontos = 0;
	}
	void adicionarPontos(int multiplicador){
		pontos += 100 * std::pow(2,multiplicador);
		texto.setString(std::to_string(pontos));
	}

	void setVidaMax(){
		vidas = 3;
	}

	void perdeVida(){
		vidas--;
		texto.setString(std::to_string(vidas));
	}

	int getVidas(){
	        return vidas;
	    }

};
}
#endif /* PONTUACAO_HPP_ */
