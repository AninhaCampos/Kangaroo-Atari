/*
 * Kangaroo.hpp
 *
 *  Created on: Aug 23, 2024
 *      Author: Ana Luiza
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <iostream>
#include "Escada.hpp"
#include "Fruta.hpp"
#include "Pontuacao.hpp"
#include "Sino.hpp"
#include "MiniKangaroo.hpp"
#include "Macaco.hpp"

/*namespaces para facilitar o uso de
 * funcoes/variaveis de diferentes classes
 * em diferentes arquivos*/

using namespace stairs;
using namespace berry;
using namespace points;
using namespace bell;
using namespace filhote;
namespace p1 {
/*Classe para definir posicao inicial do player,
 * textura, som, e funcoes de movimentacao do jogador*/

class Player {
private:

	float velX;
	float tempoPulo;
	float delayPulo;
	float tempoAnimacao;
	float tempoSoco;

	bool pulo;
	bool abaixado;
	bool subindoEscada;
	bool verificaAbaixado;
	bool naopodePular;
	bool socando;



	sf::Vector2f pos;
	sf::Sprite player;
	sf::Texture playerTexture;
	std::vector<sf::IntRect> rightPlayer;
	std::vector<sf::IntRect> leftPlayer;
	std::vector<sf::IntRect> upPlayer;
	std::vector<sf::IntRect> lowerPlayer;
	std::vector<sf::IntRect> stairsPlayer;
	sf::SoundBuffer bufferJump;
	sf::Sound somJump;

public:

	Player() {
		loadTexturePlayer();
		setSprite();
		setAnimation();
		carregaSomJump();
		pos.x = 125;
		pos.y = 468;
		delayPulo = 0;
		velX = 300;
		pulo = false;
		tempoPulo = 0.0;
		abaixado = false;
		tempoAnimacao = 0;
		subindoEscada = false;
		verificaAbaixado = false;
		naopodePular = false;
		socando=false;
		tempoSoco = 0;

	}
	void loadTexturePlayer() {
		if (!playerTexture.loadFromFile("assets/personagem.png"))
			std::cout << "Erro ao carregar a textura do player" << std::endl;
	}
	void setSprite() {
		player.setTexture(playerTexture);
		player.setTextureRect(sf::IntRect(0, 0, 27, 26));
		player.setPosition(pos);
		player.setScale(sf::Vector2f(2, 2));
		player.setOrigin(13.5, 26);
	}
	void setAnimation() {
		rightPlayer = { sf::IntRect(0, 0, 27, 26), sf::IntRect(27, 0, 27, 26) };
		leftPlayer = { sf::IntRect(106, 27, 26, 26), sf::IntRect(133, 27, 27,
				26) };
		upPlayer = { sf::IntRect(132, 0, 26, 26), sf::IntRect(107, 0, 25, 26) };
		lowerPlayer =
				{ sf::IntRect(55, 0, 25, 26), sf::IntRect(80, 10, 26, 16) };
		stairsPlayer = { sf::IntRect(162, 27, 18, 26), sf::IntRect(181, 27, 18,
				26) };

	}
	//desenha player
	void printPlayer(sf::RenderWindow *window) {
		window->draw(player);
	}
	void carregaSomJump() {
		if (!bufferJump.loadFromFile("assets/Sounds/SomPular.wav")) {
			std::cout << "Erro ao carregar o som do pulo" << std::endl;
		}
		somJump.setBuffer(bufferJump);
		somJump.setVolume(10.f);
	}
	/*funcao para verificar se o jogador esta na escada
	 * e limitar sua movimentacao apenas em Y*/

