#include "stdafx.h"
#include "QuadTree.h"

#include <cstdlib>

// Destruye los nodos hijos (creados dinámicamente)
QuadTree::~QuadTree()
{
	if (hijos[0] != nullptr)
	{
		for (int i = 0; i < 4; ++i)
		{
			delete(hijos[i]);
		}
	}
}

// Genera un nivel más en el QuadTree
void QuadTree::particionar()
{
	int width = centro.getX() / 2;
	int heigth = centro.getY() / 2;
	hijos[0] = new QuadTree(Point(centro.getX() - width, centro.getY() - heigth), nivel + 1);
	hijos[1] = new QuadTree(Point(centro.getX() + width, centro.getY() - heigth), nivel + 1);
	hijos[2] = new QuadTree(Point(centro.getX() + width, centro.getY() + heigth), nivel + 1);
	hijos[3] = new QuadTree(Point(centro.getX() - width, centro.getY() + heigth), nivel + 1);
	
}

// Devuelve los cuadrantes (del nodo actual del QuadTree) a los que pertenece una circunferencia
void QuadTree::getCuadrantes(Circunferencia c, bool* cuadrantes)
{
	// Punto central del nodo del árbol actual
	Point p = centro;

	// Calcular los cuadrantes en los que está incluida la circunferencia
	cuadrantes[0] = (c.getCentro().getX() < (p.getX() + c.getRadio()) && c.getCentro().getY() < (p.getY() + c.getRadio()));
	cuadrantes[1] = (c.getCentro().getX() < (p.getX() + c.getRadio()) && c.getCentro().getY() > (p.getY() - c.getRadio()));
	cuadrantes[2] = (c.getCentro().getX() > (p.getX() - c.getRadio()) && c.getCentro().getY() > (p.getY() - c.getRadio()));
	cuadrantes[3] = (c.getCentro().getX() > (p.getX() - c.getRadio()) && c.getCentro().getY() < (p.getY() + c.getRadio()));
}

// Añade una circunferencia al QuadTree
void QuadTree::addObjeto(Circunferencia circunferencia)
{
	int cuadrante = -1;

	bool cuadrantes[4]{ false };

	// Si no estamos en el último nivel del árbol, se intenta insertar la circunferencia en el cuadrante que le corresponda
	if (nivel < MAX_NIVEL) {

		// Obtener los cuadrantes en los que puede estar la circunferencia
		getCuadrantes(circunferencia, cuadrantes);

		// Si puede estar en todos los cuadrantes, se inserta en la lista del nodo actual
		if (cuadrantes[0] && cuadrantes[1] && cuadrantes[2] && cuadrantes[3])
		{
			lista.push_back(circunferencia);
		}
		else
		{
			// Si no se inserta en la lista del nodo actual, se tiene que insertar en alguno de los nodos hijos

			// Comprobar que los nodos hijos existen. Si no, crearlos
			if (hijos[0] == nullptr)
			{
				particionar();
			}

			// Insertar en todos los cuadrantes que toca la circunferencia
			for (int i = 0; i < 4; i++) {
				if (cuadrantes[i]) {
					hijos[i]->addObjeto(circunferencia);
				}
			}
		}
	}
	else {
		// Si estamos en el último nivel del árbol, se inserta la circunferencia en la lista del nodo actual
		lista.push_back(circunferencia);
	}
}


// Guarda en la vectorColisiones todas las circunferencias que contiene al punto p (colision). Las circunferencias con las que colisiona se van
// guardando en un vector en la parte de atras del vector, excepto cuando encuentra una con menor profundidad que la primera del vector. En este
// caso, se guarda en la parte delantera
void QuadTree::colision(const Point & p, vector<Circunferencia> & vectorColisiones)
{
	// Si la lista del nodo actual tiene objetos, se buscan colisiones con los objetos de la lista
	for (Circunferencia c : lista)
	{
		if (p.distance2(c.getCentro()) <= (c.getRadio() * c.getRadio()))
		{
			if ( (vectorColisiones.size() == 0) || 
				 (c.getProfundidad() >= (*vectorColisiones.begin()).getProfundidad()) ) {
				vectorColisiones.push_back(c);
			} else {
				vectorColisiones.insert(vectorColisiones.begin(), c);
			}
		}
	}

	// Si hay nodos jijos, buscar las colisiones en los nodos hijos
	if (nullptr != hijos[0])
	{
		for (int i = 0; i < 4; i++) {
			hijos[i]->colision(p, vectorColisiones);
		}
	}
}


// Devuelve la circunferencia con menor profundidad (menor z-buffer) que contiene al punto p (colision). Las circunferencias con las que colisiona se van
// guardando en un vector. Devuelve al final la primera que encuentre de entre todas las que tienen la misma profundidad
Circunferencia * QuadTree::colision (const Point & p)
{
	vector<Circunferencia> vectorColisiones;
	Circunferencia * circunferenciaColision = nullptr;

	colision(p, vectorColisiones);

	// Devuelve la circunferencia que corresponda
	if (vectorColisiones.size() != 0)
	{
		circunferenciaColision = new Circunferencia(vectorColisiones.at(0));
	}
	
	return circunferenciaColision;
}


// Devuelve el número de elementos total contenidos en el árbol
int QuadTree::getNumeroElementos()
{
	int elementos = 0;
	if (hijos[0] != nullptr) {
		for (int i = 0; i < 4; i++) {
			elementos += hijos[i]->getNumeroElementos();
		}
	}
	elementos += lista.size();

	return elementos;
}

