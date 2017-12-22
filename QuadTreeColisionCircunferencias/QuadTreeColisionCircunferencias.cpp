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

//const Point PUNTO_CHEQUEAR(100, 450);
const Point PUNTO_CHEQUEAR(500, 500);

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
	//QuadTree arbol2(Point(HEIGHT / 2, WIDTH / 2));

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

	yellow.r = 200;
	yellow.g = 200;
	yellow.b = 0;

	red.r = 200;
	red.g = 0;
	red.b = 0;

	//Inicializar generador de numeros aleatorios
	srand((unsigned)time(NULL));


	// Inicializar la libreria Allegro para pintar las circunferencias
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

	// Generacion aleatoria de circunferencias
	Circunferencia c;
	int anterior = 0;
	int nuevo = 0;
	for (int i = 0; i < NUMERO_CIRCUNFERENCIAS; i++)
	{
		c = generarCircunferencia(i);
		listaCircunferencias.push_back(c);

		// Cada circunferencia generada se añade al arbol
		//arbol.addObjeto(c);
		arbol.addObjeto_alternativo(c);
		anterior = nuevo;
		nuevo = arbol.getNumeroElementos();
		if ((nuevo < anterior) || (nuevo > listaCircunferencias.size())) {
			cout << "Numero de Elementos antes: " << anterior << endl;
			cout << "Numero de Elementos despues: " << nuevo << endl;
		}
		//arbol2.addObjeto(c);
	}

	// Dibujar un pequeño circulo de color rojo alrededor del punto donde se quiere calcular la colision
	al_draw_circle(PUNTO_CHEQUEAR.getX(), PUNTO_CHEQUEAR.getY(), 2.0f, red, 1.0f);

	// Dibujar todas las circunferencias
	for (Circunferencia c : listaCircunferencias)
	{
		al_draw_circle(c.getCentro().getX(), c.getCentro().getY(), c.getRadio(), green, 1.0f);
	}

	// Hace el flip para que la pantalla se actualice
	al_flip_display();
	
	// Lista el numero total de elementos en el arbol y en la lista para poder compararlos
	cout << "Total elementos en el arbol: " << arbol.getNumeroElementos() << endl << endl;
	cout << "Total elementos en la lista: " << listaCircunferencias.size() << endl << endl;

	// Obtiene la circunferencia con la que colisiona el rayo (Punto indicado)
	Circunferencia* circunferenciaColision = arbol.colision(PUNTO_CHEQUEAR);

	// Imprime un resultado u otro en función de si hay colisión con alguna de las circunferencias o no hay colisión con ninguna
	if (nullptr == circunferenciaColision)
	{
		cout << "No hay colision con el punto " << PUNTO_CHEQUEAR << endl << endl;
	}
	else
	{
		cout << "Punto " << PUNTO_CHEQUEAR << " da Colision con circunferencia " << circunferenciaColision->getId() <<  " de centro: " <<
			circunferenciaColision->getCentro() << " y profundidad: " << circunferenciaColision->getProfundidad() << endl << endl;
	}


	// Espera a que se pulse una tecla + Enter para salir
	//cin;

	//al_rest(10.0);

	char caracter = ' ';

	while (caracter == ' ')
		cin >> caracter;

	// Destruye el display de Allegro
	al_destroy_display(display);

    return 0;
}

