#include <iostream>
using namespace std;
#include "equipo.h"
#include "jornada.h"

Jornada::Jornada(){
}

Jornada::~Jornada(){
}

void Jornada::printJornada(){
	int i;
	cout << endl << "Jornada " << njor << ":" << endl << endl;
	for(i=0; i<N_EQUIPOS; i+=2){
		cout << partidos[i].getNombre();
		if(strlen(partidos[i].getNombre()) < 8){
			cout << "\t";
		}
 		cout << "\t-  " << partidos[i+1].getNombre() << endl;
	}
}

void Jornada::intercambiarEquipos(int np){
	Equipo aux;
	int i1 = (np - 1) *  2;
	int i2 = i1 + 1;
	aux = partidos[i1];
	partidos[i1] = partidos[i2];
	partidos[i2] = aux;
}
