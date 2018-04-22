#ifndef EQUIPO_H
#define EQUIPO_H

#include <stdbool.h>
#include <iostream>
#include <string.h>
#include "equipo.h"
using namespace std;

class Equipo{
	public:
		char * nombre;
		bool mezclado = false;
		int pos;
		Equipo();
		~Equipo();
		void setNombre(char * nuevo){ nombre = nuevo; }
		char * getNombre(){ return nombre; }
		void setPos(int n){ pos = n; }
		int getPos(){ return pos; }
};
#endif
