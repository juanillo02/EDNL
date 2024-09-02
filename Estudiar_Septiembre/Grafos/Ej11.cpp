/*
“UN SOLO TRANSBORDO, POR FAVOR”. Este es el título que reza en tu flamante compañía de viajes. Tu publicidad explica, por supuesto, que ofreces viajes
combinados de TREN y/o AUTOBÚS (es decir, viajes en tren, en autobús, o usando ambos), entre N ciudades del país, que ofreces un servicio inmejorable, precios muy
competitivos, y que garantizas ante notario algo que no ofrece ninguno de tus competidores: que en todos tus viajes COMO MÁXIMO se hará un solo transbordo
(cambio de medio de transporte).
Bien, hoy es 1 de Julio y comienza la temporada de viajes. ¡Qué suerte! Acaba de aparecer un cliente en tu oficina. Te explica que quiere viajar
entre dos ciudades, Origen y Destino, y quiere saber cuánto le costará.
Para responder a esa pregunta dispones de dos grafos de costes directos (matriz de costes) de viajar entre las N ciudades del país, un grafo con los costes de viajar en tren y
otro en autobús.
Implementa un subprograma que calcule la tarifa mínima en estas condiciones. Mucha suerte en el negocio, que la competencia es dura. 
*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

using namespace std;

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

tCoste Viajar(GrafoP<int>& GTren,GrafoP<int>& GAutobus, vertice origen, vertice destino);

int main()
{
    GrafoP<int> GTren ("8tren.txt");
    GrafoP<int> GAutobus ("8autobus.txt");

    tCoste costeMin = Viajar(GTren,GAutobus,0,3);

    cout << costeMin << endl;

    return 0;
}


tCoste Viajar(GrafoP<int>& GTren,GrafoP<int>& GAutobus, vertice origen, vertice destino)
{
    vector<vertice> pt(GTren.numVert()); vector<vertice> pa(GTren.numVert());
    vector<vertice> pti(GTren.numVert()); vector<vertice> pai(GTren.numVert());
    vector<tCoste> costeTren = Dijkstra(GTren,origen,pt);
    vector<tCoste> costeTrenInv = DijkstraInv(GTren,destino,pti);
    vector<tCoste> costeAutobus = Dijkstra(GAutobus,origen,pa);
    vector<tCoste> costeAutobusInv = DijkstraInv(GAutobus,origen,pai);
    tCoste minimo = min(costeTren[destino],costeAutobus[destino]);
    for(size_t i = 0 ; i < GTren.numVert() ; i++)
    {
        if(i != origen || i != destino)
        {
            minimo = min(minimo, min(suma(costeTren[i],costeAutobusInv[i]),suma(costeAutobus[i],costeTrenInv[i])));
        }
    }
    return minimo;
}