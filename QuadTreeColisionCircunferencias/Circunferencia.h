#pragma once

#include "Point.h"

using namespace std;

class Circunferencia
{
public:
	Circunferencia();

	Circunferencia(int identificador, Point centro, int radio = 10, int profundidad = 1) :identificador(identificador),
		centro(centro), radio(radio), profundidad(profundidad) {};

	Circunferencia(const Circunferencia & c) : Circunferencia(c.identificador, c.centro, c.radio, c.profundidad) {};

	~Circunferencia();

	inline Point getCentro() { return centro; }
	inline int getRadio() { return radio; }
	inline int getProfundidad() { return profundidad; }
	inline int getId() { return identificador;  }
private:

	int identificador;

	Point centro;
	int radio;

	int profundidad;
};

