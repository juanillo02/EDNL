/*
La capital de Zuelandia está alcanzando niveles de toxicidad muy elevados, por ello se ha decretado el cierre a la ciudad como paso de tránsito
hacia otras ciudades. (Para ir de una ciudad a otra no se podrá pasar por C.Zuelandia, pero si se podrá ir si es residente de la misma empleándola
como ciudad destino u origen). Implemente un subprograma que dada la capital y un grafo ponderado con los km de las carreteras existentes entre
las ciudades del país, nos devuelva los caminos resultantes de nuestra nueva política “Sin pasar por la capital, por favor”. Nota impotante: Se
ha de definir todos los tipos de dato, prototipo de las operaciones empleadas en los TADs y también los prototipos de los grafos vistos en clase
que se empleen.
*/
#include <iostream>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

matriz<vertice> ZuelandiaSC(GrafoP<int>& G, vertice capital)
{
    size_t n = G.numVert();
    GrafoP<int> GSC(G);
    for(vertice i = 0; i < n; i++)
    {
        GSC[i][capital] = GrafoP<int>::INFINITO;
        GDC[capital][i] = GrafoP<int>::INFINITO; 
    }
    matriz<vertice> MV(n);
    matriz<tCoste> MC = Floyd(G, MV);
    vector<vertice> VV(n), VVI(n);
    vector<tCoste> VD = dijsktra(G, capital, VV), VI = dijsktraInv(G, capital, VVI);
    for(vertice i = 0; i < n; i++)
    {
        MV[i][capital] = VVI[i];
        MC[i][capital] = VI[i];
    }
    MV[capital] = VV;
    MC[capital] = VD;
    return MV;
}