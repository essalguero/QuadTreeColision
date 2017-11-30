#include "stdafx.h"
#include "QuadTree.h"

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
	hijos[0] = new QuadTree(Point(centro.getX() - width, centro.getY() - heigth));
	hijos[1] = new QuadTree(Point(centro.getX() + width, centro.getY() - heigth));
	hijos[2] = new QuadTree(Point(centro.getX() + width, centro.getY() + heigth));
	hijos[3] = new QuadTree(Point(centro.getX() - width, centro.getY() + heigth));
	
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

	if (lista.size() == 6) {
		particionar();
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


void QuadTree::colision(const Point & p, vector<Circunferencia> & vectorColisiones)
{
	for (Circunferencia c : lista)
	{
		if (p.distance2(c.getCentro()) <= (c.getRadio() * c.getRadio()))
		{
			vectorColisiones.push_back(c);
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
			vectorColisiones.push_back(c);
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
		int i = 1;
		for (auto it = vectorColisiones.begin() + 1; it < vectorColisiones.end(); ++it)
		{
			if ((*it).getProfundidad() > vectorColisiones.at(pos).getProfundidad())
			{
				pos = i;
			}
			i++;
		}

		circunferenciaColision = new Circunferencia(vectorColisiones.at(pos));
		
	}
	
	return circunferenciaColision;
}



int QuadTree::getNumeroElementos()
{
	if (nullptr == hijos[0])
	{
		return lista.size();
	}
	else
	{
		int total = 0;
		for (int i = 0; i < 4; i++) {
			total += hijos[i]->getNumeroElementos();
		}
		return lista.size() + total;
	}
}

