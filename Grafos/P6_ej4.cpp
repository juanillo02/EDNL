/*
Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre dos ciudades cualesquiera de un país llamado Zuelandia.
El problema es sencillo pero hay que tener en cuenta unos pequeños detalles: 
a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas y por tanto solo permiten un sentido de la circulación. 
b) Actualmente Zuelandia es un país en guerra. Y de hecho hay una serie de ciudades del país que han sido tomadas por los rebeldes, por lo que no
pueden ser usadas para viajar. 
c) Los rebeldes no sólo se han apoderado de ciertas ciudades del país, sino que también han cortado ciertas carreteras, (por lo que estas
carreteras no pueden ser usadas). 
d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido que absolutamente todos los viajes que se hagan por el país pasen
por la capital del mismo, donde se harán los controles de seguridad pertinentes. 
Dadas estas cuatro condiciones, se pide implementar un subprograma que dados 
• el grafo (matriz de costes) de Zuelandia en situación normal, 
• la relación de las ciudades tomadas por los rebeldes, 
• la relación de las carreteras cortadas por los rebeldes 
• y la capital de Zuelandia, 
calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades zuelandesas en esta situación.
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCoste tCoste;

matriz<tCoste> Zuelandia(GrafoP<int>& Zuelandia, matriz<bool>& carreteras, vector<bool>& ciudades, vertice capital)
{
    //Creo el grafo de Zuelandia
    GrafoP<int> G(Zuelandia);
    //Saco el numero de vertices del grafo
    size_t n = G.numVert();
    //Recorro el grafo y le pongo los costes de las aristas a infinito si la carretera esta cortada y con la ciudad igual
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(carreteras[i][j])
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
        if(ciudades[i])
        {
            for(vertice j = 0; j < n; j++)
            {
                //Cortar filas y columnas del grafo
                G[i][j] = GrafoP<int>::INFINITO;
                G[j][i] = GrafoP<int>::INFINITO;
            }
        }
    }
    //Antes de hacer Floyd hacer vector de vertices.
    vector<vertice> VD(n), VI(n);
    //Para el coste del origen a la capital y de la capital al destino.
    vector<tCoste> vt = Dijkstra(G, capital, VD), vti = DijkstraInv(G, capital, VI);
    //Creamos la matriz que será el resultado
    matriz<tCoste> resultado(n, GrafoP<int>::INFINITO);
    //Recorremos la matriz y le asignamos el coste mínimo de cada arista
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(i != j)
            {
                resultado[i][j] = suma(vt[j], vti[i]);
            }
            else
            {
                resultado[i][j] = 0;
            }
        }
    }
    return resultado;
}