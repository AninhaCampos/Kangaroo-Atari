#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "Macaco.hpp"

//#include "Fezes.hpp"

using namespace std;

int main() {
	sf::Clock frameClock;
	sf::RenderWindow window(sf::VideoMode(1000, 550), "Kangaroo Atari",
			sf::Style::Close);
	//window.setFramerateLimit(30);

	sf::Texture playerTexture;
	sf::Texture mapaTexture;
	if (!playerTexture.loadFromFile("assets/kangaroo.png"))
		std::cout << "Erro ao carregar a textura do player" << std::endl;
	if (!mapaTexture.loadFromFile("assets/mapa.png"))
			std::cout << "Erro ao carregar a textura do mapa" << std::endl;

	sf::Sprite mapa;
	mapa.setTexture(mapaTexture);
	mapa.setOrigin(0,0);
	mapa.setPosition(sf::Vector2f(0,0));

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
		window.draw(mapa);
		jogador.printPlayer(&window);
		monkey.printMacaco(&window);

		monkey.moveMacaco(seconds);
		jogador.movePlayer(seconds);
		jogador.puloPlayer(seconds);
		jogador.abaixarPlayer();
		//cout<<seconds;

		window.display();
	}
	return 0;
}
