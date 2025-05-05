/*
Al dueño de una agencia de transportes se le plantea la siguiente situación. La agencia de viajes ofrece distintas trayectorias combinadas
entre N ciudades españolas utilizando tren y autobús. Se dispone de dos grafos que representan los costes (matriz de costes) de viajar entre
diferentes ciudades, por un lado en tren, y por otro en autobús (por supuesto entre las ciudades que tengan línea directa entre ellas).
Además coincide que los taxis de toda España se encuentran en estos momentos en huelga general, lo que implica que sólo se podrá cambiar de
transporte en una ciudad determinada en la que, por casualidad, las estaciones de tren y autobús están unidas. Implementa una función que
calcule la tarifa mínima (matriz de costes mínimos) de viajar entre cualesquiera de las N ciudades disponiendo del grafo de costes en autobús, 
del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <vector>
#include "matriz.h"
#include <algorithm>
#include <iostream>

using namespace std;
typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
//Viajar solo en tren, solo en bus, o en ambos medios de transporte
matriz<tCoste> tarifa(GrafoP<int>& GT, GrafoP<int>& GA, vertice transbordo)
{
    size_t n = GT.numVert();
    // Costes mínimos en tren y en bus por separado
    matriz<vertice> PTren(n), PBus(n);
    matriz<tCoste> tren = Floyd(GT, PTren);
    matriz<tCoste> bus = Floyd(GA, PBus);
    // Resultado combinado
    matriz<tCoste> resultado(n, GrafoP<int>::INFINITO);
    for (vertice i = 0; i < n; ++i)
    {
        for (vertice j = 0; j < n; ++j)
        {
            // Opción 1: solo tren
            tCoste solo_tren = tren[i][j];
            // Opción 2: solo bus
            tCoste solo_bus = bus[i][j];
            tCoste tren_bus, bus_tren;
            // Opción 3: tren hasta transbordo, luego bus, se obtiene con la fila de Floyd y el transbordo y la columna de Floyd y el transbordo
            if (tren[i][transbordo] != GrafoP<int>::INFINITO && bus[transbordo][j] != GrafoP<int>::INFINITO)
            {
                tren_bus = tren[i][transbordo] + bus[transbordo][j];
            }
            else
            {
                tren_bus = GrafoP<int>::INFINITO;
            }
            // Opción 4: bus hasta transbordo, luego tren, se obtiene con la fila de Floyd y el transbordo y la columna de Floyd y el transbordo
            if (bus[i][transbordo] != GrafoP<int>::INFINITO && tren[transbordo][j] != GrafoP<int>::INFINITO)
            {
                bus_tren = bus[i][transbordo] + tren[transbordo][j];
            }
            else
            {
                bus_tren = GrafoP<int>::INFINITO;
            }
            resultado[i][j] = min({solo_tren, solo_bus, tren_bus, bus_tren});
        }
    }
    return resultado;
}

int main()
{
    size_t N = 5;
    tCoste INF = GrafoP<int>::INFINITO;
    GrafoP<int> GT(N), GA(N);
    // Rellenar GT (tren)
    GT[0][1] = 5; GT[1][2] = 4; GT[2][3] = 3; GT[3][4] = 2;
    GT[0][0] = GT[1][1] = GT[2][2] = GT[3][3] = GT[4][4] = 0;
    // Rellenar GA (bus)
    GA[0][2] = 6; GA[2][4] = 5; GA[1][3] = 7; GA[3][4] = 1;
    GA[0][0] = GA[1][1] = GA[2][2] = GA[3][3] = GA[4][4] = 0;
    vertice transbordo = 2;
    matriz<tCoste> res = tarifa(GT, GA, transbordo);
    cout << "\nMatriz de costes mínimos entre ciudades:\n";
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            if (res[i][j] == INF)
                cout << "INF ";
            else
                cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
