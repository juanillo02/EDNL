/*
La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del valle del Jerte (Cáceres). Calcula qué canales y de qué longitud
deben construirse partiendo del grafo con las distancias entre las ciudades y asumiendo las siguientes premisas: 
− el coste de abrir cada nuevo canal es casi prohibitivo, luego la solución final debe tener un número mínimo de canales. 
− el Ministerio de Fomento nos subvenciona por Kms de canal, luego los canales deben ser de la longitud máxima posible. 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "particion.h"
#include "alg_grafoPMC.h"

typedef typename GrafoP<int>::tCoste tCoste;

GrafoP<tCoste> KruskallMax(const GrafoP<tCoste> &G);
GrafoP<tCoste> PrimMax(const GrafoP<tCoste>& G);

int main()
{
	int N = 13;	//Numero de canales
	GrafoP<int> Caceres(N);

	Caceres[0][1] = Caceres[1][0] = 1;
	Caceres[1][2] = Caceres[2][1] = 2;
	Caceres[2][3] = Caceres[3][2] = 3;
	Caceres[2][5] = Caceres[5][2] = 4;
	Caceres[2][8] = Caceres[8][2] = 4;
	Caceres[3][4] = Caceres[4][3] = 5;
	Caceres[3][6] = Caceres[6][3] = 5;
	Caceres[3][11] = Caceres[11][3] = 5;
    Caceres[3][9] = Caceres[9][3] = 5;
	Caceres[6][7] = Caceres[7][6] = 6;
	Caceres[7][8] = Caceres[8][7] = 7;
	Caceres[7][10] = Caceres[10][7] = 9;
	Caceres[8][6] = Caceres[6][8] = 8;
	Caceres[9][2] = Caceres[2][9] = 9;
	Caceres[9][10] = Caceres[10][9] = 9;
	Caceres[10][8] = Caceres[8][10] = 12;
	Caceres[10][11] = Caceres[11][10] = 12;
	Caceres[11][0] = Caceres[0][11] = 13;
	Caceres[11][12] = Caceres[12][11] = 13;
	Caceres[12][9] = Caceres[9][12] = 15;

	std::cout << std::endl << "-------------------------------------------------------" << std::endl << std::endl;

	std::cout << "Grafo Normal:" << std::endl << Caceres << std::endl;
	GrafoP<int> Pmin = Prim(Caceres);
	std::cout << "Grafo Prim:" << std::endl << Pmin << std::endl;
	GrafoP<int> Pmax = PrimMax(Caceres);
	std::cout << "Grafo Prim Max:" << std::endl << Pmax << std::endl;
	GrafoP<int> Kmin = Kruskall(Caceres);
	std::cout << "Grafo Kruskall:" << std::endl << Kmin << std::endl;
	GrafoP<int> Kmax = KruskallMax(Caceres);
	std::cout << "Grafo Kruskall Max:" << std::endl << Kmax << std::endl;

	std::cout << std::endl << "-------------------------------------------------------" << std::endl << std::endl;
}

