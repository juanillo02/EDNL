/*
El archipiélago de Tombuctú está formado por un número desconocido de islas, cada una de las cuales tiene, a su vez, un número desconocido de 
ciudades, las cuales tienen en común que todas y cada una de ellas dispone de un aeropuerto. 
Sí que se conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo). Dentro de cada una de las islas existen carreteras
que permiten viajar entre todas las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la opción de comunicación más
económica de implantar será el avión. Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. 
Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. El
objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para poder viajar entre todas las ciudades del archipiélago,
siguiendo los siguientes criterios:
1)Se implantará las mínimas líneas areas posibles.
2)Las líneas aereas escogidas serán las de menor coste.
3)Cualquier línea aerea tendrá mayor coste que cualquier carretera.
Así pues, dados los siguientes datos:
•Lista de ciudades de Tombuctú representada cada una de ellas por sus coordenadas cartesianas.
•Matriz de adyacencia de Tombuctú que indica las carreteras existentes en dicho archipiélago,
Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para comunicar adecuadamente el archipiélago siguiendo los 
criterios anteriormente expuestos.
*/
#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/grafoPMC.h"
#include "../Grafos/matriz.h"
#include "../Grafos/grafoMA.h"
#include "../Grafos/particion.h"
#include "../Grafos/apo.h"
#include <algorithm>
#include <iostream>
#include <cmath>

typedef typename GrafoP<double>::tCoste tCoste;
typedef typename GrafoP<double>::vertice vertice;

struct coordenada
{
    double x, y;
};

struct LineaAerea
{
    coordenada c1, c2;
    tCoste coste;
    LineaAerea() = default;
    LineaAerea(coordenada c1, coordenada c2): c1{c1}, c2{c2}, coste{distancia(c1, c2)} {}
};

inline bool operator<(const LineaAerea& a, const LineaAerea& b) {
    return a.coste < b.coste;
}

tCoste distancia(coordenada c1, coordenada c2)
{
    return std::sqrt(std::pow((c1.x - c2.x), 2) + std::pow((c1.y - c2.y), 2));
}

particion crearparticion(const Grafo<bool> &M)
{
    size_t n = M.numVert();
    particion p(n);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(M[i][j])
            {
                int a = p.encontrar(i), b = p.encontrar(j);
                if(a != b)
                {
                    p.unir(a,b);
                }
            }
            
        }
    }
    return p;
}

std::vector<LineaAerea> Tombuctu(Grafo<bool> MA, std::vector<coordenada> ciudad)
{
    size_t n = MA.numVert();
    GrafoP<tCoste> G(n);
    particion p = crearparticion(MA);
    tCoste max = 0, coste;
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = 0; j < n; j++)
        {
            int a = p.encontrar(i), b = p.encontrar(j);
            if(a != b)
            {
                coste = distancia(ciudad[i], ciudad[j]);
                max = std::max(max, coste);
                G[i][j] = coste;
            }
        }
    }
    GrafoP<double> GLA(n); //CREAR UN GRAFO AUXILIAR PARA CALCULAR LAS MINIMAS LINEAS AEREAS
    for(int i=0; i<n ;i++)
    {
        for(int j=0; j<n ; j++)
        {
            GLA[i][j] = max + distanciaeuclidea(coords[i], coords[j]); //COPIAMOS LOS DATOS TENIENDO EN CUENTA QUE LAS LA SON MAS CARAS QUE CUALQUIER CARRETERA
        }
    }
    GrafoP<double> GLAK(n) = Kruskall(GLA); //HACEMOS KRUSKALL PARA OBTENER EL NUMERO MINIMO DE LINEAS AEREAS CON MENOR COSTE
    std::vector<LineaAerea> aerolineas(n); // aquí guardamos las que realmente añadimos
    for(size_t i = 0; i < n; i++)
    {
        for(size_t j = i+1; j < n; j++)
        {
            if(GLAK[i][j] != GrafoP<double>::INFINITO && G[i][j] == GrafoP<double>::INFINITO)
            {
                int a = p.encontrar(i), b = p.encontrar(j);
                if(a != b) // une islas diferentes
                {
                    aerolineas.push_back(LineaAerea(ciudad[i], ciudad[j]));
                    G[i][j] = G[j][i] = GLAK[i][j];
                    p.unir(a, b);
                }
            }
        }
    }
    return aerolineas; // lista de líneas aéreas añadidas
}

std::ostream& operator<<(std::ostream& os, const coordenada& c) {
    os << "(" << c.x << ", " << c.y << ")";
    return os;
}


int main() {
    // 6 ciudades
    std::vector<coordenada> coords = {
        {0, 0}, {1, 0}, {0, 1}, // isla 1
        {5, 5}, {6, 5}, {5, 6}  // isla 2
    };

    Grafo G(6);
    // Carreteras dentro de isla 1
    G[0][1] = G[1][0] = true;
    G[0][2] = G[2][0] = true;
    G[1][2] = G[2][1] = true;

    // Carreteras dentro de isla 2
    G[3][4] = G[4][3] = true;
    G[3][5] = G[5][3] = true;
    G[4][5] = G[5][4] = true;

    auto resultado = Tombuctu(G, coords);

    std::cout << "Líneas aéreas mínimas necesarias:\n";
    for (auto& la : resultado) {
        std::cout << "Ciudad " << la.c1 << " - Ciudad " << la.c2
                  << " | Distancia: " << la.coste << '\n';
    }
    return 0;
}