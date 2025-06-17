/*
Eres el orgulloso dueño de la empresa “Cementos de Zuelandia S.A”. Empresa dedicada a la fabricación y distribución de cemento, sita en la
capital de Zuelandia. Para la distribución del cemento entre tus diferentes clientes (ciudades de Zuelandia) dispones de una flota de
camiones y de una plantilla de conductores zuelandeses. El problema a resolver tiene que ver con el carácter del zuelandés. El zuelandés es
una persona que se toma demasiadas “libertades” en su trabajo, de hecho, tienes fundadas sospechas de que tus conductores utilizan los camiones de
la empresa para usos particulares (es decir indebidos, y a tu costa) por lo que quieres controlar los kilómetros que recorren tus camiones. 
Todos los días se genera el parte de trabajo, en el que se incluyen el número de cargas de cemento (1 carga = 1 camión lleno de cemento) que
debes enviar a cada cliente (cliente = ciudad de Zuelandia). Es innecesario indicar que no todos los días hay que enviar cargas a todos los
clientes, y además, puedes suponer razonablemente que tu flota de camiones es capaz de hacer el trabajo diario. 
Para la resolución del problema quizá sea interesante recordar que Zuelandia es un país cuya especial orografía sólo permite que las carreteras
tengan un sentido de circulación. Implementa una función que dado el grafo con las distancias directas entre las diferentes ciudades
zuelandesas, el parte de trabajo diario, y la capital de Zuelandia, devuelva la distancia total en kilómetros que deben recorrer tus camiones
en el día, para que puedas descubrir si es cierto o no que usan tus camiones en actividades ajenas a la empresa.
*/
#include <iostream>
#include <vector>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"
#include "matriz.h"

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;

struct parte
{
    size_t carga;
    vertice ciudad;
};

tCoste reparto(GrafoP<int>& G, std::vector<parte>& vp, vertice capital)
{
    size_t n = G.numVert();
    std::vector<vertice> VP(n), VPI(n);
    std::vector<tCoste> VD = Dijkstra(G, capital, VP), VI = DijkstraInv(G, capital, VPI);
    tCoste resultado = 0;
    for(vertice i = 0; i < vp.size(); i++)
    {
        resultado += VD[vp[i].ciudad] * vp[i].carga;
        resultado += VI[vp[i].ciudad] * vp[i].carga;
    }
    return resultado;
}

int main()
{
    // Crear el grafo: 5 ciudades (nodos)
    size_t n = 5;
    GrafoP<int> G(n);
    // Inicializar la matriz de costes (distancias entre ciudades)
    for (vertice i = 0; i < n; i++) {
        for (vertice j = 0; j < n; j++) {
            if (i != j) {
                G[i][j] = 10 * (abs(int(i) - int(j)) + 1);  // Ejemplo de costes arbitrarios entre 10 y 50
            } else {
                G[i][j] = GrafoP<int>::INFINITO;  // No hay costo para ir de una ciudad a sí misma
            }
        }
    }
    // Crear el parte de trabajo (cargas y destinos)
    std::vector<parte> vp = {{5, 1}, {3, 3}, {4, 4}};  // Ejemplo: 5 cargas a la ciudad 1, 3 a la ciudad 3, 4 a la ciudad 4
    // Definir la capital (ciudad 0)
    vertice capital = 0;
    // Llamar a la función de reparto para calcular la distancia total
    tCoste resultado = reparto(G, vp, capital);
    // Mostrar el resultado
    std::cout << "La distancia total recorrida por los camiones es: " << resultado << " kilómetros." << std::endl;
    return 0;
}
