#ifndef PEDRA_HPP_
#define PEDRA_HPP_

class Pedra {
private:
	sf::Vector2f pos;
	sf::RectangleShape pedra;
	int velX, velY;

public:
	Pedra() {

		this -> pos.x = 80;
		this -> pos.y = 70;

		pedra.setSize(sf::Vector2f(5, 5));
		pedra.setFillColor(sf::Color::Yellow);
		pedra.setOrigin(2.5, 2.5);
		pedra.setPosition(pos );
		velX=70;
		velY=0;
	}
	void printPedra(sf::RenderWindow *window) {

		window->draw(pedra);

	}

	void movePedra(float tempo){
		pos.x += tempo * velX;
		pos.y += tempo * velY;
		pedra.setPosition(pos);

	}

	void caiPlayer(float posxPlayer){
		if(pos.x>=posxPlayer){
			velX=0;
			velY=180;



		}
		testaPedra();
	}

	sf::FloatRect retornaHitBox(){
		return pedra.getGlobalBounds();
	}

	void resetPedra(){
		pos.x=80;
		pos.y=70;

		velX=150;
		velY=0;

	}

	void testaPedra(){
		if (pos.y >= 550 || pos.x>898){
			resetPedra();
		}
	}





};

#endif /* FEZES_HPP_ */
