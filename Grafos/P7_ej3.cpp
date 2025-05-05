/*
Eres el orgulloso dueño de una empresa de distribución. Tu misión radica en distribuir todo tu stock entre las diferentes ciudades en las
que tu empresa dispone de almacén. Tienes un grafo representado mediante la matriz de costes, en el que aparece el coste (por unidad de producto)
de transportar los productos entre las diferentes ciudades del grafo. Pero además resulta que los Ayuntamientos de las diferentes ciudades en las
que tienes almacén están muy interesados en que almacenes tus productos en ellas, por lo que están dispuestos a subvencionarte con un porcentaje
de los gastos mínimos de transporte hasta la ciudad. Para facilitar el problema, consideraremos despreciables los costes de volver el camión a
su base (centro de producción). He aquí tu problema. Dispones de: el centro de producción, nodo origen en el que tienes tu producto (no tiene
almacén), una cantidad de unidades de producto (cantidad), la matriz de costes del grafo de distribución con N ciudades, la capacidad de
almacenamiento de cada una de ellas, el porcentaje de subvención (sobre los gastos mínimos) que te ofrece cada Ayuntamiento. 
Las diferentes ciudades (almacenes) pueden tener distinta capacidad, y además la capacidad total puede ser superior a la cantidad disponible de
producto, por lo que debes decidir cuántas unidades de producto almacenas en cada una de las ciudades. Debes tener en cuenta además las
subvenciones que recibirás de los diferentes Ayuntamientos, las cuales pueden ser distintas en cada uno y estarán entre el 0% y el 100% de los
costes mínimos. La solución del problema debe incluir las cantidades a almacenar en cada ciudad bajo estas condiciones y el coste mínimo total
de la operación de distribución para tu empresa.
*/
#include <iostream>
#include <vector>
#include "alg_grafoPMC.h"
#include "grafoPMC.h"

typedef typename GrafoP<int>::tCoste tCoste;
typedef typename GrafoP<int>::vertice vertice;
//Cambiar la estructura por un vector, donde se guarde la cantidad
struct distribucion
{
    std::vector<vertice> cantidad;
    tCoste CosteMin;
};

distribucion trabajo(GrafoP<int>& G, vertice centro, size_t cantidad, std::vector<vertice>& ciudades, std::vector<float>& subvencion)
{
    size_t n = G.numVert();  // Número de ciudades (nodos) en el grafo
    // Calcular los costes mínimos de transporte desde el centro de producción hacia todas las ciudades
    std::vector<vertice> VC(n);  // Vector de vértices
    std::vector<tCoste> VD = Dijkstra(G, centro, VC);  // Costes mínimos de cada ciudad
    //No se hace DijkstraInv porque no se necesita el coste de camino de vuelta
    for(vertice i = 0; i < n; i++)
    {
        if(VD[i] != GrafoP<int>::INFINITO)
        {
            // Reducir el coste de transporte según la subvención ofrecida por cada ciudad
            VD[i] -= VD[i] * subvencion[i];
        }
    }
    std::vector<vertice> CiuVis(n);  // Cantidades visitadas por cada ciudad
    size_t cantidadTotal = 0;  // Coste total de la distribución
    // Mientras haya producto por distribuir
    while(cantidad > 0)
    {
        tCoste minimo = GrafoP<int>::INFINITO;  // El coste mínimo a considerar
        vertice ciudad = centro;  // Ciudad candidata de distribución
        // Buscar la ciudad con el coste más bajo de transporte
        for(vertice i = 0; i < n; i++)
        {
            if(i != ciudad && VD[i] < minimo && ciudades[i] > 0 && CiuVis[i] == 0)
            {
                ciudad = i;  // Actualizar la ciudad con el coste mínimo
                minimo = VD[i];
            }
        }
        // Verificar si la ciudad tiene suficiente capacidad de almacenamiento
        if(ciudades[ciudad] < cantidad)
        {
            CiuVis[ciudad] = ciudades[ciudad];  // Asignar toda la capacidad disponible
            cantidad -= ciudades[ciudad];  // Reducir la cantidad de producto restante
            cantidadTotal += ciudades[ciudad] * G[centro][ciudad];  // Aumentar el coste total
        } else {
            CiuVis[ciudad] = cantidad;  // Asignar lo que queda del producto
            cantidadTotal += cantidad * G[centro][ciudad];  // Aumentar el coste total
            cantidad = 0;  // Ya no queda producto por distribuir
        }
    }
    // Almacenar los resultados en la estructura de distribución
    distribucion resultado;
    resultado.cantidad = CiuVis;  // Cantidades almacenadas en cada ciudad
    resultado.CosteMin = cantidadTotal;  // Coste mínimo de distribución
    return resultado;  // Retornar el resultado
}

int main() {
    // Crear un grafo de 5 ciudades (nodos)
    size_t n = 5;
    GrafoP<int> G(n);
    // Inicializar la matriz de costes (con INFINITO para caminos no existentes)
    for (vertice i = 0; i < n; i++) {
        for (vertice j = 0; j < n; j++) {
            if (i != j) {
                G[i][j] = 10 * (abs(int(i) - int(j)) + 1);  // Ejemplo de costes arbitrarios entre 10 y 50
            } else {
                G[i][j] = GrafoP<int>::INFINITO;  // No hay costo para ir de una ciudad a sí misma
            }
        }
    }
    // Definir las capacidades de los almacenes (cuánto pueden almacenar las ciudades)
    std::vector<vertice> ciudades = {0, 10, 15, 20, 25};  // Ciudad 0 no tiene almacén, el resto sí
    // Definir los porcentajes de subvención de cada ciudad
    std::vector<float> subvencion = {0.0, 0.2, 0.1, 0.3, 0.25};  // Porcentaje de subvención por ciudad (20%, 10%, 30%, 25%)
    // Centro de producción (nodo de origen, ciudad 0)
    vertice centro = 0;
    // Cantidad total de producto a distribuir (ejemplo: 30 unidades)
    size_t cantidad = 30;
    // Llamada a la función de distribución
    distribucion res = trabajo(G, centro, cantidad, ciudades, subvencion);
    // Mostrar los resultados
    std::cout << "Distribución de producto:\n";
    for (vertice i = 0; i < n; i++)
    {
        std::cout << "Ciudad " << i << " -> " << res.cantidad[i] << " unidades almacenadas\n";
    }
    std::cout << "Coste total de distribución: " << res.CosteMin << "\n";
    return 0;
}
