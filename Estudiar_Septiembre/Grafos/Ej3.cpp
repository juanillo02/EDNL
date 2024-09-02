/*
Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre dos ciudades cualesquiera de un país llamado Zuelandia. El problema es sencillo pero
hay que tener en cuenta unos pequeños detalles:
a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas y por tanto solo permiten un sentido de la circulación.
b) Actualmente Zuelandia es un país en guerra. Y de hecho hay una serie de ciudades del país que han sido tomadas por los rebeldes, por lo que no pueden ser usadas para viajar.
c) Los rebeldes no sólo se han apoderado de ciertas ciudades del país, sino que también han cortado ciertas carreteras, (por lo que estas carreteras no pueden ser usadas).
d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido que absolutamente todos los viajes que se hagan por el país pasen por la capital del mismo,
donde se harán los controles de seguridad pertinentes.
Dadas estas cuatro condiciones, se pide implementar un subprograma que dados
• el grafo (matriz de costes) de Zuelandia en situación normal,
• la relación de las ciudades tomadas por los rebeldes,
• la relación de las carreteras cortadas por los rebeldes
• y la capital de Zuelandia,
calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades
zuelandesas en esta situación. 
*/

#include <iostream>
#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

matriz<tCoste> zuelandia(GrafoP<int>& G, vector<bool>& ciudades, matriz<bool>& carreteras,GrafoP<int>::vertice capital);

int main()
{
    GrafoP<int> G(7);
    cout << G << endl;
    //El vertice 0 sera nuestra capital, mientras que el vertice 2 sera conquistada por los rebeldes. Ademas los rebeldes tomaran la carretera del 0 -> 5
    vector<bool> V (G.numVert(),false);
    V[2] = true;
    matriz<bool> M(G.numVert(),false);
    M[0][5] = true;
    matriz<tCoste> Mcostes = zuelandia(G,V,M,0);
    cout << endl << endl << Mcostes << endl;
    return 0;
}

matriz<tCoste> zuelandia(GrafoP<int>& G, vector<bool>& ciudades, matriz<bool>& carreteras, GrafoP<int>::vertice capital)
{
    matriz<tCoste> Mcostes(G.numVert(),GrafoP<int>::INFINITO);
    for(size_t i = 0; i < G.numVert(); i++)
    {
        if(ciudades[i] == true)
        {
            for(size_t j = 0; j < G.numVert(); j++)
            {
                G[i][j] = GrafoP<int>::INFINITO;
                G[j][i] = GrafoP<int>::INFINITO;
            }
        }
    }
    //La ciudad conquistada la ocultamos
    for(size_t i = 0; i < G.numVert(); i++) 
    {
        for(size_t j = 0; j < G.numVert(); j++)
        {
            if(carreteras[i][j] == true)
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
    } 
    //la carretera es cortada
    //matriz<vertice> P(G.numVert());
    //Calcularemos los caminos mas cortos desde la capital hacia cualquier ciudad y desde cualquier ciudad
    vector<vertice> Vv1(G.numVert());
    vector<vertice> Vv2(G.numVert());
    vector<tCoste> Vd = Dijkstra(G,capital,Vv1);
    vector<tCoste> Vdi = DijkstraInv(G,capital,Vv2);
    for(size_t i = 0; i < G.numVert(); i++) 
    { 
        for(size_t j = 0; j < G.numVert(); j++)
        {
            if(i != j)
            {
                Mcostes[i][j] = suma(Vd[j],Vdi[i]);
            }
            else
            {
                Mcostes[i][j] = 0;
            }
        }
    }
    cout << G << endl;
    return Mcostes;
}