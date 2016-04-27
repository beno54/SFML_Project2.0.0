#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Ball
{
public:
	// Constructeurs
	Ball(int x_dir, int y_dir, int radius, int i_indice);
	Ball(int radius, int i_indice);
	Ball(int i_indice);
	Ball();

	//fonction
	sf::Vector2f Ball::getPosition() ;

	void Ball::setRadius(int var);
	void Ball::setPosition(sf::Vector2f);
	void Ball::move(int);

	sf::CircleShape Ball::getShape();

	int Ball::getX_dir();
	int Ball::getY_dir();
	int Ball::getE_distance();


	void Ball::setX_dir(int);
	void Ball::setY_dir(int);
	void Ball::setE_distance(int);

	void Ball::inverseX();
	void Ball::inverseY();

	void Ball::Description()const;

private:
	int x_dir, y_dir, radius, e_distance, i_indice;
	sf::CircleShape shape;
};

#endif