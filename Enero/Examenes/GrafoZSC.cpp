/*
La capital de Zuelandia está alcanzando niveles de toxicidad muy elevados, por ello se ha decretado el cierre a la ciudad como paso de tránsito
hacia otras ciudades. (Para ir de una ciudad a otra no se podrá pasar por C.Zuelandia, pero si se podrá ir si es residente de la misma empleándola
como ciudad destino u origen). Sin embargo esto podria ocasionar traslados mas largos y el consecuente descontento del viajero zuelandes, asi como
un incremento de la contaminacion eb todo el pais. Por esa razon, el gobierno solo tomara esta medida si el coste total adicional en km recorridos
por los conductores zueladeces con motivo de la medida anticontaminacion no exceden a una cantidad de km determinada. Para poder estimar/calcular
el numero total de km adicionales se dispone del numero de viajes diarios que se realizan entre cualquieras dos ciudades de Zuelandia (obviamente,
el numero de viajes diarios podrá ser distintos para dos pares diferentes de ciudades de Zuelandia). Asi pues, dados los siguientes datos: la
capital de Zuelandia, el Grafo con los km de cada carretera del est, los viajes diarios que se estima que se realizan entre todos los pares de
ciudades del pais y el numero maximo del total de km adicionales que se acepta realizar para implementar la medida.
Implementa un subprograma que calcule y devuelva el numero de km adicionales que provocara la implantacion de la medida anticontaminacion
y si debe implementarse dicha medida o no, de acuerdo al criterio anteriormente descrito.
*/

#include <iostream>
#include "alg_grafo_E-S.h"
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct decision
{
    tCoste numkm;
    bool aceptar;
};

decision ZuelandiaSC(GrafoP<int>& G, vertice capital, matriz<int> viaje, int kmadicionales)
{
    size_t n = G.numVert();
    Grafo<int> GSC(n);
    matriz<vertice> MVA(n);
    matriz<tCoste> MCA = Floyd(G, MVA);
    int kmAntes = kmtotales(MCA, viaje, n);
    for(vertice = 0; i < n; i++)
    {
        GSC[i][capital] = GrafoP<int>::INFINITO;
        GSC[capital][i] = GrafoP<int>::INFINITO;
    }
    matriz<vertice> MV(n);
    matriz<tCoste> MC = Floyd(GSC, MV);
    vector<vertice> VV(n), VVI(n);
    vector<tCoste> VD = dijsktra(G, capital, VV), VDI = dijsktraInv(G, capital, VVI);
    for(vertice i = 0; i < n; i++)
    {
        MC[i][capital] = VDI[i];
    }
    MC[capital] = VD;
    decision res;
    res.numKm = kmtotales(MC, viaje, n);
    res.aceptar = (res.numKm < kmadicionales + kmAntes);
    return res;
}


int kmtotales(GrafoP<int>& G, matriz<int> viajes, size_t n)
{
    int suma = 0;
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            if(i != j G[i][j] != GrafoP<int>::INFINITO)
            {
                suma += (G[i][j] * viajes[i][j]);
            }
        }
    }
    return suma;
}