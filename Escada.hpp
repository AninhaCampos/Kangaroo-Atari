#ifndef ESCADA_HPP_
#define ESCADA_HPP_
namespace stairs {
class Escada {
private:
	float largura, altura;
	sf::Vector2f pos;
	sf::RectangleShape escada;
	sf::RectangleShape patamarEscada;
public:
	Escada() {
		pos.x = 0;
		pos.y = 0;
		altura = 0;
		largura = 0;

	}  // Construtor padrão
	Escada(float x, float y) {
		pos.x = x;
		pos.y = y;
		largura = 20;
		altura = 133;
		escada.setSize(sf::Vector2f(largura, altura));
		escada.setFillColor(sf::Color::Blue);
		escada.setOrigin(largura / 2, altura);
		escada.setPosition(pos);

		patamarEscada.setSize(sf::Vector2f(20, 10));
		patamarEscada.setOrigin(10,10);
		patamarEscada.setPosition(pos.x,pos.y-altura);
		patamarEscada.setFillColor(sf::Color::Red);

	}

	sf::FloatRect retornaHitBox() {
		sf::FloatRect bounds = escada.getGlobalBounds();
		return bounds;
	}

	sf::FloatRect retornaHitBoxPatamar(){
		sf::FloatRect boundsPatamar = patamarEscada.getGlobalBounds();
		return boundsPatamar;
	}

	void printEscada(sf::RenderWindow *window) {
		window->draw(escada);
		window->draw(patamarEscada);
	}

	int getAlturaEscada() {
		return pos.y;
	}
};

}

#endif /* ESCADA_HPP_ */
