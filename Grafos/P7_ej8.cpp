/*
“UN SOLO TRANSBORDO, POR FAVOR”. Este es el título que reza en tu flamante compañía de viajes. Tu publicidad explica, por supuesto, que ofreces
viajes combinados de TREN y/o AUTOBÚS (es decir, viajes en tren, en autobús, o usando ambos), entre N ciudades del país, que ofreces un servicio
inmejorable, precios muy competitivos, y que garantizas ante notario algo que no ofrece ninguno de tus competidores: que en todos tus viajes
COMO MÁXIMO se hará un solo transbordo (cambio de medio de transporte). Bien, hoy es 1 de Julio y comienza la temporada de viajes. 
¡Qué suerte! Acaba de aparecer un cliente en tu oficina. Te explica que quiere viajar entre dos ciudades, Origen y Destino, y quiere saber
cuánto le costará. Para responder a esa pregunta dispones de dos grafos de costes directos (matriz de costes) de viajar entre las N ciudades
del país, un grafo con los costes de viajar en tren y otro en autobús. Implementa un subprograma que calcule la tarifa mínima en estas condiciones. 
Mucha suerte en el negocio, que la competencia es dura.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

tCoste precio(GrafoP<int>& GT, GrafoP<int>&& GA, vertice origen, vertice destino)
{
    size_t nt = GT.numVert(), na = GA.numVert();
    vector<vertice> V1(nt), V2(nt), V3(na), V4(na);
    vector<tCoste> VD1 = Dijkstra(GT, origen, V1), VD2 = Dijkstra(GA, origen, V3), VI1 = DijkstraInv(GT, destino, V2), VI2 = DijkstraInv(GA, destino, V4);
    tCoste minimo = std::min(VD1[destino], VD2[destino]);
    for(vertice i = 0; i < nt; i++)
    {
        if(i != origen || i != destino)
        {
            minimo = std::min(minimo, std::min(suma(VD1[i], VI1[i]), suma(VD2[i], VI2[i])));
        }
    }
    return minimo;
}