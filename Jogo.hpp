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
using namespace primata;
/*Classe principal do jogo que cria todos os objetos,
 *  inicializa eles e chama todas as funcoes*/
class Jogo {
private:
	//janela
	sf::RenderWindow window;
	sf::Clock frameClock;
	sf::Texture monkeyTexture;

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
	Fruta frutas[3];
	Escada escadas[3];
	float tempoSpawnMacaco;
	vector<Macaco> monkey;
	sf::SoundBuffer bufferDerrota;
	sf::Sound somDerrota;


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
	void loadTextureMacaco() {
			if (!monkeyTexture.loadFromFile("assets/macaco.png"))
				std::cout << "Erro ao carregar a textura do macaco" << std::endl;
		}

	void atualizarJogo(float seconds) {

		tempoSpawnMacaco += seconds;
		        if(tempoSpawnMacaco >= 1){
		            Macaco newMacaco(&monkeyTexture);
		            monkey.push_back(newMacaco);
		            tempoSpawnMacaco = 0;
		        }
		        for(unsigned int i = 0 ; i < monkey.size();){
		            monkey[i].moveMacaco(seconds);
		            monkey[i].pegaCanguru(jogador.retornaAndar(), seconds);
		            monkey[i].atualizaCoco(seconds);
		            jogador.encostaMacaco(&monkey[i], &vidas);
		           if( monkey[i].morreMacaco(jogador.retornaHitBoxPlayer())){
		        	   monkey.erase(monkey.begin()+i);
		           }

		            sf::Vector2f posMacaco = monkey[i].retornaPosMacaco();

		            if(posMacaco.x >= 1000){
		                monkey.erase(monkey.begin() + i); //remove apenas o macaco que passou da tela na pos x
		                std::cout << "macaco saiu da tela e foi excluido !";
		            }else{
		                i++; //avanca para o prox macaco apenas se nenhum for removido
		            }
		        }


		jogador.moveEscada(seconds, escadas);
		jogador.movePlayer(seconds);
		miniKangaroo.movePlayer2(seconds);
		bell.tocouSino(jogador.retornaHitBoxPlayer(), frutas, seconds);
		jogador.socoKangaroo(seconds);




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
	        for(unsigned int i = 0; i<monkey.size();i++){

	            monkey[i].printMacaco(&window);
	            monkey[i].printCoco(&window);
	        }
	        jogador.printPlayer(&window);
	        miniKangaroo.printPlayer2(&window);
	        palavra1.printText(&window);
	        palavra2.printText(&window);
	        pontos.printText(&window);
	        vidas.printText(&window);
	        bell.printSino(&window);


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
		if (!bufferDerrota.loadFromFile("assets/Sounds/SomDefeat.wav"))
		                    std::cout << "Erro ao carregar o som da derrota" << std::endl;

		                somDerrota.setBuffer(bufferDerrota);
		                somDerrota.setVolume(100.f);


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

	void Perdeu() {
	            if (vidas.getVidas() <= 0) {

	                backgroundMusic.pause();
	                sf::Texture textureDefeat;
	                textureDefeat.loadFromFile("assets/GameDefeat.png");
	                sf::Sprite gameDefeat;
	                gameDefeat.setTexture(textureDefeat);
	                gameDefeat.setOrigin(0, 0);
	                gameDefeat.setPosition(0, 0);
	                //gameWin.setScale(2, 2);


	                window.clear();
	                window.draw(gameDefeat);
	                window.display();

	                somDerrota.play();
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
		tempoSpawnMacaco=0;
		loadTextureMacaco();

	}
	//loop principal do jogo
	void loopJogo() {
		while (window.isOpen()) {
			sf::Time frameTime = frameClock.restart();
			float seconds = frameTime.asSeconds();

			Venceu();
			Perdeu();
			processarEventos();

			if (paraJogo == false) {
				atualizarJogo(seconds);
				renderizarObjetos();

			}

		}
	}

};

#endif /* JOGO_HPP_ */
