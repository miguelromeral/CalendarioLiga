#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
using namespace std;
#include "equipo.h"
#include "jornada.h"
#include "liga.h"

Liga::Liga(){
	n_participantes = 0;
}

Liga::~Liga(){
}

void Liga::anyadirEquipo(char * nombre){
	Equipo n;
	n.setNombre(nombre);
	//Si no está lleno...
	if(n_participantes < N_EQUIPOS){
		n.setPos(n_participantes + 1);
		//Los equipos se registran en participantes[]
		participantes[n_participantes] = n;
		n_participantes++;
	}else{
		cout << "Imposible anyadir al " << nombre << ". Ya hay " << N_EQUIPOS << " equipos." << endl; 
	}
}

void Liga::rellenarEquiposLigaSantander(){
	//Se añaden en este orden. Para evitar que el calendario sea siempre
	//el mismo habría que sortearlo después.
	anyadirEquipo((char *) "Real Madrid CF");
	anyadirEquipo((char *) "FC Barcelona");
	anyadirEquipo((char *) "Atletico Madrid");
	anyadirEquipo((char *) "Sevilla FC");
	anyadirEquipo((char *) "Valencia FC");		// 4
	anyadirEquipo((char *) "Villarreal");		// 5
	anyadirEquipo((char *) "RC Celta");		// 6
	anyadirEquipo((char *) "RC Deportivo");		// 7
	anyadirEquipo((char *) "SAD Getafe");		// 8
	anyadirEquipo((char *) "Levante");		// 9
	anyadirEquipo((char *) "Girona");		// 10
	anyadirEquipo((char *) "Leganes");		// 11
	anyadirEquipo((char *) "RCD Espanyol");
	anyadirEquipo((char *) "Real Betis");
	anyadirEquipo((char *) "Eibar SD");		// 14
	anyadirEquipo((char *) "Real Sociedad");	// 15
	anyadirEquipo((char *) "Athletic Club");	// 16
	anyadirEquipo((char *) "RCD Alaves");
	anyadirEquipo((char *) "Malaga FC");
	anyadirEquipo((char *) "Las Palmas");
}



void Liga::printEquipos(){
	int i;
	cout << "Mostrando a los " << N_EQUIPOS << " que forman la liga." << endl;
	for(i=0; i<n_participantes; i++){
		cout << participantes[i].getNombre();
		if(i == N_EQUIPOS - 1){
			cout << "." <<endl;
		}else{
			cout << ", ";
		}
	}
}

bool Liga::tiene_opuesto(Equipo e){
	//Para comprobar si tiene opuesto, antes habría que crear la pareja de opuestos a través de código.
	int i, j;
	for(i=0; i<parejas_opuestas; i++){
		for(j=0; j<2; j++){
			if(strcmp(opuestos[i][j].getNombre(), e.getNombre()) == 0){
				return true;
			}
		}
	}
	return false;
}

//Indica si el equipo está entre los registrados en la liga.
bool Liga::esta(char * e){
	int i;
	for(i=0; i<n_participantes; i++){
		if(strcmp(participantes[i].getNombre(), e) == 0){
			return true;
		}
	}
	return false;
}

void Liga::rellenarOpuestosLigaSantander(){
	//Se indican las restricciones que tiene LaLiga.
	opuestos[0][0] = participantes[0]; //RMD
	opuestos[0][1] = participantes[2]; //ATM
	opuestos[1][0] = participantes[1]; //FCB
	opuestos[1][1] = participantes[12]; //ESP
	opuestos[2][0] = participantes[3]; //SEV
	opuestos[2][1] = participantes[13]; //BET
	opuestos[3][0] = participantes[15]; //RSO
	opuestos[3][1] = participantes[16]; //ATH
	parejas_opuestas = 4;
}

