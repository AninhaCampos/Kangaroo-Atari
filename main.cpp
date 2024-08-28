#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "Macaco.hpp"
//#include "Fezes.hpp"

using namespace std;

int main() {
	sf::Clock frameClock;
	sf::RenderWindow window(sf::VideoMode(640, 768), "Kangaroo Atari",
			sf::Style::Close);
	window.setFramerateLimit(60);

	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("assets/kangaroo.png"))
		std::cout << "Erro ao carregar a textura do player" << std::endl;

	Player jogador(playerTexture);
	Macaco monkey;

	while (window.isOpen()) {
		sf::Time frameTime = frameClock.restart();
		float seconds = frameTime.asSeconds();
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		window.clear(sf::Color::Black);
		jogador.printPlayer(&window);
		monkey.printMacaco(&window);

		monkey.moveMacaco();
		jogador.movePlayer(seconds);
		jogador.puloPlayer(seconds);
		jogador.abaixarPlayer();
		cout<<seconds;

		window.display();
	}
	return 0;
}
