/*
 * Pontuacao.h
 *
 *  Created on: Oct 1, 2024
 *      Author: Ana Luiza
 */

#ifndef PONTUACAO_HPP_
#define PONTUACAO_HPP_

#include <string>

class Pontuacao {
private:
	sf::Font fonte;
	sf::Text texto;
	int pontos;
	std::string palavra;
	sf::Vector2f pos;

public:
	Pontuacao() { //Construtor padrao
		pontos = 0;
		pos.x = 0.0;
		pos.y = 0.0;
	}
	Pontuacao(std::string palavra, sf::Vector2f pos){
		if (!fonte.loadFromFile("assets/Fonts/AtariSmall.ttf"))
			std::cout << "Erro ao carregar a fonte do jogo" << std::endl;
		texto.setFont(fonte);
		texto.setString(palavra);
		texto.setCharacterSize(22);
		setPosition(pos);
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
	/*void adicionarPontos(int *pontos){
		pontos += 200;
	}*/
};

#endif /* PONTUACAO_HPP_ */