//Calcula la posición opuesta para que lso equipos con restricciones no jueguen los dos en casa o fuera simultaneamente.
//El equipo 0 va con el 19 (si son 20)
//Después, se coge el opuesto haciendo una cruz:
//4 3
//5 2
//6 1
//7 0
//Los opuestos son: 7-0, 4-1, 5-2, 6-3. La formula es esa:
int Liga::calcular_opuesto(int num){
	switch(num){
		case 0: return N_EQUIPOS-1;
		case 1: return N_EQUIPOS/2;
		case N_EQUIPOS-1: return 0;
		case N_EQUIPOS/2: return 1;
		default:
			if(num < N_EQUIPOS/2){
				return num + (N_EQUIPOS/2) - 1;	
			}else{
				return num - (N_EQUIPOS/2) + 1;
			}
	}
}

void Liga::sortear(){
	//Deben estar los equipos llenos
	if(n_participantes == N_EQUIPOS){
		int al = time(NULL);
		srand(al);
		//Guardamos a los equipos que no están mezclados aun en tosel y que no tienen restricciones. Los que
		//si tienen restricciones estan guardados en opuestos[][].
		Equipo tosel[N_EQUIPOS];
		//Indicamos que esa posición no esté cogida.
		bool selec[N_EQUIPOS];
		//ne indica cuantos equipos no tienen restricciones.
		int i, ne = 0;

		//Se cogen los equipos que no tienen restricciones
		for(i=0; i<N_EQUIPOS; i++){
			if(!tiene_opuesto(participantes[i])){
				tosel[ne] = participantes[i];
				tosel[ne].mezclado = false;
				ne++;
			}
			selec[i] = false;
		}

		int op, otro;
		bool asignado;
		//1º se sortean los que tienen restricciones:
		for(i=0; i<parejas_opuestas; i++){
			asignado = false;
			while(!asignado){
				//Cogemos al azar un numero para su posición.
				al = rand() % (N_EQUIPOS/2);
				//Cogemos un numero 0 ó 1 para coger un equipo opuesto aleatoriamente.
				otro = rand() % 2;
				if(!selec[al]){
					participantes[al] = opuestos[i][otro];
					participantes[al].mezclado = true;
					selec[al] = true;
					op = calcular_opuesto(al);
					participantes[op] = opuestos[i][(otro+1)%2];
					participantes[op].mezclado = true;
					selec[op] = true;
					asignado = true;
				}
			}
		}

		//2º los que no tienen restricciones
		for(i=0; i<ne; i++){
			if(!tosel[i].mezclado){
				asignado = false;
				while(!asignado){
					al = rand() % N_EQUIPOS;
					if(!selec[al]){
						participantes[al] = tosel[i];
						participantes[al].mezclado = true;
						selec[al] = true;
						asignado = true;
					}
				}
			}
		}
		cout << "Equipos de la liga sorteados." << endl;
	}else{
		cout << "No es posible sortear la liga si no hay equipos suficientes." << endl;
	}
}

void Liga::printClasificacion(){
	if(liga_generada){
		int i, j;
		cout << "Mostrando la clasificacion:" << endl;
		for(i=1; i<n_participantes+1; i++){
			cout << i << "º- ";
			for(j=0; j<n_participantes; j++){
				if(participantes[j].getPos() == i){
					cout << participantes[j].getNombre() << endl;
				}
			}
		}
	}
}

void Liga::printLiga(){
	if(liga_generada){
		int i;
		for(i=0; i<N_JORNADAS; i++){
			jornada[i].printJornada();
		}
	}
}

void Liga::printJornada(int n){
	if(liga_generada){
		if(n > 0 && n <= N_JORNADAS){
			jornada[n-1].printJornada();
		}
	}
}

void Liga::printLigaEquipo(char * nombre){
	if(liga_generada){
		if(esta(nombre)){
			cout << endl << "Liga del " << nombre << ":" << endl;
			int i, j;
			for(i=0; i<N_JORNADAS; i++){
				for(j=0; j<N_EQUIPOS; j++){
					if(strcmp(jornada[i].partidos[j].getNombre(), nombre) == 0){
						cout << "Jornada " << (i+1) << ": ";
						if(j % 2 == 0){
							cout << "local\tvs. " << jornada[i].partidos[j+1].getNombre() << endl;
						}else{
							cout << "visitante\tvs. " << jornada[i].partidos[j-1].getNombre() << endl;
						}
					}
				}
			}
		}else{
			cout << "El equipo " << nombre << " no esta en la liga." << endl;
		}
	}
}

