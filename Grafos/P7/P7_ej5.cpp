/*
Se dispone de tres grafos que representan la matriz de costes para viajes en un determinado país pero por diferentes medios de transporte,
por supuesto todos los grafos tendrán el mismo número de nodos. El primer grafo representa los costes de ir por carretera, el segundo en tren
y el tercero en avión. Dado un viajero que dispone de una determinada cantidad de dinero, que es alérgico a uno de los tres medios de transporte,
y que sale de una ciudad determinada, implementar un subprograma que determine las ciudades a las que podría llegar nuestro infatigable viajero.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <vector>
#include <iostream>

typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCoste tCoste;

enum TipoViaje {carretera, tren, avion};

GrafoP<int> viajeminimo(GrafoP<int>& G1, GrafoP<int>& G2)
{
    size_t n = G1.numVert();
    GrafoP<int> resultado(n);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            resultado[i][j] = std::min(G1[i][j], G2[i][j]);
        }
    }
    return resultado;
}

vector<vertice> viaje(GrafoP<int>& GC, GrafoP<int>& GT, GrafoP<int>& GA, unsigned int dinero, TipoViaje alergia, vertice origen)
{
    GrafoP<int> Gaux(GC.numVert());
    switch(alergia)
    {
        case carretera: Gaux = viajeminimo(GT, GA); break;
        case tren: Gaux = viajeminimo(GC, GA); break;
        case avion: Gaux = viajeminimo(GC, GT); break;
    }
    vector<vertice> VV(Gaux.numVert());
    vector<tCoste> VD = Dijkstra(Gaux, origen, VV);
    vector<vertice> resultado;
    for(vertice i = 0; i < Gaux.numVert(); i++)
    {
        if(VD[i] <= dinero && i != origen && VD[i] != GrafoP<int>::INFINITO)
        {
            resultado.push_back(i);
        }
    }
    return resultado;
}
//Poder llegar(?)
using namespace std;

// Incluimos la función viaje y el enum TipoViaje desde el código corregido
int main()
{
    const int INF = GrafoP<int>::INFINITO;
    const size_t N = 4;
    // Creamos grafos de coste para carretera, tren y avión con 4 ciudades
    GrafoP<int> C(N), T(N), A(N);
    // Inicializamos todos los costes a INFINITO
    for (vertice i = 0; i < N; ++i)
        for (vertice j = 0; j < N; ++j)
            C[i][j] = T[i][j] = A[i][j] = INF;
    // Costes carretera
    C[0][1] = 10;
    C[1][2] = 20;
    C[2][3] = 15;
    C[0][3] = 50;
    // Costes tren
    T[0][1] = 5;
    T[1][2] = 25;
    T[0][2] = 30;
    T[2][3] = 10;
    // Costes avión
    A[0][3] = 20;
    A[1][3] = 25;
    A[0][2] = 50;
    A[2][3] = 5;
    // Datos del viajero
    vertice origen = 0;               // Ciudad desde la que sale
    unsigned int dinero = 40;         // Presupuesto disponible
    TipoViaje alergia = carretera;    // Es alérgico a viajar por carretera
    // Ejecutamos la función viaje
    vector<vertice> alcanzables = viaje(C, T, A, dinero, alergia, origen);
    // Mostramos resultados
    cout << "Ciudades alcanzables desde ciudad " << origen << " con " << dinero 
         << " unidades de dinero evitando ";
    switch (alergia) {
        case carretera: cout << "carretera"; break;
        case tren: cout << "tren"; break;
        case avion: cout << "avion"; break;
    }
    cout << ":" << endl;
    for (vertice v : alcanzables)
        cout << "- Ciudad " << v << endl;
    return 0;
}
