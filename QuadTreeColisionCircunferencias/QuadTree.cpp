#include "stdafx.h"
#include "QuadTree.h"

#include <cstdlib>

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

void QuadTree::particionar()
{
	int width = centro.getX() / 2;
	int heigth = centro.getY() / 2;
	hijos[0] = new QuadTree(Point(centro.getX() - width, centro.getY() - heigth), nivel + 1);
	hijos[1] = new QuadTree(Point(centro.getX() + width, centro.getY() - heigth), nivel + 1);
	hijos[2] = new QuadTree(Point(centro.getX() + width, centro.getY() + heigth), nivel + 1);
	hijos[3] = new QuadTree(Point(centro.getX() - width, centro.getY() + heigth), nivel + 1);
	
}

int QuadTree::getCuadrante(Circunferencia c)
{
	int x = c.getCentro().getX();
	int y = c.getCentro().getY();

	int cuadrante = 0;

	if (x < centro.getX())
	{
		if (y < centro.getY())
		{
			cuadrante = 0;
		}
		else if (y > centro.getY())
		{
			cuadrante = 3;
		}
		else
		{
			cuadrante = -1;
		}
	}
	else if (x > centro.getX())
	{
		if (y < centro.getY())
		{
			cuadrante = 2;
		}
		else if (y > centro.getY())
		{
			cuadrante = 1;
		}
		else
		{
			cuadrante = -1;
		}
	}
	return cuadrante;
}

void QuadTree::addObjeto(Circunferencia circunferencia)
{
	int cuadrante = -1;

	list<Circunferencia> listaActual;

	if (nivel < MAX_NIVEL) {
		/*if ( abs(circunferencia.getCentro().getX() - centro.getX()) < circunferencia.getRadio() && 
			abs(circunferencia.getCentro().getY() - centro.getY()) < circunferencia.getRadio())
		{
			cuadrante = getCuadrante(circunferencia);

			if (-1 == cuadrante)
			{
				listaActual.push_back(c);
			}
			else
			{
				hijos[cuadrante]->addObjeto(c);
			}
		}
		else {
			lista.push_back(circunferencia);
		}*/
		if (abs(circunferencia.getCentro().getX() - centro.getX()) < circunferencia.getRadio() ||
			abs(circunferencia.getCentro().getY() - centro.getY()) < circunferencia.getRadio())
		{
			lista.push_back(circunferencia);
		}
		else
		{
			cuadrante = getCuadrante(circunferencia);

			if (-1 == cuadrante)
			{
				lista.push_back(circunferencia);
			}
			else
			{
				if (hijos[0] == nullptr)
				{
					particionar();
				}
				hijos[cuadrante]->addObjeto(circunferencia);
			}
		}
	}
	else {
		lista.push_back(circunferencia);
	}
}

void QuadTree::addObjeto_old(Circunferencia circunferencia)
{
	int cuadrante = -1;

	list<Circunferencia> listaActual;

	if (nivel < MAX_NIVEL) {

		if (lista.size() == 6) {
			particionar();

			cout << "Particionando" << endl;

			for (Circunferencia c : lista)
			{
				cuadrante = getCuadrante(c);

				if (-1 == cuadrante)
				{
					listaActual.push_back(c);
				}
				else
				{
					hijos[cuadrante]->addObjeto(c);
				}
			}
			lista = listaActual;

			cuadrante = getCuadrante(circunferencia);
			if (-1 == cuadrante)
			{
				lista.push_back(circunferencia);
			}
			else
			{
				hijos[cuadrante]->addObjeto(circunferencia);
			}
		}
		else
		{
			if (nullptr == hijos[0])
			{
				lista.push_back(circunferencia);
			}
			else
			{
				cuadrante = getCuadrante(circunferencia);
				if (-1 == cuadrante)
				{
					lista.push_back(circunferencia);
				}
				else
				{
					hijos[cuadrante]->addObjeto(circunferencia);
				}
			}
		}
	}
	else
	{
		lista.push_back(circunferencia);
	}


}


void QuadTree::colision(const Point & p, vector<Circunferencia> & vectorColisiones)
{
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

	if (nullptr != hijos[0])
	{
		for (int i = 0; i < 4; i++) {
			hijos[i]->colision(p, vectorColisiones);
		}
	}
}

Circunferencia * QuadTree::colision (const Point & p)
{
	vector<Circunferencia> vectorColisiones;
	Circunferencia * circunferenciaColision = nullptr;

	int pos = 0;
	
	for (Circunferencia c : lista)
	{
		if (p.distance2(c.getCentro()) <= (c.getRadio() * c.getRadio()))
		{
			if ( (vectorColisiones.size() == 0) || 
				 (c.getProfundidad() >= (*vectorColisiones.begin()).getProfundidad()) ) {
				vectorColisiones.push_back(c);
			}
			else {
				vectorColisiones.insert(vectorColisiones.begin(), c);
			}
		}
	}

	if (nullptr != hijos[0])
	{
		for (int i = 0; i < 4; i++)
		{
			hijos[i]->colision(p, vectorColisiones);
		}
	}

	if (vectorColisiones.size() != 0)
	{
		/*int i = 1;
		for (auto it = vectorColisiones.begin() + 1; it < vectorColisiones.end(); ++it)
		{
			if ((*it).getProfundidad() > vectorColisiones.at(pos).getProfundidad())
			{
				pos = i;
			}
			i++;
		}

		circunferenciaColision = new Circunferencia(vectorColisiones.at(pos));*/
		circunferenciaColision = new Circunferencia(vectorColisiones.at(0));
	}
	
	return circunferenciaColision;
}



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

