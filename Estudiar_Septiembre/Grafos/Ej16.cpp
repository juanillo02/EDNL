/*
El archipiélago de las Huríes acaba de ser devastado por un maremoto de dimensiones desconocidas hasta la fecha. La primera consecuencia ha sido que todos y
cada uno de los puentes que unían las diferentes ciudades de las tres islas han sido destruidos. En misión de urgencia las Naciones Unidas han decidido construir el
mínimo número de puentes que permitan unir las tres islas. Asumiendo que el coste de construcción de los puentes implicados los pagará la ONU, por lo que se considera
irrelevante, nuestro problema es decidir qué puentes deben construirse. Las tres islas de las Huríes tienen respectivamente N1, N2 y N3 ciudades, de las cuales C1, C2 y C3 son
costeras (obviamente C1 ≤ N1 , C2 ≤ N2 y C3 ≤ N3) . Nuestro problema es elegir los puentes a construir entre todos los posibles. Por tanto, escogeremos aquellos puentes
que minimicen el coste global de viajar entre todas las ciudades de las tres islas, teniendo en cuenta las siguientes premisas:
1. Se asume que el coste viajar entre las ciudades que unan los puentes es 0.
2. La ONU subvencionará únicamente el número mínimo de puentes necesario para comunicar las tres islas.
3. Para poder plantearse las mejoras en el transporte que implica la construcción de un puente frente a cualquier otro, se asume que se realizarán exactamente el
mismo número de viajes entre cualesquiera ciudades del archipélago. Dicho de otra forma, todos los posibles trayectos a realizar dentro del archipiélago son igual de importantes.
Dadas las matrices de costes directos de las tres islas y las listas de ciudades costeras del archipiélago, implementad un subprograma que calcule los puentes a construir en las
condiciones anteriormente descritas. 
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


vector<puente> unir(GrafoP<int>& Gisla1, GrafoP<int>& Gisla2, GrafoP<int>& Gisla3, vector<vertice> Costeras1,vector<vertice> Costeras2,vector<vertice> Costeras3);  
tCoste costeGlobal(matriz<tCoste> M, size_t n1, size_t n2, size_t n3);

int main()
{
    GrafoP<int> Gisla1("13isla1.txt");
    GrafoP<int> Gisla2("13isla2.txt");
    GrafoP<int> Gisla3("13isla3.txt");

    vector<vertice> Costeras1(2);
    vector<vertice> Costeras2(2);
    vector<vertice> Costeras3(1);

    Costeras1[0] = 0; Costeras1[1] = 1;
    Costeras2[0] = 0; Costeras2[1] = 1;
    Costeras3[0] = 0;

    vector<puente> p = unir(Gisla1,Gisla2,Gisla3,Costeras1,Costeras2,Costeras3);

    cout << "Los puentes a construir van de: " << p[0].v1 << " a " << p[0].v2 << " y de " << p[1].v1 << " a " << p[1].v2 << endl;

    return 0;
}

vector<puente> unir(GrafoP<int>& Gisla1, GrafoP<int>& Gisla2, GrafoP<int>& Gisla3, vector<vertice> Costeras1,vector<vertice> Costeras2,vector<vertice> Costeras3)
{
    size_t n1 = Gisla1.numVert();
    size_t n2 = Gisla2.numVert();
    size_t n3 = Gisla3.numVert();

    GrafoP<int> G(n1 + n2 + n3);

    for(vertice i = 0 ; i < n1 ; i++)
    {
        for(vertice j = 0 ; j < n1 ; j++)
        {
            G[i][j] = Gisla1[i][j];
        }
    }

    for(vertice i = n1 ; i < n1 + n2 ; i++)
    {
        for(vertice j = n1 ; j < n1 + n2 ; j++)
        {
            G[i][j] = Gisla2[i-n1][j-n1];
        }
    }

    for(vertice i = n1 + n2 ; i < n1 + n2 + n3 ; i++)
    {
        for(vertice j = n1 + n2 ; j < n1 + n2 + n3 ; j++)
        {
            G[i][j] = Gisla3[i-n1-n2][j-n1-n2];
        }
    }

    //normalizamos Costeras2 y 3
    for(size_t i = 0 ; i < Costeras2.size() ; i++)
    {
        Costeras2[i] = Costeras2[i] + n1;
    }

    for(size_t i = 0 ; i < Costeras3.size() ; i++)
    {
        Costeras3[i] = Costeras3[i] + n1 + n2;
    }


    matriz<vertice> Mvertice(n1+n2+n3);
    matriz<tCoste> M;

    tCoste minimo = GrafoP<int>::INFINITO;
    tCoste Mactual;
    vertice v1a;
    vertice v2a;
    vertice v1b;
    vertice v2b;

    // Creamos los hipoteticos puentes (Al ser los minimos deberiamos tener unicamente 2 puentes para conectar las 3 islas)
    for(size_t i = 0 ; i < Costeras1.size() ; i++)
    {
        for(size_t j = 0 ; j < Costeras2.size() ; j++)
        {
            for(size_t k = 0 ; k < Costeras3.size() ; k++)
            {
                G[Costeras1[i]][Costeras2[j]] = 0;
                G[Costeras2[j]][Costeras1[i]] = 0;

                G[Costeras1[i]][Costeras3[k]] = 0;
                G[Costeras3[k]][Costeras1[i]] = 0;

                M = Floyd(G,Mvertice);

                Mactual = costeGlobal(M,n1,n2,n3);

                if(Mactual < minimo)
                {
                    minimo = Mactual;
                    v1a = Costeras1[i];
                    v2a = Costeras2[j];
                    v1b = Costeras1[i];
                    v2b = Costeras3[k];
                }
                G[Costeras1[i]][Costeras2[j]] = GrafoP<int>::INFINITO;
                G[Costeras2[j]][Costeras1[i]] = GrafoP<int>::INFINITO;

                G[Costeras1[i]][Costeras3[k]] = GrafoP<int>::INFINITO;
                G[Costeras3[k]][Costeras1[i]] = GrafoP<int>::INFINITO;                
            }
        }
    }
    vector<puente> p(2);
    p[0].v1 = v1a;
    p[0].v2 = v2a;
    p[1].v1 = v1b;
    p[1].v2 = v2b;

    return p;

}

tCoste costeGlobal(matriz<tCoste> M, size_t n1, size_t n2, size_t n3)
{
    tCoste sum = 0;
    for(vertice i = 0 ; i < n1+n2+n3 ; i++)
    {
        for(vertice j = 0 ; j < n1+n2+n3 ; j++)
        {
            if(M[i][j] != GrafoP<int>::INFINITO)
            {
                sum = sum + M[i][j];
            }
        }
    }
    return sum;
}