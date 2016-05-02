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
	~Ball();
	//fonction
	sf::Vector2f Ball::getPosition() ;

	void Ball::setRadius(int var);
	int Ball::getRadius();
	void Ball::setPosition(sf::Vector2f);
	void Ball::move(int);
	void Ball::move(int , double , double );

	sf::CircleShape Ball::getShape();

	int Ball::getX_dir();
	int Ball::getY_dir();
	int Ball::getE_distance();


	void Ball::setX_dir(int);
	void Ball::setY_dir(int);
	void Ball::setE_distance(int);
	void Ball::setFillColor(sf::Color);

	void Ball::inverseX();
	void Ball::inverseY();

	void Ball::Description()const;

	static int Ball::nombreInstances();
	static void  Ball::ResetInstances();
	static void  Ball::SetInstances();
	static void  Ball::UnsetInstances();

	void Ball::Initialise(sf::Vector2i, int, int);

private:
	int x_dir, y_dir, radius, e_distance, i_indice;
	sf::CircleShape shape;
	static int compteur;

};

#endif