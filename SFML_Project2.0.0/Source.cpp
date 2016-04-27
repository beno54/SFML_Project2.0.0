#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "Ball.h"

int NB_SHAPE= 1;
#define SCREEN_HIGH 1080
#define SCREEN_LENGTH 1920
#define SHAPE_RADIUS 10
#define VITESSE 3

void Coordonne_ligne(Ball*, int i);
void init_shape(Ball*);

void Detection_bord(Ball*);

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_LENGTH, SCREEN_HIGH), "SFML works!", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);
	int i = 0, e = 0;

	//Encodage de NB_SHAPE
	printf("Nombre de balles a generer: ");
	scanf_s("%d", &NB_SHAPE);
	printf("\n\n ");

	//r�servation de la place m�moire pour les balles . Attention l'initalisation (appel constructeur) pour chaque balle se fait dans la fonction init
	Ball * corps = (Ball*)malloc(sizeof(Ball)*NB_SHAPE);

	////initialisation des rond et leurs donn�es de trajectoire
	init_shape(corps);

	//lancement de la fen�tre
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		////on dessine les ronds et les lignes
		for (i = 0; i < NB_SHAPE; i++)
		{
			//	//d�tection des bords ==> x_dir et y_dir peuvent �tre modifi�
			Detection_bord(&corps[i]);

			//	//calcul de l'indice de la balle la plus proche et detection collision ==> x_dir et y_dir peuvent �tre modifi�
			Coordonne_ligne(corps, i);
		}

		//// on s�pare la d�tection de l'affichage car si on d�place avant de d�tecter toutes les collisions : pas juste
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
			//	//on dessine le rond apr�s calcul de la trajectoire et d�placement
			window.draw(corps[i].getShape());
			//	// on dessine les lignes
			window.draw(line, 2, sf::Lines);
		}

		window.display();
	}

	//suppression du tableau de balle
	for (int i = 0; i < NB_SHAPE; i++)
	{
		(corps + i)->~Ball();
	}
	free(corps);
	// fin de suppresion

	return 0;
}

void init_shape(Ball *shape)
{
	// on, g�n�re la position des balles
	int a = 0, e = 0;
	for (int i = 0; i < NB_SHAPE; i++)
	{
		//appel du constructeur de base pour chaques balles
		new (shape + i)Ball(i);

		//mise en memoire des donn�es voulue
		if (a + a * 4 * SHAPE_RADIUS > SCREEN_LENGTH)
		{
			e++;
			a = 0;
		}

		float x = float(SHAPE_RADIUS + a * 4 * SHAPE_RADIUS);
		float y = float(SHAPE_RADIUS + e * 4 * SHAPE_RADIUS);

		shape[i].setPosition(sf::Vector2f(x, y));
		shape[i].setRadius(SHAPE_RADIUS);
		a+=2;
	}


}

void Coordonne_ligne(Ball *shape, int i)
{
	double MAX = SCREEN_LENGTH;
	int nb_collision = 0;
	for (int e = 0; e < NB_SHAPE; e++)
	{
		// on v�rifie qu'on le comapre pas � lui m�me
		if (e != i)
		{
			//distance entre 2 points
			double distance = sqrt(pow(shape[i].getPosition().x - shape[e].getPosition().x, 2) + pow(shape[i].getPosition().y - shape[e].getPosition().y, 2));

			//enregistre si distance la plus courte vis � vis de ce point
			if (distance < MAX)
			{
				if (shape[e].getE_distance() != i)
				{
					MAX = distance;
					shape[i].setE_distance(e);
				}
			}

			// d�tection collision
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

