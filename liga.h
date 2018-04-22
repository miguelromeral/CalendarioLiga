#ifndef LIGA_H
#define LIGA_H

#include <stdbool.h>
#include <iostream>
#include <string.h>
#include "equipo.h"
#include "jornada.h"
#define N_EQUIPOS 20
#define N_JORNADAS 38
//Si se cambia N_EQUIPOS y N_JORNADAS se deben cambiar en jornada.h también.
using namespace std;

class Liga{
	private:
		Equipo participantes[N_EQUIPOS];
		Jornada jornada[N_JORNADAS];
		int n_participantes;
		bool liga_generada;
		int calcular_opuesto(int);
		Equipo opuestos[N_EQUIPOS/2][2];
		int parejas_opuestas;
	public:
		Liga();
		~Liga();
		void anyadirEquipo(char *);
		void printLigaEquipo(char *);
		void sortear();
		void rellenarOpuestosLigaSantander();
		bool esta(char *);
		void printJornada(int);
		bool tiene_opuesto(Equipo);
		void rellenarEquiposLigaSantander();
		void printEquipos();
		void printClasificacion();
		void printLiga();
		void generarLiga();
		void printOrdenLiga();
};
#endif
