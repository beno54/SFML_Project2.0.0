#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Ball.h"

#define NB_SHAPE_TOT  150
#define SCREEN_HIGH 1080
#define SCREEN_LENGTH 1920
#define SHAPE_RADIUS 5
#define NB_SHAPE_RADIUS_BETWEEN_BALL 4
//détermine l'orientation par défaut des balles
#define COEFF_DIR_X .47
#define COEFF_DIR_Y .78
#define VITESSE 5

void init_shape(Ball*, sf::Vector2i );
void Coordonne_ligne(Ball*, int i);
void Detection_bord(Ball*);

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_LENGTH, SCREEN_HIGH), "SFML works!", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	int i = 0, e = 0;
	bool Position_free = true;

	//réservation de la place mémoire pour les balles . Attention l'initalisation (appel constructeur) pour chaque balle se fait dans la fonction init
	Ball * corps;
	corps = new Ball[NB_SHAPE_TOT];
	Ball::ResetInstances();


	//lancement de la fenêtre
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		Position_free = true;

		//CLICK SOURIS =  CREATE BALL
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
	
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			for (int i = 0; i < Ball::nombreInstances(); i++)
			{
				double distance = sqrt(pow(corps[i].getPosition().x - localPosition.x, 2) + pow(corps[i].getPosition().y - localPosition.y, 2));
				// on test qu'aucunes autre balle n'est présente à l'amplacement de la souris
				if (distance <= (NB_SHAPE_RADIUS_BETWEEN_BALL * SHAPE_RADIUS) )
				{
					//printf("error");
					Position_free = false;	
				}
			}
		
			// on test que la souris est assez loin des bords, si ok, on créer la balle
			if (Position_free == true && ((localPosition.x > 2 * SHAPE_RADIUS) && (localPosition.y < (SCREEN_HIGH - (2* SHAPE_RADIUS))) && (localPosition.x < (SCREEN_LENGTH-(2 * SHAPE_RADIUS))) && (localPosition.y > 2 * SHAPE_RADIUS)))
			{ 
				init_shape(corps, localPosition); 
			}
		}

		////on dessine les ronds et les lignes
		for (i = 0; i < Ball::nombreInstances(); i++)
		{
				//calcul de l'indice de la balle la plus proche et detection collision ==> x_dir et y_dir peuvent être modifié
			Coordonne_ligne(corps, i);
			Detection_bord(&corps[i]);

				//	//détection des bords ==> x_dir et y_dir peuvent être modifié
		}

		//// on sépare la détection de l'affichage car si on déplace avant de détecter toutes les collisions : pas juste
		for (i = 0; i < Ball::nombreInstances(); i++)
		{
			int e = corps[i].getE_distance();
			// on relie avec le point le plus proche 
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f((corps[i].getPosition().x + SHAPE_RADIUS), corps[i].getPosition().y + SHAPE_RADIUS)),
				sf::Vertex(sf::Vector2f((corps[e].getPosition().x + SHAPE_RADIUS), corps[e].getPosition().y + SHAPE_RADIUS))
			};

			corps[i].move(VITESSE, COEFF_DIR_X, COEFF_DIR_Y);

			//	//on dessine le rond après calcul de la trajectoire et déplacement
			window.draw(corps[i].getShape());
			//	// on dessine les lignes
			//window.draw(line, 2, sf::Lines);
		}

		window.display();
	}

	//suppression du tableau de balle
	delete[] corps;
	// fin de suppresion

	return 0;
}

void init_shape(Ball *shape, sf::Vector2i localPosition)
{
	//printf("\nCREATE:ball %d", Ball::nombreInstances());
	if (Ball::nombreInstances() != NB_SHAPE_TOT)
	{
		//génère la couleur en fonction de la position du curseur
		shape[Ball::nombreInstances()].setFillColor(sf::Color(localPosition.y % 245, localPosition.x % 245, (localPosition.y + localPosition.x) % 245));
		shape[Ball::nombreInstances()].setPosition(sf::Vector2f(localPosition));
		shape[Ball::nombreInstances()].setRadius(SHAPE_RADIUS);
		//incrémente la variable static qui compte le nombre de Balle pour qu'elle comprenne le nomrbe de balle existante
		Ball::SetInstances();
	}
}

void Coordonne_ligne(Ball *shape, int i)
{
	double MAX = SCREEN_LENGTH;
	int nb_collision = 0;
	for (int e = 0; e < Ball::nombreInstances(); e++)
	{
		// on vérifie qu'on le comapre pas à lui même
		if (e != i)
		{
			//distance entre 2 points
			double distance = sqrt(pow(shape[i].getPosition().x - shape[e].getPosition().x, 2) + pow(shape[i].getPosition().y - shape[e].getPosition().y, 2));

			//enregistre si distance la plus courte vis à vis de ce point
			if (distance < MAX)
			{
				// on enregistre qd meme la distance la plus proche
				MAX = distance;
				if (shape[e].getE_distance() != i)
				{
					// si un corps à déjà un lien avec, on ne le lie pas avec ce corps
					shape[i].setE_distance(e);
				}
			}
		}
	}

	// détection collision
	if (MAX <= 2 * SHAPE_RADIUS)
	{
		shape[i].Description();
		printf(" : Collision avec la ");
		shape[shape[i].getE_distance()].Description();
		printf(" \n");
		//si collision avec position_y de balle A = position_y de balle B, elle ne bouge que sur un axe 

		shape[i].inverseY();
		shape[i].inverseX();

	}
}

void Detection_bord(Ball *shape)
{
	float x = (shape->getPosition().x);
	float y = (shape->getPosition().y);

	if ((x >= SCREEN_LENGTH - 2 * SHAPE_RADIUS) || (x <= 0))
	{
		shape->inverseX();
		//shape->Description();
		//printf(" : Collision avec le bord X\n");
	
	}
	if ((y >= SCREEN_HIGH - 2 * SHAPE_RADIUS) || (y <= 0))
	{
		shape->inverseY();
		//shape->Description();
		//printf(" : Collision avec le bord Y\n");
	}

}

