#ifndef JORNADA_H
#define JORNADA_H

#include <iostream>
#include <string.h>
#include "equipo.h"
using namespace std;
#define N_EQUIPOS 20
//Si se cambia N_EQUIPOS se deben cambiar en liga.h también.

class Jornada{
	public:
		Equipo partidos[N_EQUIPOS];
		int njor;
		Jornada();
		~Jornada();
		void intercambiarEquipos(int);
		void printJornada();
};
#endif
