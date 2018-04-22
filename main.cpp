#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#include "equipo.h"
#include "liga.h"
#define LENGTH_TEAM 30

int main(int args, char ** argv){
	Liga liga;

	//Orden LaLiga 2018
	/*liga.anyadirEquipo((char *) "Las Palmas");
	liga.anyadirEquipo((char *) "Girona");
	liga.anyadirEquipo((char *) "Eibar SD");
	liga.anyadirEquipo((char *) "SAD Getafe");
	liga.anyadirEquipo((char *) "RCD Espanyol");
	liga.anyadirEquipo((char *) "RCD Alaves");	
	liga.anyadirEquipo((char *) "Real Betis");
	liga.anyadirEquipo((char *) "Real Sociedad");
	liga.anyadirEquipo((char *) "Levante");	
	liga.anyadirEquipo((char *) "Real Madrid CF");
	liga.anyadirEquipo((char *) "RC Deportivo");
	liga.anyadirEquipo((char *) "Villarreal");
	liga.anyadirEquipo((char *) "RC Celta");
	liga.anyadirEquipo((char *) "FC Barcelona");	
	liga.anyadirEquipo((char *) "Leganes");
	liga.anyadirEquipo((char *) "Sevilla FC");
	liga.anyadirEquipo((char *) "Athletic Club");
	liga.anyadirEquipo((char *) "Malaga FC");
	liga.anyadirEquipo((char *) "Atletico Madrid");
	liga.anyadirEquipo((char *) "Valencia FC");*/

	
	liga.rellenarEquiposLigaSantander();

	liga.rellenarOpuestosLigaSantander();
	liga.sortear();
	liga.generarLiga();
	liga.printLiga();
	liga.printOrdenLiga();
	liga.printLigaEquipo((char *) "Real Madrid CF");
	//liga.printJornada(1);
	return 0;
}
