/*
Tu  empresa  de  transportes  “PEROTRAVEZUNGRAFO  S.A.”  acaba  de  recibir  la 
lista  de  posibles  subvenciones  del  Ministerio  de  Fomento  en  la  que  una  de  las  más 
jugosas  se  concede  a  las  empresas  cuyo  grafo  asociado  a  su  matriz  de  costes  sea 
acíclico. ¿Puedes pedir esta subvención? 
Implementa un subprograma que a partir de la matriz de costes nos indique si tu 
empresa tiene derecho a dicha subvención.
*/
#include "alg_grafoPMC.h"
#include "grafoPMC.h"

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

bool aciclico(GrafoP<int>& G)
{
    bool subvencion = false;
    size_t n = G.numVert();
    matriz<tCoste> MC = FloydMod(G);
    for(vertice i = 0; i < n; i++)
    {
        if(MC[i][i] == GrafoP<int>::INFINITO)
        {
            subvencion = true;
        }
    }
    return subvencion;
}