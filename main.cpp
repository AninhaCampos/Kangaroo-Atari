#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Mapa.hpp"
#include "Player.hpp"
#include "Macaco.hpp"
#include "Escada.hpp"
#include "Fruta.hpp"
#include "Pontuacao.hpp"

//#include "Fezes.hpp"
using namespace stairs;
using namespace std;

int main() {
	sf::Clock frameClock;
	sf::RenderWindow window(sf::VideoMode(1000, 550), "Kangaroo Atari",
			sf::Style::Close);
	//window.setFramerateLimit(30);

	Pontuacao palavra1("Pontuacao:",sf::Vector2f(800,500));
	Pontuacao palavra2("Vidas:", sf::Vector2f(10,500));
	Pontuacao pontos(0,sf::Vector2f(920,500));
	Pontuacao vidas(3,sf::Vector2f(80,500));
	Player jogador;
	Mapa mapa;
	Macaco monkey;
	Fruta morango(sf::IntRect(0, 32, 43, 40), sf::Vector2f(700, 120));
	Fruta apple(sf::IntRect(54, 30, 46, 44), sf::Vector2f(250, 250));
	Escada escada[3] = { Escada(850, 469), Escada(160, 336), Escada(850, 203) };

	while (window.isOpen()) {
		sf::Time frameTime = frameClock.restart();
		float seconds = frameTime.asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		window.clear(sf::Color::Black);
		mapa.printMapa(&window);
		jogador.printPlayer(&window);
		monkey.printMacaco(&window);
		morango.printFruta(&window);
		apple.printFruta(&window);
		palavra1.printText(&window);
		palavra2.printText(&window);
		pontos.printText(&window);
		vidas.printText(&window);

		monkey.moveMacaco(seconds);
		jogador.movePlayer(seconds);
		jogador.moveEscada(seconds, escada);

		//cout<<seconds;

		window.display();
	}
	return 0;
}
