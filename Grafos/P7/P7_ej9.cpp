/*
Se dispone de dos grafos que representan la matriz de costes para viajes en un determinado país, pero por diferentes medios de transporte
(tren y autobús, por ejemplo). Por supuesto ambos grafos tendrán el mismo número de nodos, N. Dados ambos grafos, una ciudad de origen, una ciudad
de destino y el coste del taxi para cambiar de una estación a otra dentro de cualquier ciudad (se supone constante e igual para todas las
ciudades), implementa un subprograma que calcule el camino y el coste mínimo para ir de la ciudad origen a la ciudad destino.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

struct viaje
{
    tCamino ruta;
    tCoste CosteMin;
};

viaje precio(GrafoP<int>& tren, GrafoP<int>& bus, vertice origen, vertice destino, tCoste taxi)
{
    size_t n = tren.numVert();
    GrafoP<int> G(n*2);
    for(vertice i = 0; i < n*2; i++)
    {
        G[n+i][i] = taxi;
        G[i][n+i] = taxi;
        for(vertice j = 0; j < n; j++)
        {
            G[i][j] = tren[i][j];
            G[n+i][j+n] = bus[i][j];
        }
    }
    vector<vertice> VT(n), VB(n);
    vector<tCoste> V1 = Dijkstra(tren, origen, VT), V2 = Dijkstra(bus, origen, VB);
    vertice o = origen, d = destino;
    tCoste minimo = std::min(V1[d], V1[d+n]);
    vertice v_vehiculo = 1;
    if(V1[destino +  n] < V1[destino])
    {
        d = destino + n;
    }
    minimo = std::min(minimo, V2[destino]);
    if(minimo < V2[destino])
    {
        o = origen + n;
        v_vehiculo = 2;
    }
    minimo = std::min(minimo, V2[destino + n]);
    if(minimo < V2[destino + n])
    {
        o = origen + n;
        d = destino + n;
        v_vehiculo = 2;
    }
    viaje resultado;
    resultado.CosteMin = minimo;
    if(v_vehiculo == 1)
    {
        resultado.ruta = camino<vertice>(o, d, VT);
    }
    else
    {
        resultado.ruta = camino<vertice>(o, d, VB);
    }
    return resultado;
}
