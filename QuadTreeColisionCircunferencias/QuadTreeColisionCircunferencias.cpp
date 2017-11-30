// QuadTreeColisionCircunferencias.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "QuadTree.h"


#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_color.h>

#include <iostream>

using namespace std;

const int SCREEN_WIDTH{ 1000 };
const int SCREEN_HEIGHT{ 1000 };

/*const int SCREEN_WIDTH{ 800 };
const int SCREEN_HEIGHT{ 600 };*/

const int WIDTH{ 1000 };
const int HEIGHT{ 1000 };

const int RADIO{ 100 };

const int NUMERO_CIRCUNFERENCIAS{ 100 };

const int MAX_PROFUNDIDAD{ 10 };

const Point PUNTO_CHEQUEAR(100, 450);

//Generar Circunferencias de manera aleatoria
Circunferencia generarCircunferencia(int identificador)
{
	Point p(rand() % WIDTH, rand() % HEIGHT);
	
	int profundidad{ rand() % MAX_PROFUNDIDAD };

	int radio{ RADIO };

	return Circunferencia(identificador, p, radio, profundidad);
}

int main()
{

	QuadTree arbol(Point(HEIGHT / 2, WIDTH / 2));

	list<Circunferencia> listaCircunferencias;

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_COLOR white = ALLEGRO_COLOR();
	ALLEGRO_COLOR yellow = ALLEGRO_COLOR();
	ALLEGRO_COLOR red = ALLEGRO_COLOR();
	ALLEGRO_COLOR green = ALLEGRO_COLOR();
	ALLEGRO_COLOR blue = ALLEGRO_COLOR();
	ALLEGRO_BITMAP *backBuffer = NULL;

	green.r = 0;
	green.g = 50;
	green.b = 0;

	red.r = 200;
	red.g = 0;
	red.b = 0;

	//Inicializar generador de numeros aleatorios
	srand((unsigned)time(NULL));


	al_init_primitives_addon();

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	backBuffer = al_get_backbuffer(display);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	Circunferencia c;
	for (int i = 0; i < NUMERO_CIRCUNFERENCIAS; i++)
	{
		c = generarCircunferencia(i);
		listaCircunferencias.push_back(c);

		arbol.addObjeto(c);
	}

	al_draw_pixel(PUNTO_CHEQUEAR.getX(), PUNTO_CHEQUEAR.getY(), red);

	for (Circunferencia c : listaCircunferencias)
	{
		al_draw_circle(c.getCentro().getX() / 10, c.getCentro().getY() / 10, c.getRadio(), green, 1.0f);
	}

	
	al_flip_display();
	

	cout << "Total elementos en el arbol: " << arbol.getNumeroElementos() << endl << endl;


	Circunferencia* circunferenciaColision = arbol.colision(PUNTO_CHEQUEAR);

	if (nullptr == circunferenciaColision)
	{
		cout << "No hay colision con el punto " << PUNTO_CHEQUEAR << endl << endl;
	}
	else
	{
		cout << "Punto " << PUNTO_CHEQUEAR << " da Colision con circunferencia de centro: " << 
			circunferenciaColision->getCentro() << " y profundidad: " << c.getProfundidad() << endl << endl;
	}


	cin;

	//al_rest(10.0);

	char caracter = ' ';

	while (caracter == ' ')
		cin >> caracter;

	al_destroy_display(display);

    return 0;
}

