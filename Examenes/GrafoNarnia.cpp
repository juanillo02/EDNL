/*
Modelizaremos Narnia como una matriz de NxM casillas. Los movimientos del fauno se modernizarán con los movimientos de un caballo del ajedrez.
Dicho de otra forma, cada movimiento del fauno debe ser un movimiento de caballo de ajedrez.
A Narnia se llega a través de su entrada, casilla (0,0), y se marcha uno a través de una única salida, en la casilla (N-1, M-1). Sería un problema
bastante fácil, pero Narnia es un país lleno de peligros, en particular si eres un fauno.
Para empezar, los lugareños han puesto dentro de Narnia una serie de trampas en determinadas casillas, de forma que si pasas por ellas mueres.
Pero no contentos con eso, los habitantes de Narnia han contratado Minos caballeros, que se colocan también en casillas estratégicas. En este
caso, el fauno no muere si cae en una de ellas, pero si muere en caso de caer en alguna de las casillas que rodean al caballero, entre 3 y 8,
dependiendo de su posición, ya que su espada tiene longitud 1.
El problema nos pide dos cosas, la primera saber si el fauno puede hacer de forma segura el camino entre la entrada y la salida de Narnia, y,
en caso afirmativo, cual sería el número mínimo de saltos necesarios para conseguirlo
Dado los siguientes parámetros
• Dimensiones de Narnia N y M.
• Relación de casillas trampa.
• Relación de casillas ocupadas por caballeros.
Implementa una función que calcula y devuelva si el fauno podrá llegar o no a la salida y, en caso afirmativo, el número mínimo de
saltos necesarios para conseguirlo.
Nota importante: Es absolutamente necesario definir todos los tipos de datos implicados en la resolución del problema, así como los prototipos de
las operaciones utilizadas de los TADs conocidos y también los prototipos de los algoritmos de grafos visto en clase que se utilicen.
GrafoP<tCoste> G(size_t n): Crea un grafo ponderado representado mediante una matriz de costes de dimension n
G.numVert(): Devuelve el numero de vertices del grafo
Dijkstra(GrafoP<Tcoste> G, vertice o, vector<vertice> P): Devuelve un vector de tCoste con los costes minimos para ir desde el vertice o hacia
cualquier otro vertice
*/
#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "matriz.h"
#include <iostream>
#include <vector>
#include <algorithm>

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct fauno
{
    tCoste saltos;
    bool escapa;
};

struct casilla
{
    int x, y;
};

vertice casillanodo(casilla c, size_t M)
{
    return (c.x * M) + c.y;
}

casilla nodocasilla(vertice v, size_t M)
{
    casilla c;
    c.x = v / M;
    c.y = v % M;
    return c;
}

bool adyacentes(casilla c1, casilla c2)
{
    return (abs(c1.x - c2.x) + abs(c1.y - c2.y) == 1) || (abs(c1.x - c2.x) == 1 && abs(c1.y - c2.y) == 1);
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
    else
    {
        return false;
    }
}


fauno narnia(size_t N, size_t M, std::vector<casilla>& trampa, std::vector<casilla>& caballero)
{
    size_t n = N*M;
    GrafoP<int> G(n);
    for(vertice i = 0; i < n; i++)
    {
        for(vertice j = 0; j < n; j++)
        {
            if(caballo(nodocasilla(i, M), nodocasilla(j, M), N, M))
            {
                G[i][j] = 1;
            }
            else
            {
                G[i][j] = GrafoP<int>::INFINITO;
            }
        }
        for(vertice k = 0; k < trampa.size(); k++)
        {
            G[i][casillanodo(trampa[k], M)] = GrafoP<int>::INFINITO;
            G[casillanodo(trampa[k], M)][i] = GrafoP<int>::INFINITO;
        }
        for(vertice l = 0; l < caballero.size(); l++)
        {
            if(adyacentes(nodocasilla(i, M), caballero[l]))
            {
                for(vertice m = 0; m < n; m++)
                {
                    G[i][m] = GrafoP<int>::INFINITO;
                    G[m][i] = GrafoP<int>::INFINITO;
                }
            }
        }
    }
    vector<vertice> VV(n);
    vector<tCoste> VD = Dijkstra(G, 0, VV);
    fauno res;
    if(VD[(N*M-1)] != GrafoP<int>::INFINITO)
    {
        res.saltos = VD[(N*M)-1];
        res.escapa = true;
    }
    else
    {
        res.escapa = false;
    }
    return res;
}

int main() {
    size_t N = 5, M = 5;

    // Trampas en zonas alejadas
    vector<casilla> trampas = {
        {0, 4}
    };

    // Un solo caballero lejos de la ruta principal
    vector<casilla> caballeros = {
        {2, 2}
    };

    fauno resultado = narnia(N, M, trampas, caballeros);

    if (resultado.escapa) {
        std::cout << "El fauno puede escapar en " << resultado.saltos << " saltos." << std::endl;
    } else {
        std::cout << "El fauno no puede escapar de Narnia." << std::endl;
    }

    return 0;
}