	void moveEscada(float tempo, Escada vetorEscadas[]) {
		if (testaHitboxPatamar(vetorEscadas)
				|| testaHitboxEscada(vetorEscadas)) {
			descerEscada(tempo, vetorEscadas[0].getAlturaEscada(),
					vetorEscadas[1].getAlturaEscada(),
					vetorEscadas[2].getAlturaEscada(), vetorEscadas,
					stairsPlayer);

		} else {

			naopodePular = false;
			subindoEscada = false;
		}

		if (testaHitboxEscada(vetorEscadas)) {
			naopodePular = true;
			if (pulo == true) {
				pos.y = pos.y + 30;
				pulo = false;
			}

			subirEscada(tempo, vetorEscadas[0].getAlturaEscada(), stairsPlayer);

			descerEscada(tempo, vetorEscadas[0].getAlturaEscada(),
					vetorEscadas[1].getAlturaEscada(),
					vetorEscadas[2].getAlturaEscada(), vetorEscadas,
					stairsPlayer);
		} else {

			naopodePular = false;
			subindoEscada = false;
		}
	}
	/*Funcao de movimentacao: verifica se o player esta ou nao na escada.
	 * caso esteja: pode andar apenas em Y
	 * caso nao esteja: pode andar apenas em X*/
	void movePlayer(float tempo) {

		if (subindoEscada == false) {

			andarDireita(tempo, rightPlayer);
			andarEsquerda(tempo, leftPlayer);
			if (naopodePular == false) {
				pular(tempo, upPlayer, rightPlayer);
			}
			abaixar(tempo, lowerPlayer, rightPlayer);

		}
	}

	//Funcoes chamadas dentro da movePlayer
	void andarDireita(float tempo, std::vector<sf::IntRect> right) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (pulo == false) {
				tempoAnimacao += tempo;
				if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
					player.setTextureRect(right[0]);
				} else if (tempoAnimacao > 0.3) {
					player.setTextureRect(right[1]);
					tempoAnimacao = 0;
				}
			}
			if (abaixado == false) {
				if (pos.x <= 898 - (player.getGlobalBounds().width / 2)) {
					pos.x += velX * tempo;
					player.setPosition(pos);

				}
			}
		}
	}
	void andarEsquerda(float tempo, std::vector<sf::IntRect> left) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (pulo == false) {
				tempoAnimacao += tempo;
				if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
					player.setTextureRect(left[0]);
				} else if (tempoAnimacao > 0.3) {
					player.setTextureRect(left[1]);
					tempoAnimacao = 0;
				}
			}
			if (abaixado == false) {
				if (pos.x >= 102 + (player.getGlobalBounds().width / 2)) {
					pos.x -= velX * tempo;
					player.setPosition(pos);
				}
			}
		}
	}
	void pular(float tempo, std::vector<sf::IntRect> up,
			std::vector<sf::IntRect> right) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

			if (delayPulo > 0.2) {
				if (abaixado == false) {
					if (pulo == false) {
						std::cout << pos.y << std::endl;
;						somJump.play();
						pos.y -= 30;
						tempoPulo = 0;
						pulo = true;
						tempoAnimacao = 0;

					}
				}
			}
		}
		if (pulo == true) {
			tempoAnimacao += tempo;
			if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
				player.setTextureRect(up[0]);
			} else if (tempoAnimacao > 0.3) {
				player.setTextureRect(up[1]);
				tempoAnimacao = 0;
			}
		}
		tempoPulo += tempo;
		delayPulo += tempo;
		if (pulo == true) {
			if (tempoPulo > 0.5) {
				pos.y += 30;

				pulo = false;
				delayPulo = 0;
				player.setTextureRect(right[0]);
			}

		}
		player.setPosition(pos);
	}
	void abaixar(float tempo, std::vector<sf::IntRect> lower,
			std::vector<sf::IntRect> right) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {




			if (pulo == false) {
				if(naopodePular){
					player.setTextureRect(lower[0]);
				}else{
				player.setTextureRect(lower[1]);
				player.setPosition(pos.x,pos.y+20);
				}
				//player.setScale(sf::Vector2f(2, 1));
				//std::cout<<"baixado";
				abaixado = true;
				verificaAbaixado = true;

			}
		} else {
			if (verificaAbaixado == true) {

				player.setTextureRect(right[0]);
				verificaAbaixado = false;
			}
			//std::cout<<"nao baixado";
			//player.setScale(sf::Vector2f(2, 2));
			abaixado = false;
		}

	}
	void subirEscada(float tempo, int alturaEscada,
			std::vector<sf::IntRect> stairsPlayer) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

			//subindoEscada = false;
			tempoAnimacao += tempo;
			if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
				player.setTextureRect(stairsPlayer[0]);
			} else if (tempoAnimacao > 0.3) {
				player.setTextureRect(stairsPlayer[1]);
				tempoAnimacao = 0;
			}

			pos.y -= 100 * tempo;
			subindoEscada = true;

			player.setPosition(pos);

		}
	}
	void descerEscada(float tempo, int alturaEscada1, int alturaEscada2,
			int alturaEscada3, Escada vetorEscadas[],
			std::vector<sf::IntRect> stairsPlayer) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if(abaixado==false){
			tempoAnimacao += tempo;
			if (tempoAnimacao > 0.1 && tempoAnimacao < 0.2) {
				player.setTextureRect(stairsPlayer[0]);
			} else if (tempoAnimacao > 0.3) {
				player.setTextureRect(stairsPlayer[1]);
				tempoAnimacao = 0;
			}
			if (testaHitboxPatamar(vetorEscadas)) {
				pos.y += 30 * tempo;
				subindoEscada = true;
				player.setPosition(pos);

			} else if ((pos.y >= alturaEscada1)
					|| (pos.y >= alturaEscada2 && pos.y <= alturaEscada2 + 5)
					|| (pos.y >= alturaEscada3 && pos.y <= alturaEscada3 + 5)) {
				subindoEscada = false;
			} else {
				pos.y += 30 * tempo;
				subindoEscada = true;
				player.setPosition(pos);

			}
			}
		}
	}