//El orden de la liga es (respecto a la primera jornada):
// 4 5
// 3 6
// 2 7
// X 1
//X es el comodín.
void Liga::printOrdenLiga(){
	if(liga_generada){
		cout << endl << "Orden de liga:" <<endl;
		cout << "- " << participantes[0].getNombre() << endl;
		int i;
		for(i=N_EQUIPOS-2; i>=N_EQUIPOS/2; i--){
			cout << "- " << participantes[i].getNombre() <<endl;
		} 
		for(i=(N_EQUIPOS/2) - 1; i>0; i--){
			cout << "- " << participantes[i].getNombre() << endl;
		}
		cout << "Comodin: " << participantes[N_EQUIPOS-1].getNombre() <<endl;
	}
}

void Liga::generarLiga(){
	//Deben estar todas las plazas llenas.
	if(n_participantes == N_EQUIPOS){
		int n_partidos = N_EQUIPOS / 2;
		int i, k;

		//Se ponen los numeros de jornada.
		for(int i=0; i<N_JORNADAS; i++){
			jornada[i].njor = (i+1);
		}

		// 1ª Jornada: se cogen de tal y como venían registrados. Pueden haber sido 
		// alterados por el sorteo.
		for(i=0; i<n_partidos; i++){
			jornada[0].partidos[i*2] = participantes[n_partidos + i];
			jornada[0].partidos[(i*2) + 1] = participantes[n_partidos - 1 - i];
		}	

		// Jornadas impares: en función de la jornada impar anterior. El comodín se mantiene
		// donde estaba y los demás equipos giran en sentido antihorario.
		for(k=2; k<N_EQUIPOS; k+=2){
			jornada[k].partidos[N_EQUIPOS-2] = jornada[k-2].partidos[N_EQUIPOS-2];
			jornada[k].partidos[0] = jornada[k-2].partidos[1];
			jornada[k].partidos[N_EQUIPOS-1] = jornada[k-2].partidos[N_EQUIPOS-4];
			for(i=1; i<n_partidos-1; i++){
				jornada[k].partidos[(i*2)] = jornada[k-2].partidos[(i-1)*2];
			}
			for(i=0; i<n_partidos-1; i++){
				jornada[k].partidos[(i*2)+1] = jornada[k-2].partidos[(i*2)+3];
			}
		}

		// Jornadas pares: en función de la jornada anterior, el comodín pasa arriba a la derecha
		// y el resto de equipos de esa columna (que estaban encima de él), pasan a estar en la otra columna
		// (la derecha), justo debajo del comodín. La otra columna que pasa a la izquierda no se toca.
		for(k=1; k<N_EQUIPOS-1; k+=2){
			jornada[k].partidos[1] = jornada[k-1].partidos[N_EQUIPOS - 2];
			for(i=1; i<n_partidos; i++){
				jornada[k].partidos[(i*2)+1] = jornada[k-1].partidos[(i*2)-2];
			}
			for(i=0; i<n_partidos; i++){
				jornada[k].partidos[(i*2)] = jornada[k-1].partidos[(i*2)+1];
			}
		}


		//PERMUTACIÓN 2 ÚLTIMAS JORNADAS DEL COMODÍN...
		//Para evitar que se jueguen 3 partidos fuera o en casa, se permuta el partido del comodín
		//en las dos ultimas jornadas.
		jornada[N_EQUIPOS-3].intercambiarEquipos(1);
		jornada[N_EQUIPOS-2].intercambiarEquipos(n_partidos);

		//Creación de la vuelta: simplemente se permutan todos los partidos de la primera vuelta.
		for(k=N_EQUIPOS-1; k<N_JORNADAS; k++){
			for(i=0; i<N_EQUIPOS; i+=2){
				jornada[k].partidos[i] = jornada[(k-N_EQUIPOS)+1].partidos[i+1];
				jornada[k].partidos[i+1] = jornada[(k-N_EQUIPOS)+1].partidos[i];
			}
		}
		//Liga generada.
		liga_generada = true;
	}
}
