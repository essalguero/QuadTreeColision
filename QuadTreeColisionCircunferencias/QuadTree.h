#pragma once

#include <list>
#include <vector>

#include "Circunferencia.h"

using namespace std;

class QuadTree
{
public:
	QuadTree(Point centro) : centro(centro) {};
	~QuadTree();

	Circunferencia * colision(const Point & p);

	void addObjeto(Circunferencia c);

	int getNumeroElementos();

private:
	QuadTree* hijos[4]{nullptr};

	list<Circunferencia> lista;

	Point centro;


	void particionar();

	int getCuadrante(Circunferencia c);

	void colision(const Point & p, vector<Circunferencia> &vectorColisiones);
};

