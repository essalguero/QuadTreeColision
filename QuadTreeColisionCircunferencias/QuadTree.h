#pragma once

#include <list>
#include <vector>

#include "Circunferencia.h"

using namespace std;

class QuadTree
{
public:
	QuadTree(Point centro, int nivel = 0) : centro(centro), nivel(nivel) {};
	~QuadTree();

	Circunferencia * colision(const Point & p);

	void addObjeto(Circunferencia c);

	void addObjeto_old(Circunferencia c);

	int getNumeroElementos();


	void addObjeto_alternativo(Circunferencia);



private:

	const int MAX_NIVEL = 6;

	QuadTree* hijos[4]{nullptr};

	list<Circunferencia> lista;

	Point centro;

	int nivel;

	int totalElementos = 0;


	void particionar();

	int getCuadrante(Circunferencia c);
	bool* getCuadrante_alternativo(Circunferencia c);

	void colision(const Point & p, vector<Circunferencia> &vectorColisiones);
};

