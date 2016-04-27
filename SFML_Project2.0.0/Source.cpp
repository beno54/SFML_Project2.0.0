#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Ball.h"

#define NB_SHAPE_TOT  100
int NB_SHAPE= 0;
#define SCREEN_HIGH 1080
#define SCREEN_LENGTH 1920
#define SHAPE_RADIUS 10
#define VITESSE 3

void Coordonne_ligne(Ball*, int i);
void init_shape(Ball*, sf::Vector2i );

void Detection_bord(Ball*);

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_LENGTH, SCREEN_HIGH), "SFML works!", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	int i = 0, e = 0;
	bool Position_free = true;
	//Encodage de NB_SHAPE
	//printf("Nombre de balles a generer: ");
	//scanf_s("%d", &NB_SHAPE);
	//printf("\n\n ");

	//réservation de la place mémoire pour les balles . Attention l'initalisation (appel constructeur) pour chaque balle se fait dans la fonction init
	Ball * corps;
	corps = new Ball[NB_SHAPE_TOT];

	////initialisation des rond et leurs données de trajectoire
	

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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
			for (int i = 0; i < NB_SHAPE; i++)
			{
				double distance = sqrt(pow(corps[i].getPosition().x - localPosition.x, 2) + pow(corps[i].getPosition().y - localPosition.y, 2));
				if (distance <= (2 * SHAPE_RADIUS))
				{
					Position_free = false;
				}
			}
			// le bouton gauche est enfoncé : on crée
			if (Position_free == true)init_shape(corps, localPosition);
		}

		////on dessine les ronds et les lignes
		for (i = 0; i < NB_SHAPE; i++)
		{
			//	//détection des bords ==> x_dir et y_dir peuvent être modifié
			Detection_bord(&corps[i]);

			//	//calcul de l'indice de la balle la plus proche et detection collision ==> x_dir et y_dir peuvent être modifié
			Coordonne_ligne(corps, i);
		}

		//// on sépare la détection de l'affichage car si on déplace avant de détecter toutes les collisions : pas juste
		for (i = 0; i < NB_SHAPE; i++)
		{
			int e = corps[i].getE_distance();
			// on relie avec le point le plus proche 
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f((corps[i].getPosition().x + SHAPE_RADIUS), corps[i].getPosition().y + SHAPE_RADIUS)),
				sf::Vertex(sf::Vector2f((corps[e].getPosition().x + SHAPE_RADIUS), corps[e].getPosition().y + SHAPE_RADIUS))
			};

			//	//on move le shape
			corps[i].move(VITESSE);
			//	//on dessine le rond après calcul de la trajectoire et déplacement
			window.draw(corps[i].getShape());
			//	// on dessine les lignes
			window.draw(line, 2, sf::Lines);
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
	if (NB_SHAPE != NB_SHAPE_TOT )
	{
		shape[NB_SHAPE].setFillColor(sf::Color(localPosition.y % 255, localPosition.x % 255, (localPosition.y + localPosition.x) % 255));
		shape[NB_SHAPE].setPosition(sf::Vector2f(localPosition));
		shape[NB_SHAPE].setRadius(SHAPE_RADIUS);

		NB_SHAPE++;
	}


}

void Coordonne_ligne(Ball *shape, int i)
{
	double MAX = SCREEN_LENGTH;
	int nb_collision = 0;
	for (int e = 0; e < NB_SHAPE; e++)
	{
		// on vérifie qu'on le comapre pas à lui même
		if (e != i)
		{
			//distance entre 2 points
			double distance = sqrt(pow(shape[i].getPosition().x - shape[e].getPosition().x, 2) + pow(shape[i].getPosition().y - shape[e].getPosition().y, 2));

			//enregistre si distance la plus courte vis à vis de ce point
			if (distance < MAX)
			{
				if (shape[e].getE_distance() != i)
				{
					MAX = distance;
					shape[i].setE_distance(e);
				}
			}

			// détection collision
			if (distance <= 2 * SHAPE_RADIUS)
			{
				shape[i].Description();
				printf(" : Collision avec la ");
				shape[shape[i].getE_distance()].Description();
				printf(" \n");
				shape[i].inverseX();
				shape[i].inverseY();
			}
		}
	}

}

void Detection_bord(Ball *shape)
{
	float x = (shape->getPosition().x);
	float y = (shape->getPosition().y);

	if ((x >= SCREEN_LENGTH - 2 * SHAPE_RADIUS) || (x <= 0))
	{
		shape->inverseX();
		shape->Description();
		printf(" : Collision avec le bord X\n");
	}
	if ((y >= SCREEN_HIGH - 2 * SHAPE_RADIUS) || (y <= 0))
	{
		shape->inverseY();
		shape->Description();
		printf(" : Collision avec le bord Y\n");
	}

}

