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
#include "MiniKangaroo.hpp"
#include "Pontuacao.hpp"
#include "Sino.hpp"

using namespace stairs;
using namespace std;
using namespace berry;
using namespace p1;
using namespace bell;
/*Classe principal do jogo que cria todos os objetos,
 *  inicializa eles e chama todas as funcoes*/
class Jogo {
private:
	//janela
	sf::RenderWindow window;
	sf::Clock frameClock;
	bool paraJogo;
	float delayAtualizar;

	// objetos do jogo
	Pontuacao palavra1;
	Pontuacao palavra2;
	Pontuacao pontos;
	Pontuacao vidas;
	Player jogador;
	MiniKangaroo miniKangaroo;
	Mapa mapa;
	Sino bell;
	Macaco monkey;
	Fruta frutas[3];
	Escada escadas[3];

	//sons
	sf::Music backgroundMusic;
	sf::SoundBuffer bufferVitoria;
	sf::Sound somVitoria;

	void processarEventos() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	void atualizarJogo(float seconds) {
		monkey.moveMacaco(seconds);
		jogador.moveEscada(seconds, escadas);
		jogador.movePlayer(seconds);
		miniKangaroo.movePlayer2(seconds);
		monkey.pegaCanguru(jogador.retornaAndar(), seconds);
		bell.tocouSino(jogador.retornaHitBoxPlayer(), frutas, seconds);
		monkey.atualizaCoco(seconds);

		for (int i = 0; i < 3; i++) {
			jogador.pegaFruta(&frutas[i], &pontos);

		}
	}
	/* Funcao para chamar todas as funcoes de print na janela e atualziar o display*/
	void renderizarObjetos() {
		window.clear(sf::Color::Black); //limpa tela
		mapa.printMapa(&window);

		for (int i = 0; i < 3; i++) {
			frutas[i].printFruta(&window);
		}
		jogador.printPlayer(&window);
		miniKangaroo.printPlayer2(&window);
		monkey.printMacaco(&window);
		palavra1.printText(&window);
		palavra2.printText(&window);
		pontos.printText(&window);
		vidas.printText(&window);
		bell.printSino(&window);
		monkey.printCoco(&window);

		window.display(); //atualiza tela
	}

	void carregaSons() { //carrega som de fundo e som de vitoria
		if (!backgroundMusic.openFromFile("assets/Sounds/BackgroundSong.wav"))
			std::cout << "Erro ao carregar a musica de fundo do jogo"
					<< std::endl;
		backgroundMusic.play();
		backgroundMusic.setVolume(50);
		backgroundMusic.setLoop(true);

		if (!bufferVitoria.loadFromFile("assets/Sounds/SomWin.wav"))
			std::cout << "Erro ao carregar o som da vitoria" << std::endl;

		somVitoria.setBuffer(bufferVitoria);
		somVitoria.setVolume(80.f);

	}

	void Venceu() {
		if (jogador.getPosY() <= 70.0 && paraJogo == false) {

			backgroundMusic.pause();
			sf::Texture textureWin;
			textureWin.loadFromFile("assets/GameWin.png");
			sf::Sprite gameWin;
			gameWin.setTexture(textureWin);
			gameWin.setOrigin(0, 0);
			gameWin.setPosition(0, 0);
			//gameWin.setScale(2, 2);


			window.clear();
			window.draw(gameWin);
			window.display();

			somVitoria.play();
			paraJogo = true;

		}

	}

public:
	Jogo() :
			window(sf::VideoMode(1000, 550), "Kangaroo Atari",
					sf::Style::Close), palavra1("Pontuacao:",
					sf::Vector2f(800, 500)), palavra2("Vidas:",
					sf::Vector2f(10, 500)), pontos(0, sf::Vector2f(920, 500)), vidas(
					3, sf::Vector2f(80, 500)), frutas { Fruta(
					sf::Vector2f(250, 250)), Fruta(sf::Vector2f(700, 310)),
					Fruta(sf::Vector2f(550, 120)) }, escadas { Escada(850, 469),
					Escada(160, 336), Escada(850, 203) }

	{
		paraJogo = false;
		delayAtualizar = 0.0;
		carregaSons();
		pontos.setPontosZero();
		vidas.setVidaMax();

	}
	//loop principal do jogo
	void loopJogo() {
		while (window.isOpen()) {
			sf::Time frameTime = frameClock.restart();
			float seconds = frameTime.asSeconds();

			Venceu();
			processarEventos();

			if (paraJogo == false) {
				atualizarJogo(seconds);
				renderizarObjetos();
				jogador.encostaMacaco(monkey.retornaHitBoxMacaco(),monkey.retornaHitBoxCoco(), &vidas);
			}

		}
	}

};

#endif /* JOGO_HPP_ */
