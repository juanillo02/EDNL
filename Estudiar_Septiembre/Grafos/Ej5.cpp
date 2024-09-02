/*
Se dispone de un laberinto de NxN casillas del que se conocen las casillas de entrada y salida del mismo. Si te encuentras en una casilla sólo puedes moverte en las siguientes
cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared
(en caso contrario no sería un verdadero laberinto).
Implementa un subprograma que dados
• N (dimensión del laberinto),
• la lista de paredes del laberinto,
• la casilla de entrada, y
• la casilla de salida,
calcule el camino más corto para ir de la entrada a la salida y su longitud. 
*/

#include <iostream>
#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "alg_grafo_E-S.h"
#include "matriz.h"
#include <vector>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct casilla
{
    int x, y;
};

struct pared
{
    casilla origen, destino;
};

struct path
{
    tCoste costeTotal;
    GrafoP<int>::tCamino OrigenDestino;
};

path laberinto(size_t&, vector<pared>&, casilla&, casilla&);
vertice CasillaToNodo(casilla, size_t);
casilla NodoToCasilla(vertice, size_t);
bool abyacentes (casilla, casilla);

int main()
{
    size_t N = 3; //Tamaño del laberinto 3

    // DEFINICION DE LA PAREDES
    vector<pared> paredes(4);
    pared p1,p2,p3,p4;
    p1.origen.x=0; p1.origen.y=0; p1.destino.x=1; p1.destino.y=0;
    p2.origen.x=1; p2.origen.y=0; p2.destino.x=1; p2.destino.y=1;
    p3.origen.x=1; p3.origen.y=1; p3.destino.x=2; p3.destino.y=1;
    p4.origen.x=1; p4.origen.y=1; p4.destino.x=1; p4.destino.y=2;

    paredes[0]=p1; paredes[1]=p2; paredes[2]=p3; paredes[3]=p4;
    // FIN DEFINICION DE PAREDES

    casilla entrada,salida;
    entrada.x = 0; entrada.y = 0;
    salida.x = 2; salida.y = 0;


    path resultado = laberinto(N,paredes,entrada,salida);

    Lista<vertice>::posicion p = resultado.OrigenDestino.primera();

   std::cout << "El coste minimo para completar el laberinto es de: " << resultado.costeTotal << std::endl << "Ademas el camino a seguir es: ";
   while(p != resultado.OrigenDestino.fin())
   {
        std::cout << resultado.OrigenDestino.elemento(p) << " ";
        p = resultado.OrigenDestino.siguiente(p);
   }

    return 0;
}

path laberinto(size_t& N, vector<pared>& paredes, casilla& entrada, casilla& salida)
{
    GrafoP<int> G(N*N);
    for(vertice i = 0; i < N*N; i++)
    {
        G[i][i] = 0;
        for(vertice j = 0; j < N*N; j++)
        {
            if(abyacentes(NodoToCasilla(i,N),NodoToCasilla(j,N)))
            {
                G[i][j] = 1;
            }
            else
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
        for(size_t i = 0; i < paredes.size(); i++)
        {
            casilla origen = paredes[i].origen;
            casilla destino = paredes[i].destino;
            vertice v1 = CasillaToNodo(origen,N);
            vertice v2 = CasillaToNodo(destino,N);
            G[v1][v2] = GrafoP<int>::INFINITO;
            G[v2][v1] = GrafoP<int>::INFINITO;
        }
        vertice o = CasillaToNodo(entrada,N);
        vertice d = CasillaToNodo(salida,N);
        vector<vertice> P(G.numVert());
        vector<tCoste> D = Dijkstra(G,o,P);
        path C;
        C.costeTotal = D[d];
        GrafoP<tCoste>::tCamino ruta = camino<GrafoP<size_t>::vertice>(o,d,P);
        C.OrigenDestino = ruta;
        return C;
    }
}

vertice CasillaToNodo(casilla c,size_t N)
{
    vertice v = (c.x * N) + c.y;
    return v;
}

casilla NodoToCasilla(vertice v,size_t N)
{
    casilla c;
    c.x = v / N;
    c.y = v % N;
    return c;
}

bool abyacentes (casilla c1, casilla c2)
{
    return (abs(c1.x - c2.x) + abs(c1.y - c2.y) == 1);
}