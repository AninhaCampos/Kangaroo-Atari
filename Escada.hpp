#ifndef ESCADA_HPP_
#define ESCADA_HPP_

class Escada{
public:
	float largura, altura;
	sf::Vector2f pos;
	sf::RectangleShape escada;

	Escada (float x,float y) {
		pos.x = x;
		pos.y = y;
		largura=51;
		altura=133;
		escada.setSize(sf::Vector2f(largura, altura));
		escada.setFillColor(sf::Color::Blue);
		escada.setOrigin(largura/2, altura);
		escada.setPosition(pos);

	}

	sf::FloatRect retornaHitBox(){
		sf::FloatRect bounds = escada.getGlobalBounds();
		return bounds;
	}

	void printEscada(sf::RenderWindow *window){
		window->draw(escada);

	}
};






















#endif /* ESCADA_HPP_ */
