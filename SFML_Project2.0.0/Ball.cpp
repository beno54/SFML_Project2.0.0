#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace std;

//constructeur
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
Ball::Ball() : x_dir(1), y_dir(1), radius(10), e_distance(0), i_indice(NULL)
{
	shape.setRadius(radius);
	shape.setPosition(sf::Vector2f(0, 0));
}
Ball::Ball(int i_indice) : x_dir(1), y_dir(1), radius(10), e_distance(0), i_indice(i_indice)
{
	shape.setRadius(radius);
	shape.setPosition(sf::Vector2f(0, 0));
}

//fonction
sf::Vector2f Ball::getPosition() 
{
	return(shape.getPosition().x, shape.getPosition());
}

void Ball::setRadius(int var)
{
	shape.setRadius(var);
}

void Ball::move(int vitesse)
{
	sf::Vector2f var(vitesse*x_dir, vitesse*y_dir);
	shape.move(var);
}

sf::CircleShape Ball::getShape()
{
	return shape;
}

void Ball::setX_dir(int var)
{
	x_dir = var;
}
void Ball::setY_dir(int var)
{
	y_dir = var;
}

int Ball::getX_dir()
{
	return x_dir;
}
int Ball::getY_dir()
{
	return y_dir;
}
void Ball::setPosition(sf::Vector2f var)
{
	shape.setPosition(var);
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
int Ball::getE_distance()
{
	return e_distance;
}
void Ball::Description()const
{
	printf("Balle %d", i_indice);
}

void Ball::setFillColor(sf::Color color)
{
	shape.setFillColor(color);
}
