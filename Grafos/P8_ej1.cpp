/*
El archipiélago de Tombuctú, está formado por un número indeterminado de islas, cada una de las cuales tiene, a su vez, un número indeterminado de
ciudades. En cambio, sí es conocido el número total de ciudades de Tombuctú (podemos llamarlo N, por ejemplo). Dentro de cada una de las islas
existen carreteras que permiten viajar entre todas las ciudades de la isla. Se dispone de las coordenadas cartesianas (x, y) de todas y cada 
una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre
cualesquiera dos ciudades del archipiélago. El objetivo de nuestro problema es encontrar qué ciudades de Tombuctú pertenecen a cada una de
las islas del mismo y cuál es el coste mínimo de viajar entre cualesquiera dos ciudades de una misma isla de Tombuctú. Así pues, dados los
siguientes datos:
- Lista de ciudades de Tombuctú representada cada una de ellas por sus coordenadas cartesianas. 
- Matriz de adyacencia de Tombuctú, que indica las carreteras existentes en dicho archipiélago. 
Implementen un subprograma que calcule y devuelva la distribución en islas de las ciudades de Tombuctú, así como el coste mínimo de viajar
entre cualesquiera dos ciudades de una misma isla del archipiélago.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include "grafoMA.h"
#include "grafoPMC.h"
#include "alg_grafoPMC.h"
#include "matriz.h"
#include "particion.h"
//Sin TAD particion, recorrer el grafo y aplicar Wharsal, ya que es el unico que trabaja con matriz de adyacencia.
typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

struct coordenada {
    int x, y;
};

double distancia(const coordenada& c1, const coordenada& c2) {
    return std::sqrt(std::pow(c1.x - c2.x, 2) + std::pow(c1.y - c2.y, 2));
}

struct resultado {
    matriz<double> MR;
    Particion p;

    resultado(size_t N) : MR(N), p(N) {}
};
//Modificar con el resultado
resultado tombuctu(const Grafo& G, std::vector<coordenada>& ciudades) {
    size_t N = G.numVert();
    GrafoP<tCoste> GD(N);
    resultado res(N);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (G[i][j]) {
                GD[i][j] = distancia(ciudades[i], ciudades[j]);
                if (res.p.encontrar(i) != res.p.encontrar(j))
                    res.p.unir(res.p.encontrar(i), res.p.encontrar(j));
            } else {
                GD[i][j] = GrafoP<double>::INFINITO;
            }
        }
    }

    matriz<vertice> MV(N);
    res.MR = Floyd(GD, MV);
    return res;
}

int main() {
    // Supongamos que tenemos 6 ciudades y dos islas:
    // Isla 1: ciudades 0, 1, 2
    // Isla 2: ciudades 3, 4, 5

    Grafo G(6);
    G[0][1] = G[1][0] = true;
    G[1][2] = G[2][1] = true;
    G[3][4] = G[4][3] = true;
    G[4][5] = G[5][4] = true;

    std::vector<coordenada> coords = {
        {0, 0}, {1, 0}, {2, 0},  // Isla 1
        {10, 10}, {11, 10}, {12, 10}  // Isla 2
    };

    resultado res = tombuctu(G, coords);

    std::cout << "Costes minimos dentro de cada isla:\n";
    for (size_t i = 0; i < res.MR.dimension(); ++i) {
        for (size_t j = 0; j < res.MR.dimension(); ++j) {
            if (res.p.encontrar(i) == res.p.encontrar(j)) {
                std::cout << res.MR[i][j] << " ";
            } else {
                std::cout << "INF ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "\nIslas identificadas:\n";
    for (size_t i = 0; i < coords.size(); ++i) {
        std::cout << "Ciudad " << i << " pertenece a isla " << res.p.encontrar(i) << "\n";
    }

    return 0;
}