/*
El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas, Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2
ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2). Se desea construir un puente que una ambas islas. Nuestro problema es elegir el puente a construir entre todos los
posibles, sabiendo que el coste de construcción del puente se considera irrelevante. Por tanto, escogeremos aquel puente que minimice el coste global de viajar entre todas las
ciudades de las dos islas, teniendo en cuenta las siguientes premisas:
1. Se asume que el coste viajar entre las dos ciudades que una el puente es 0.
2. Para poder plantearse las mejoras en el transporte que implica la construcción de un puente frente a cualquier otro, se asume que se realizarán exactamente el
mismo número de viajes entre cualesquiera ciudades del archipiélago. Por ejemplo, se considerará que el número de viajes entre la ciudad P de Fobos y la
Q de Deimos será el mismo que entre las ciudades R y S de la misma isla. Dicho de otra forma, todos los posibles trayectos a realizar dentro del archipiélago son
igual de importantes.
Dadas las matrices de costes directos de Fobos y Deimos y las listas de ciudades costeras de ambas islas, implementa un subprograma que calcule las dos ciudades que
unirá el puente. 
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

struct puente
{
    vertice v1,v2;
};

puente unir(GrafoP<int>& GFobos,GrafoP<int>& GDeimos, vector<vertice> CosterasF , vector<vertice> CosterasD);
tCoste costeGlobal(matriz<tCoste> M,size_t nf, size_t nd);

int main()
{
    GrafoP<int> GFobos("12fobos.txt");
    GrafoP<int> GDeimos("12deimos.txt");
    vector<vertice> CosterasF(2);
    CosterasF[0] = 1; CosterasF[1] = 2;
    vector<vertice> CosterasD(3);
    CosterasD[0] = 0; CosterasD[1] = 1; CosterasD[2] = 2;

    puente p = unir(GFobos,GDeimos,CosterasF,CosterasD);

    cout << "el puente ira desde la ciudad " << p.v1 << " de Fobos, hasta la ciudad " << p.v2 << endl;" de Deimos.";

    return 0;
}

puente unir(GrafoP<int>& GFobos,GrafoP<int>& GDeimos, vector<vertice> CosterasF , vector<vertice> CosterasD)
{
    size_t nf = GFobos.numVert();
    size_t nd = GDeimos.numVert();

    GrafoP<int> G(nf + nd);

    matriz<tCoste> M;
    matriz<vertice> Mver(nf + nd);

    vertice v1,v2;

    for(vertice i = 0 ; i < nf ; i++)
    {
        for(vertice j = 0 ; j < nf ; j++)
        {
            G[i][j] = GFobos[i][j];
        }
    }

    for(vertice i = nf ; i < nf + nd ; i++)
    {
        for(vertice j = nf ; j < nf + nd ; j++)
        {
            G[i][j] = GDeimos[i-nf][j-nf];
        }
    }


    tCoste minimo = GrafoP<int>::INFINITO;
    tCoste coste;
    puente p;

    //normalizamos el vector de costeras en Deimos
    for (size_t i = 0; i < CosterasD.size() ; i++)
    {
        CosterasD[i] = CosterasD[i] + nf;
    }
    cout << CosterasD;
    //buscamos el puente mejor
    for (size_t i = 0; i < CosterasF.size() ; i++)
    {
        for (size_t j = 0; j < CosterasD.size() ; j++)
        {
            
            G[CosterasF[i]][CosterasD[j]] = 0;
            G[CosterasD[j]][CosterasF[i]] = 0;
            M = Floyd(G,Mver);
            //cout << M << endl;
            coste = costeGlobal(M,nf,nd);
            //cout << "COSTE DE LA MATRIZ: " << coste << endl << endl;
            if (coste < minimo)
            {
                minimo = coste;
                v1 = CosterasF[i];
                v2 = CosterasD[j];
            }
            G[CosterasF[i]][CosterasD[j]] = GrafoP<int>::INFINITO;
            G[CosterasD[j]][CosterasF[i]] = GrafoP<int>::INFINITO;
        }
    }

    p.v1 = v1;
    p.v2 = v2;

    return p;
}

tCoste costeGlobal(matriz<tCoste> M,size_t nf, size_t nd)
{
    tCoste sum = 0;
    for(vertice i = 0; i < nf + nd ; i++)
    {
        for(vertice j = 0; j < nf + nd ; j++)
        {
            if(M[i][j] != GrafoP<int>::INFINITO)
            {
                sum = sum + M[i][j];
            }
        }
    } 
    return sum;
}