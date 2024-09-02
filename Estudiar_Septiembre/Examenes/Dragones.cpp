/*
Dado un árbol binario, en cuya raíz se encuentra situado un tesoro y cuyos nodos internos pueden contener un dragón o no contener nada,
se pide diseñar un algoritmo que nos indique la hoja del arbol cuyo camino hasta la raíz tenga el menor numero de dragones. En caso de que existan varios caminos
con el mismo numero de dragones, el algoritmo devolvera el que se encuentre mas a la izquierda de todos ellos.
Para ello implementar una función que reciba un árbol binario cuyos nodos almacenan enteros:
1. La raíz contiene el entero 0, que representa al tesoro.
2. Los nodos internos contienen el entero 1 para indicar que en el nodo hay un dragón o el entero 2 para indicar que no hay dragón.
3. En cada hoja se almacena un entero mayor o igual a 3 que no puede estar repetido y devuelva el entero de la hoja del camino seleccionado.
El árbol tiene como mínimo un nodo raíz y un nodo hoja diferente de la raíz.
*/

#include "../Abin/abin.hpp"
#include <iostream>
#include <vector>
#include <limits>

struct Camino
{
    int cont;
    int num;
};

int Hoja(Abin<int>& A, Abin<int>::nodo n, int cont)
{
    if(n != Abin<int>::NODO_NULO)
    {
        if(A.elemento(n) == 1)
        {
            cont++;
        }
        Hoja(A, A.padre(n), cont);
    }
    else
    {
        return cont;
    }
}

int RamaRec(Abin<int>& A, Abin<int>::nodo n, std::vector<Camino>& v)
{
    if(n == Abin<int>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) == Abin<int>::NODO_NULO)
        {
            RamaRec(A, A.hijoIzqdo(n), v);
        }
        if(A.hijoDrcho(n) != Abin<int>::NODO_NULO && A.hijoIzqdo(n) == Abin<int>::NODO_NULO)
        {
            RamaRec(A, A.hijoDrcho(n), v);
        }
        if(A.hijoIzqdo(n) != Abin<int>::NODO_NULO && A.hijoDrcho(n) != Abin<int>::NODO_NULO)
        {
            RamaRec(A, A.hijoIzqdo(n), v);
            RamaRec(A, A.hijoDrcho(n), v);
        }
        if(A.hijoIzqdo(n) == Abin<int>::NODO_NULO && A.hijoDrcho(n) == Abin<int>::NODO_NULO)
        {
            Camino c;
            c.num = A.elemento(n);
            c.cont = Hoja(A, n, 0);
            v.push_back(c);
        }
    }
    int aux = std::numeric_limits<int>::max();
    size_t dev;
    for(size_t i = 0; i < v.size(); i++)
    {
        if(v[i].cont < aux)
        {
            aux = v[i].cont;
            dev = i;
        }
    }
    return v[dev].num;
}

int Rama(Abin<int>& A, std::vector<Camino>& v)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return RamaRec(A, A.raiz(), v);
    }
}

int main()
{
    Abin<int> A;
    std::vector<Camino> v;
    A.insertarRaiz(0);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHijoDrcho(A.raiz(), 1);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 2);
    A.insertarHijoDrcho(A.hijoIzqdo(A.raiz()), 1);
    A.insertarHijoIzqdo(A.hijoDrcho(A.raiz()), 1);
    A.insertarHijoDrcho(A.hijoDrcho(A.raiz()), 1);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 4);
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 1);
    A.insertarHijoIzqdo(A.hijoDrcho(A.hijoIzqdo(A.raiz())), 6);
    A.insertarHijoDrcho(A.hijoDrcho(A.hijoIzqdo(A.raiz())), 7);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoDrcho(A.raiz())), 8);
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoDrcho(A.raiz())), 9);
    A.insertarHijoIzqdo(A.hijoDrcho(A.hijoDrcho(A.raiz())), 10);
    A.insertarHijoDrcho(A.hijoDrcho(A.hijoDrcho(A.raiz())), 11);
    A.insertarHijoIzqdo(A.hijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), 5);
    A.insertarHijoDrcho(A.hijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), 12);
    std::cout << "El nodo es: " << Rama(A, v);
    return 0;
}