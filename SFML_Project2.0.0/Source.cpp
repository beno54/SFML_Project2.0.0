#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Ball.h"

#define NB_SHAPE_TOT  200
#define SCREEN_HIGH 1080
#define SCREEN_LENGTH 1920
#define SHAPE_RADIUS 10

/*DOIT ETRE > 2 VOIR 3 POUR EVITER TOUT PB DU AUX COLLISIONS SIMULTANEES */
#define NB_SHAPE_RADIUS_BETWEEN_BALL 3

#define COEFF_DIR_X 0.48
#define COEFF_DIR_Y 0.65
#define VITESSE 8

void init_shape(Ball*, sf::Vector2i );
void Detection_collision(Ball*, int i);
void Detection_bord(Ball*);

int main()
{
	//RESERVATION DE LA MEMOIRE ET CREATION DES VARIABLES
	sf::RenderWindow window(sf::VideoMode(SCREEN_LENGTH, SCREEN_HIGH), "SFML works!", sf::Style::Fullscreen);
	int i = 0, e = 0;
	bool Position_free = true;
	Ball * corps = new Ball[NB_SHAPE_TOT];

	//CONTROL ED LA FENETRE ET MISE A 0 DU NOMRBE D INSTANCES DE BALL
	Ball::ResetInstances();
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	//LANCEMENT DE LA FENETRE
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		
		//BOUCLE ACTION CLICK GAUCHE
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			for (int i = 0; i < Ball::nombreInstances(); i++)
			{ 
				double distance = sqrt(pow(corps[i].getPosition().x - localPosition.x, 2) + pow(corps[i].getPosition().y - localPosition.y, 2));

				// TEST SI POSITION LIBRE 
				if (distance <= (NB_SHAPE_RADIUS_BETWEEN_BALL * SHAPE_RADIUS) )
				{
					Position_free = false;	
				}
			}
			//SI POSITION EST LIBRE + A UNE DISTANCE 2*SHAPE_RADIUS DES BORDS
			if (Position_free == true && ((localPosition.x > 2 * SHAPE_RADIUS) && (localPosition.y < (SCREEN_HIGH - (2* SHAPE_RADIUS))) && (localPosition.x < (SCREEN_LENGTH-(2 * SHAPE_RADIUS))) && (localPosition.y > 2 * SHAPE_RADIUS)))
			{ 
				init_shape(corps, localPosition); 
			}
			//REMISE A TRUE DE LA POSITION_FREE
			Position_free = true;
		}
		
		//BOUCLE ACTION BALL
		for (i = 0; i < Ball::nombreInstances(); i++)
		{
			//DETECTION DES COLLISIONS 
			Detection_collision(corps, i);
			Detection_bord(&corps[i]);
			//DEPLACEMENT DE LA BALL
			corps[i].move(VITESSE, COEFF_DIR_X, COEFF_DIR_Y);
			//DESSINE LA BALL
			window.draw(corps[i].getShape());
		}
		window.display();
	}

	//suppression du tableau de balle
	delete[] corps;
	// fin de suppresion

	return 0;
}

/*(Re)Initialise pour autant que le nombre max n'est pas dépassé
Le nombre de corps en cours est alors incrémenté*/
void init_shape(Ball *shape, sf::Vector2i localPosition)
{
	if (Ball::nombreInstances() != NB_SHAPE_TOT)
	{
		shape[Ball::nombreInstances()].Initialise(localPosition, SHAPE_RADIUS, Ball::nombreInstances());
		Ball::SetInstances();
	}
}
/*Calcul la distance entre un corps face aux autres. L'indice du corps le plus proche est enregisté
Si la distance est plus petite que la taille d'une balle, c'est qu'il y a collision.On ne comapre pas un corps à lui même*/
void Detection_collision(Ball *shape, int i)
{
	double MAX = SCREEN_LENGTH;
	int nb_collision = 0;
	for (int e = 0; e < Ball::nombreInstances(); e++)
	{
		if (e != i)
		{
			double distance = sqrt(pow(shape[i].getPosition().x - shape[e].getPosition().x, 2) + pow(shape[i].getPosition().y - shape[e].getPosition().y, 2));
			if (distance < MAX)
			{
				MAX = distance;
				shape[i].setE_distance(e);
			}
		}
	}

	// SI COLLISION
	if (MAX <= 2 * shape[i].getRadius())
	{
		/*MESSAGE ECRAN*/
		shape[i].Description();
		printf(" : Collision avec la ");
		shape[shape[i].getE_distance()].Description();
		printf(" \n");

		/*INVERSE LA DIRECTION*/
		shape[i].inverseY();
		shape[i].inverseX();

		//INVERSION SUIVIS DE SUPPRESSION
		/*shape[shape[i].getE_distance()]=shape[Ball::nombreInstances() - 1];
		Ball::UnsetInstances();
		shape[i]=shape[Ball::nombreInstances() - 1];
		Ball::UnsetInstances();*/
	}
}
void Detection_bord(Ball *shape)
{
	float x = (shape->getPosition().x);
	float y = (shape->getPosition().y);

	if ((x >= SCREEN_LENGTH - 2 * shape->getRadius()) || (x <= 0))
	{
		shape->inverseX();
	}
	if ((y >= SCREEN_HIGH - 2 * shape->getRadius()) || (y <= 0))
	{
		shape->inverseY();
	}
}

