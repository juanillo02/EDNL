/*
La capital de Zuelandia está alcanzando niveles de toxicidad muy elevados, por ello se ha decretado el cierre a la ciudad como paso de tránsito hacia otras ciudades.
(Para ir de una ciudad a otra no se podrá pasar por C.Zuelandia, pero si se podrá ir si es residente de la misma empleándola como ciudad destino u origen).
Implemente un subprograma que dada la capital y un grafo ponderado con los km de las carreteras existentes entre las ciudades del país,
nos devuelva los caminos resultantes de nuestra nueva política “Sin pasar por la capital, por favor”.
Nota impotante: Se ha de definir todos los tipos de dato, prototipo de las operaciones empleadas en los TADs y también los prototipos de los grafos vistos en clase que se empleen.
*/

#include <iostream>
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

matriz<vertice> ZuelandiaSinCapital(GrafoP<int>& G, vertice capital)
{
    GrafoP<int> ZSC(G);
    size_t n = G.numVert();
    for(vertice i = 0; i < n; i++)
    {
        ZSC[capital][i] = GrafoP<int>::INFINITO;
        ZSC[i][capital] = GrafoP<int>::INFINITO;
    }
    matriz<vertice> MC(n);
    matriz<tCoste> MF = Floyd(ZSC, MC);
    vector<vertice> V1(n), V2(n);
    vector<tCoste> D = Dijkstra(ZSC, capital, V1), DI = DijkstraInv(ZSC, capital, V2);
    for(vertice i = 0; i < n; i++)
    {
        MF[i][capital] = DI[i];
        MC[i][capital] = V2[i];
    }
    MF[capital] = D;
    MC[capital] = V1;
    return MC;
}