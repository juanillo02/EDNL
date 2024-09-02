/*
Modelizaremos Narnia como una matriz de NxM casillas. Los movimientos del fauno se modernizarán con los movimientos de un caballo del ajedrez.
Dicho de otra forma, cada movimiento del fauno debe ser un movimiento de caballo de ajedrez.
A Narnia se llega a través de su entrada, casilla (0,0), y se marcha uno a través de una única salida, en la casilla (N-1, M-1).
Sería un problema bastante fácil, pero Narnia es un país lleno de peligros, en particular si eres un fauno.
Para empezar, los lugareños han puesto dentro de Narnia una serie de trampas en determinadas casillas, de forma que si pasas por ellas mueres.
Pero no contentos con eso, los habitantes de Narnia han contratado Minos caballeros, que se colocan también en casillas estratégicas.
En este caso, el fauno no muere si cae en una de ellas, pero si muere en caso de caer en alguna de las casillas que rodean al caballero, entre 3 y 8,
dependiendo de su posición, ya que su espada tiene longitud 1.
El problema nos pide dos cosas, la primera saber si el fauno puede hacer de forma segura el camino entre la entrada y la salida de Narnia, y, en caso afirmativo,
cual sería el número mínimo de saltos necesarios para conseguirlo
Dado los siguientes parámetros
• Dimensiones de Narnia N y M.
• Relación de casillas trampa.
• Relación de casillas ocupadas por caballeros.
Implementa una función que calcula y devuelva si el fauno podrá llegar o no a la salida y, en caso afirmativo, el número mínimo de saltos necesarios para conseguirlo.
Nota importante: Es absolutamente necesario definir todos los tipos de datos implicados en la resolución del problema, así como los prototipos de las operaciones utilizadas de los TADs
conocidos y también los prototipos de los algoritmos de grafos visto en clase que se utilicen.
*/
/*
GrafoP<tCoste> G(size_t n): Crea un grafo ponderado representado  mediante una matriz de costes de dimension n
G.numVert(): Devuelve el numero de vertices del grafo
Dijkstra(GrafoP<Tcoste> G, vertice o, vector<vertice> P): Devuelve un vector de tCoste con los costes minimos para ir desde el vertice o hacia cualquier otro vertice
*/

#include "../Grafos/grafoPMC.h"
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/matriz.h"
#include <iostream>
#include <vector>
#include <algorithm>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct fauno
{
    tCoste saltos;
    bool sale;
};

struct casilla
{
    int x, y;
};

vertice CasillaNodo(casilla c, size_t M)
{
    vertice v = (c.x * M) + c.y;
    return v;
}

casilla NodoCasilla(vertice v, size_t M)
{
    casilla c;
    c.x = v/M;
    c.y = v%M;
    return c;
}

bool adyacente(casilla c1, casilla c2)
{
    return (abs(c1.x - c2.x) + abs(c1.y - c2.y) == 1) || abs(c1.x - c2.x) == 1 && abs(c1.y - c2.y) == 1;
}

bool caballo(casilla c1, casilla c2, size_t N, size_t M)
{
    if(c2.x >= 0 && c2.x < N && c2.y >= 0 && c2.y < M)
    {
        if((abs(c1.x - c2.x) == 1 && abs(c1.y - c2.y) == 2) || (abs(c1.x - c2.x) == 2 && abs(c1.y - c2.y) == 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

fauno Laberinto(size_t& N, size_t& M, vector<casilla>& trampas, vector<casilla>& caballeros)
{
    fauno F;
    GrafoP<tCoste> G(N*M);
    for(vertice i = 0; i < N*M; i++)
    {
        for(vertice j = 0; j < N*M; j++)
        {
            if(caballo(NodoCasilla(i, M), NodoCasilla(j, M), N, M))
            {
                G[i][j] = 1;
            }
            else
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
    }
    for(vertice i = 0; i < N*M; i++)
    {
        for(vertice j = 0; j < trampas.size(); j++)
        {
            G[i][CasillaNodo(trampas[j], M)] = GrafoP<int>::INFINITO;
            G[CasillaNodo(trampas[j], M)][i] = GrafoP<int>::INFINITO;
        }
    }
    for(vertice i = 0; i < N*M; i++)
    {
        for(vertice j = 0; j < caballeros.size(); j++)
        {
            if(adyacente(NodoCasilla(i, M), caballeros[j]))
            {
                for(vertice k = 0; k < trampas.size(); k++)
                {
                    G[k][i] = GrafoP<int>::INFINITO;
                    G[i][k] = GrafoP<int>::INFINITO;
                }
            }
        }
    }
    vector<vertice> P(N*M);
    vector<tCoste> D = Dijkstra(G, 0, P);
    if(D[(N*M)-1] != GrafoP<int>::INFINITO)
    {
        F.saltos = D[(N*M)-1];
        F.sale = true;
    }
    else
    {
        F.sale = false;
    }
    return F;
}
