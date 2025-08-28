/*
La capital de Zuelandia está alcanzando niveles de toxicidad muy elevados, por ello se ha decretado el cierre a la ciudad como paso de tránsito
hacia otras ciudades. (Para ir de una ciudad a otra no se podrá pasar por C.Zuelandia, pero si se podrá ir si es residente de la misma empleándola
como ciudad destino u origen). Implemente un subprograma que dada la capital y un grafo ponderado con los km de las carreteras existentes entre
las ciudades del país, nos devuelva los caminos resultantes de nuestra nueva política “Sin pasar por la capital, por favor”. Nota impotante: Se
ha de definir todos los tipos de dato, prototipo de las operaciones empleadas en los TADs y también los prototipos de los grafos vistos en clase
que se empleen.
*/
#include <iostream>
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include <vector>
#include <cmath>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

matriz<vertice> ZuelandiaSC(GrafoP<int>& G, vertice capital)
{
    size_t n = G.numVert();
    GrafoP<int> GSC(G);
    for(vertice i = 0; i < n; i++)
    {
        GSC[i][capital] = GrafoP<int>::INFINITO;
        GSC[capital][i] = GrafoP<int>::INFINITO; 
    }
    matriz<vertice> MV(n);
    matriz<tCoste> MC = Floyd(GSC, MV);
    vector<vertice> VV(n), VVI(n);
    vector<tCoste> VD = Dijkstra(G, capital, VV), VI = DijkstraInv(G, capital, VVI);
    for(vertice i = 0; i < n; i++)
    {
        MV[i][capital] = VVI[i];
        MC[i][capital] = VI[i];
    }
    MV[capital] = VV;
    MC[capital] = VD;
    return MV;
}

int main()
{
    // Ejemplo con 4 ciudades (0,1,2,3), 0 la capital
    size_t n = 4;
    GrafoP<tCoste> G(n);

    // Inicializamos INFINITO en grafo
    for(size_t i=0; i<n; i++)
        for(size_t j=0; j<n; j++)
            G[i][j] = (i == j) ? 0 : GrafoP<tCoste>::INFINITO;

    // Carreteras (simétricas)
    G[0][1] = G[1][0] = 10;
    G[1][2] = G[2][1] = 20;
    G[0][2] = G[2][0] = 30;
    G[2][3] = G[3][2] = 40;
    G[1][3] = G[3][1] = 50;

    matriz<vertice> res = ZuelandiaSC(G, 0);
    return 0;
}
