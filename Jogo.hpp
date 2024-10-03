/*
 * Game.hpp
 *
 *  Created on: Oct 1, 2024
 *      Author: Ana Luiza
 */

#ifndef JOGO_HPP_
#define JOGO_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Mapa.hpp"
#include "Player.hpp"
#include "Macaco.hpp"
#include "Escada.hpp"
#include "Fruta.hpp"
#include "Pontuacao.hpp"
using namespace stairs;
using namespace std;
using namespace berry;

class Jogo {
private:
	//janela
	sf::RenderWindow window;
	sf::Clock frameClock;

	// Objetos do jogo
	Pontuacao palavra1;
	Pontuacao palavra2;
	Pontuacao pontos;
	Pontuacao vidas;
	Player jogador;
	Mapa mapa;
	Macaco monkey;
	Fruta morango;
	Fruta apple;
	Escada escadas[3];
	sf::Music backgroundMusic;

	void processarEventos() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	//em andamento
	/*void verificarColisoes() {
	 if (jogador.verificaColisaoComFruta(morango)) {
	 pontos.adicionarPontos(200);
	 }
	 if (jogador.verificaColisaoComFruta(apple)) {
	 pontos.adicionarPontos(200);
	 }
	 }*/

	void atualizarJogo(float seconds) {
		monkey.moveMacaco(seconds);
		jogador.movePlayer(seconds);
		jogador.moveEscada(seconds, escadas);
	}

	void renderizarObjetos() {
		window.clear(sf::Color::Black); //limpa tela

		mapa.printMapa(&window);
		jogador.printPlayer(&window);
		monkey.printMacaco(&window);
		morango.printFruta(&window);
		apple.printFruta(&window);
		palavra1.printText(&window);
		palavra2.printText(&window);
		pontos.printText(&window);
		vidas.printText(&window);

		window.display(); //atualiza tela
	}
	void carregaSons() {
		if (!backgroundMusic.openFromFile("assets/Sounds/BackgroundSong.wav"))
					std::cout << "Erro ao carregar a fonte do jogo" << std::endl;
			backgroundMusic.play();
			backgroundMusic.setVolume(50);
			backgroundMusic.setLoop(true);
		}
	public:
		Jogo() :
		window(sf::VideoMode(1000, 550), "Kangaroo Atari", sf::Style::Close),
		palavra1("Pontuacao:", sf::Vector2f(800, 500)),
		palavra2("Vidas:", sf::Vector2f(10, 500)),
		pontos(0, sf::Vector2f(920, 500)),
		vidas(3, sf::Vector2f(80, 500)),
		morango(sf::IntRect(0, 32, 43, 40), sf::Vector2f(700, 120)),
		apple(sf::IntRect(54, 30, 46, 44), sf::Vector2f(250, 250)),
		escadas {Escada(850, 469), Escada(160, 336), Escada(850, 203)}

		{
			carregaSons();
			pontos.setPontosZero();
		}
		//loop principal do jogo
		void loopJogo() {
			while (window.isOpen()) {
				sf::Time frameTime = frameClock.restart();
				float seconds = frameTime.asSeconds();

				processarEventos();
				//verificarColisoes();
				atualizarJogo(seconds);
				renderizarObjetos();
				jogador.pegaFruta(&apple,&pontos);
			}
		}

	};

#endif /* JOGO_HPP_ */
