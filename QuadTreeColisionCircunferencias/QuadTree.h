#pragma once

#include <list>
#include <vector>

#include "Circunferencia.h"

using namespace std;

// Clase que implementa un arbol tipo QuadTree. Utiliza memoria dinámica para los distintos nodos del árbol

class QuadTree
{
public:

	// Constructor
	QuadTree(Point centro, int nivel = 0) : centro(centro), nivel(nivel) {};

	// Destructor
	~QuadTree();

	// Devuelve una circunferencia guardada en el árbol que contenga el punto pasado por parámetro
	Circunferencia * colision(const Point & p);

	// Añade una circunferencia al árbol
	void addObjeto(Circunferencia c);

	// Devuelve el número de elementos guardados en el árbol
	int getNumeroElementos();


private:

	// Número máximo de niveles en el árbol
	const int MAX_NIVEL = 6;

	// Referencias a los nodos hijos
	QuadTree* hijos[4]{nullptr};

	// Lista que contiene las Circunferencias del nodo del árbol
	list<Circunferencia> lista;

	// Punto central del nodo actual
	Point centro;

	// Nivel dentro del árbol de los nodos actuales
	int nivel;

	// Número de elementos en el árbol
	int totalElementos = 0;

	// Crea un nuevo nivel en el QuadTree
	void particionar();
	
	// Obtiene los cuadrantes a los que pertenece una circunferencia
	void getCuadrantes(Circunferencia, bool*);

	// Devuelve un vector con todas las circunferencias contenidas en el árbol que incluyen al punto p
	void colision(const Point & p, vector<Circunferencia> &vectorColisiones);
};

