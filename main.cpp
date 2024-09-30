#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Mapa.hpp"
#include "Player.hpp"
#include "Macaco.hpp"
#include "Escada.hpp"
//#include "Fezes.hpp"
using namespace stairs;
using namespace std;

int main() {
	sf::Clock frameClock;
	sf::RenderWindow window(sf::VideoMode(1000, 550), "Kangaroo Atari",
			sf::Style::Close);
	//window.setFramerateLimit(30);


	std::vector<sf::IntRect> rising = { sf::IntRect(2, 0, 100, 93), sf::IntRect(110, 103, 120, 90) };
	std::vector<sf::IntRect> down = { sf::IntRect(2, 0, 100, 93), sf::IntRect(110, 103, 120, 90), sf::IntRect(104, 0, 115, 90) };

	Player jogador;
	Mapa mapa;
	Macaco monkey;
	Escada escada[3]= { Escada(850, 469), Escada(160, 469-133), Escada(850, 469-266) };

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
		monkey.moveMacaco(seconds);
		jogador.movePlayer(seconds);
		jogador.moveEscada(seconds, escada);

		//cout<<seconds;

		window.display();
	}
	return 0;
}
