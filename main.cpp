#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Macaco.hpp"
#include "Fezes.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 768), "Kangaroo Atari",sf::Style::Close);
	window.setFramerateLimit(60);
	Player jogador;
	Macaco monkey;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) {
				window.close();
			}

		window.clear(sf::Color::Black);
		jogador.printPlayer(&window);
		monkey.printMacaco(&window);

		jogador.movePlayer();
		window.display();
	}
	return 0;
}
