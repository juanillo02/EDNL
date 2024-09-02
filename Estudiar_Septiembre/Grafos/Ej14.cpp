/*
Disponemos de tres grafos (matriz de costes) que representan los costes directos de viajar entre las ciudades de tres de las islas del archipiélago de las Huríes (Zuelandia).
Para poder viajar de una isla a otra se dispone de una serie de puentes que conectan ciudades de las diferentes islas a un precio francamente asequible (por decisión del
Prefecto de las Huríes, el uso de los puentes es absolutamente gratuito).
Si el alumno desea simplificar el problema, puede numerar las N1 ciudades de la isla 1, del 0 al N1-1, las N2 ciudades de la isla 2, del N1 al N1+N2-1, y las N3 de la última, del
N1+ N2 al N1+N2+ N3-1.
Disponiendo de las tres matrices de costes directos de viajar dentro de cada una delas islas, y la lista de puentes entre ciudades de las mismas, calculad los costes mínimos
de viajar entre cualesquiera dos ciudades de estas tres islas. ¡¡¡ QUE DISFRUTÉIS EL VIAJE !!!
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

matriz<tCoste> viajarCosteMin(GrafoP<int>& Gisla1, GrafoP<int>& Gisla2, GrafoP<int>& Gisla3, vector<puente> puentes);

int main ()
{
    GrafoP<int> Gisla1 ("11isla1.txt");
    GrafoP<int> Gisla2 ("11isla2.txt");
    GrafoP<int> Gisla3 ("11isla3.txt");
    vector<puente> puentes(2);
    puentes[0].v1 = 1; puentes[0].v2 = 7;
    puentes[1].v1 = 1; puentes[1].v2 = 3;


    matriz<tCoste> Mcostes = viajarCosteMin(Gisla1,Gisla2,Gisla3,puentes); 

    cout << "Los costes minimos de una ciudad cualquiera a otra cualquira se representa mediante la siguiente matriz: " << endl << Mcostes << endl;

    return 0;
}

matriz<tCoste> viajarCosteMin(GrafoP<int>& Gisla1, GrafoP<int>& Gisla2, GrafoP<int>& Gisla3, vector<puente> puentes)
{
    size_t n1 = Gisla1.numVert(), n2 = Gisla2.numVert(), n3 = Gisla3.numVert();
    GrafoP<int> G(n1+n2+n3);
    //pasamos las ciudades de cada isla al grafo auxiliar
    //isla 1
    for(vertice i = 0 ; i < n1 ; i++)
    {
        for(vertice j = 0 ; j < n1 ; j++ )
        {
            G[i][j] = Gisla1[i][j];
        }
    }
    //isla 2
    for(vertice i = n1 ; i < n1+n2 ; i++)
    {
        for(vertice j = n1 ; j < n1+n2 ; j++)
        {
            G[i][j] = Gisla2[i-n1][j-n1];
        }
    }
    //isla 3
    for(vertice i = n1+n2 ; i < n1+n2+n3 ; i++)
    {
        for(vertice j = n1+n2 ; j < n1+n2+n3 ; j++)
        {
            G[i][j] = Gisla3[i-n1-n2][j-n1-n2];
        }
    }
    //creacion de puentes
    for(size_t i = 0; i < puentes.size() ; i++)
    {
        G[puentes[i].v1][puentes[i].v2] = 0; //el coste de usar los puentes es gratuito
        G[puentes[i].v2][puentes[i].v1] = 0;
    }
    matriz<vertice> Mver(G.numVert());
    return Floyd(G,Mver);
}