#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace std;

//STATIC VAR 
int Ball::compteur = 0; 

//CONSTRUCTOR
Ball::Ball(int x_dir, int y_dir, int radius, int i_indice) : x_dir(x_dir), y_dir(y_dir), e_distance(0), i_indice(i_indice)
{
	shape.setRadius(radius);
	shape.setPosition(sf::Vector2f(0,0));
}
Ball::Ball(int radius, int i_indice) : x_dir(1), y_dir(1), e_distance(0), i_indice(i_indice)
{
	shape.setRadius(radius);
	shape.setPosition(sf::Vector2f(0, 0));
}
Ball::Ball() : x_dir(-1), y_dir(1), radius(10), e_distance(0), i_indice(NULL)
{ 
	shape.setRadius(radius);
	shape.setPosition(sf::Vector2f(0, 0));
}
Ball::Ball(int i_indice) : x_dir(1), y_dir(1), radius(10), e_distance(0), i_indice(i_indice)
{
	shape.setRadius(radius);
	shape.setPosition(sf::Vector2f(0, 0));
}

//DESTRUCTOR
Ball::~Ball()
{
	--compteur;  //Et on enlève 1 au compteur lors de la destruction
}

//FONCTIONS
	//FONCTIONS APPLICABLE SUR LA VARIABLE CircleShape DE L INSTANCE
void Ball::move(int vitesse)
{
	sf::Vector2f var(vitesse*x_dir, vitesse*y_dir);
	shape.move(var);
}
void Ball::move(int vitesse, double coeff_x, double coeff_y)
{
	sf::Vector2f var(vitesse*x_dir*coeff_x, vitesse*y_dir*coeff_y);
	shape.move(var);
}
void Ball::setPosition(sf::Vector2f var)
{
	shape.setPosition(var);
}
void Ball::setRadius(int var)
{
	radius = var;
	shape.setRadius(radius);
}
void Ball::setFillColor(sf::Color color)
{
	shape.setFillColor(color);
}

	//SETTER
void Ball::setX_dir(int var)
{
	x_dir = var;
}
void Ball::setY_dir(int var)
{
	y_dir = var;
}
void Ball::inverseX()
{
	x_dir = -x_dir;
}
void Ball::inverseY()
{
	y_dir = -y_dir;
}
void Ball::setE_distance(int var)
{
	e_distance = var;
}

	//GETTER
sf::Vector2f Ball::getPosition() 
{
	return(shape.getPosition().x, shape.getPosition());
}
int Ball::getRadius()
{
	return radius;
}
sf::CircleShape Ball::getShape()
{
	return shape;
}
int Ball::getX_dir()
{
	return x_dir;
}
int Ball::getY_dir()
{
	return y_dir;
}
int Ball::getE_distance()
{
	return e_distance;
}
void Ball::Description()const
{
	printf("Balle %d", i_indice);
}


	//FONCTIONS SUR LE COMPTEUR D INSTANCES
int Ball::nombreInstances()
{
	return compteur;   
}
void  Ball::ResetInstances()
{
	compteur = 0;
}
void  Ball::SetInstances()
{
	++compteur;
}
void  Ball::UnsetInstances()
{
	--compteur;
}

	//FONCTIONS INITIALISATION
void Ball::Initialise(sf::Vector2i localPosition, int SHAPE_RADIUS, int var)
{
	x_dir = 1;
	y_dir = 1;
	radius = SHAPE_RADIUS;
	e_distance = 0; 
	i_indice = var;
	shape.setRadius(radius);
	shape.setFillColor(sf::Color(localPosition.y % 245, localPosition.x % 245, (localPosition.y + localPosition.x) % 245));
	shape.setPosition(sf::Vector2f(localPosition));
}