//Funcoes chamadas dentro da moveEscada
	bool testaHitboxEscada(Escada vetorEscadas[]) {
		bool encostouEscada = vetorEscadas[0].retornaHitBox().intersects(
				player.getGlobalBounds())
				|| vetorEscadas[1].retornaHitBox().intersects(
						player.getGlobalBounds())
				|| vetorEscadas[2].retornaHitBox().intersects(
						player.getGlobalBounds());
		return encostouEscada;
	}
	bool testaHitboxPatamar(Escada vetorEscadas[]) {
		bool encostouPatamar =
				vetorEscadas[0].retornaHitBoxPatamar().intersects(
						player.getGlobalBounds())
						|| vetorEscadas[1].retornaHitBoxPatamar().intersects(
								player.getGlobalBounds())
						|| vetorEscadas[2].retornaHitBoxPatamar().intersects(
								player.getGlobalBounds());
		return encostouPatamar;
	}

	/*Funcao para verificar se o player encostou na fruta e adicionar os pontos*/
	void pegaFruta(Fruta *fruta, Pontuacao *pontos) {
		if (player.getGlobalBounds().intersects(fruta->retornaHitBoxFruta())) {
			fruta->frutaColetada(pontos);

		} else {

		}
	}

	int retornaAndar() { //Funcao para saber em que andar o player esta
		if (pos.y < 470 && pos.y > 340) {
			return 1;
		} else if (pos.y < 340 && pos.y > 205) {
			return 2;
		} else if (pos.y < 205) {
			return 3;
		} else {
			return 0;
		}

	}

	sf::FloatRect retornaHitBoxPlayer() { // retorna a hitbox do player para usar na funcao
		sf::FloatRect hitboxPlayer = player.getGlobalBounds();
		return hitboxPlayer;
	}
	/*Funcao que verifica se o player encostou no macaco.
	 * Caso encoste ele perde uma vida*/
	void encostaMacaco(primata::Macaco *monkey, points::Pontuacao *vidas) {
		if ((player.getGlobalBounds().intersects(monkey->retornaHitBoxMacaco()) && socando==false) || player.getGlobalBounds().intersects(monkey->retornaHitBoxCoco()) ) {
			vidas->perdeVida();
			pos.x = 125;
			pos.y = 468;
			monkey->someCoco(player.getGlobalBounds());
			player.setPosition(pos);


		}

	}

	float getPosY(){
		return pos.y;
	}

	void socoKangaroo(float tempo){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (subindoEscada==false){
			socando=true;
			tempoSoco=0;
			std::cout<<"socando";
		}
		}

		tempoSoco += tempo;
		if(tempoSoco>0.5){
			socando=false;
		}


	}
};
}

#endif /* PLAYER_HPP_ */
