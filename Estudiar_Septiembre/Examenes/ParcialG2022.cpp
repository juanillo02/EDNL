/*
La capital de Zuelandia está alcanzando niveles de toxicidad muy elevados, por ello se ha decretado el cierre a la ciudad como paso de tránsito hacia otras ciudades.
(Para ir de una ciudad a otra no se podrá pasar por C.Zuelandia, pero si se podrá ir si es residente de la misma empleándola como ciudad destino u origen).
Sin embargo esto podria ocasionar traslados mas largos y el consecuente descontento del viajero zuelandes, asi como un incremento de la contaminacion eb todo el pais.
Por esa razon, el gobierno solo tomara esta medida si el coste total adicional en km recorridos por los conductores zueladeces con motivo de la medida anticontaminacion
no exceden a una cantidad de km determinada. Para poder estimar/calcular el numero total de km adicionales se dispone del numero de viajes diarios que se realizan entre
cualquieras dos ciudades de Zuelandia (obviamente, el numero de viajes diarios podrá ser distintos para dos pares diferentes de ciudades de Zuelandia).
Asi pues, dados los siguientes datos
    o La capital de Zuelandia
    o El Grafo con los km de cada carretera del est
    o Los viajes diarios que se estima que se realizan entre todos los pares de ciudades del pais
    o El numero maximo del total de km adicionales que se acepta realizar para implementar la medida
Implementa un subprograma que calcule y devuelva el numero de km adicionales que provocara la implantacion de la medida anticontaminacion
y si debe implementarse dicha medida o no, de acuerdo al criterio anteriormente descrito.
*/

#include <iostream>
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct decision
{
    tCoste NumKM;
    bool acepta;
};

tCoste Total(matriz<tCoste> Coste, matriz<int> Viajes, size_t n)
{
    tCoste suma = 0;
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            if(i != j && Coste[i][j] != GrafoP<tCoste>::INFINITO)
            {
                suma += Coste[i][j] * Viajes[i][j];
            }
        }
    }
    return suma;
}

decision ZuelandiaSinCapital(GrafoP<double>& G, vertice capital, matriz<int> NumViajes, double KM)
{
    size_t n = G.numVert();
    GrafoP<int> ZSC(G);
    matriz<vertice> MV(n);
    matriz<tCoste> MF = Floyd(ZSC, MV);
    tCoste KMTotal = Total(MF, NumViajes, n);
    for(vertice i = 0; i < n; i++)
    {
        ZSC[i][capital] = GrafoP<int>::INFINITO;
        ZSC[capital][i] = GrafoP<int>::INFINITO;
    }
    matriz<vertice> MV2(n);
    matriz<tCoste> MF2 = Floyd(ZSC, MV2);
    vector<vertice> V(n), VI(n);
    vector<tCoste> D = Dijkstra(ZSC, capital, V), DI = DijkstraInv(ZSC, capital, VI);
    for(vertice i = 0; i < n; i++)
    {
        MF2[i][capital] = DI[i];
    }
    MF2[capital] = D;
    decision d;
    d.NumKM = Total(MF2, NumViajes, n);
    d.acepta = d.NumKM < KM + KMTotal;
    return d;
}