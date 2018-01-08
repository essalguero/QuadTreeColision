#pragma once

#include <list>
#include <vector>

#include "Circunferencia.h"

using namespace std;

// Clase que implementa un arbol tipo QuadTree. Utiliza memoria din�mica para los distintos nodos del �rbol

class QuadTree
{
public:

	// Constructor
	QuadTree(Point centro, int nivel = 0) : centro(centro), nivel(nivel) {};

	// Destructor
	~QuadTree();

	// Devuelve una circunferencia guardada en el �rbol que contenga el punto pasado por par�metro
	Circunferencia * colision(const Point & p);

	// A�ade una circunferencia al �rbol
	void addObjeto(Circunferencia c);

	// Devuelve el n�mero de elementos guardados en el �rbol
	int getNumeroElementos();


private:

	// N�mero m�ximo de niveles en el �rbol
	const int MAX_NIVEL = 6;

	// Referencias a los nodos hijos
	QuadTree* hijos[4]{nullptr};

	// Lista que contiene las Circunferencias del nodo del �rbol
	list<Circunferencia> lista;

	// Punto central del nodo actual
	Point centro;

	// Nivel dentro del �rbol de los nodos actuales
	int nivel;

	// N�mero de elementos en el �rbol
	int totalElementos = 0;

	// Crea un nuevo nivel en el QuadTree
	void particionar();
	
	// Obtiene los cuadrantes a los que pertenece una circunferencia
	void getCuadrantes(Circunferencia, bool*);

	// Devuelve un vector con todas las circunferencias contenidas en el �rbol que incluyen al punto p
	void colision(const Point & p, vector<Circunferencia> &vectorColisiones);
};

