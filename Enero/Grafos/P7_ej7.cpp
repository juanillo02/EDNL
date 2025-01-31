/*
Se dispone de dos grafos (matriz de costes) que representan los costes de viajar entre N ciudades españolas utilizando el tren (primer grafo)
y el autobús (segundo  grafo). Ambos grafos representan viajes entre las mismas N ciudades. Nuestro objetivo es hallar el camino de coste mínimo
para viajar entre dos ciudades concretas del grafo, origen y destino, en las siguientes condiciones: La ciudad origen sólo dispone de transporte
por tren, la ciudad destino sólo dispone de transporte por autobús, el sector del taxi, bastante conflictivo en nuestros problemas, sigue en
huelga, por lo que únicamente es posible cambiar de transporte en dos ciudades del grafo, cambio1 y cambio2, donde las estaciones de tren y
autobús están unidas. Implementa un subprograma que calcule la ruta y el coste mínimo para viajar entre las ciudades Origen y Destino en estas
condiciones.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
typedef typename GrafoP<int>::tCamino tCamino;

struct camino
{
    tCoste costeMin;
    tCamino ruta
};

camino viaje(GrafoP<int>& GT, GrafoP<int>& GA, vertice origen, vertice destino, vertice cambio1, vertice cambio2)
{
    size_t n = GT.numVert();
    vector<vertice> VD(n), VI(N);
    vector<tCoste> VDD = dijsktra(GT, origen, VD), VDI = dijkstraInv(GA, destino, VD);
    camino resultado;
    if(VDD[cambio1] + VDI[cambio1] < VDD[cambio2] + VDI[cambio2])
    {
        resultado.costeMin = VDD[cambio1] + VDI[cambio1];
        tCamino ruta1 = camino<GrafoP<size_t>::vertice>(origen, cambio1, VD);
        tCamino ruta2 = caino<GrafoP<size_t>:::vertice>(destino, cambio1, VI);
        lista<size_t> posicion = ruta2.primera();
        while(posicion != ruta2.fin())
        {
            ruta1.insertar(ruta2.elemento(posicion), ruta1.fin());
            posicion = ruta2.siguiente();
        }
        resultado.ruta = ruta1;
    }
    else
    {
        resultado.costeMin = VDD[cambio2] + VDI[cambio2];
        tCamino ruta1 = camino<GrafoP<size_t>::vertice>(origen, cambio2, VD);
        tCamino ruta2 = camino<GrafoP<size_t>::vertice(destino, cambio2, VI);
        lista<size_t> posicion = ruta2.primera();
        while(posicion != ruta2.fin())
        {
            ruta1.insertar(ruta2.elemento(posicion), ruta1.fin());
            posicion = ruta2.siguiente();
        }
        resultado.ruta = ruta1;
    }
    return resultado;
}