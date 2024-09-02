/*
Implementa un subprograma que calcule el número de nodos de un árbol binario.
*/

#include "abin.hpp"
#include <iostream>

typedef char T;

int numeroNodos(Abin<T> A);
int numeroNodosRec(Abin<T> A, Abin<T>::nodo n);

int main()
{
    Abin<T> A;
    int nodos = numeroNodos(A);
    std::cout << nodos << std::endl;
    return 0;
}

int numeroNodos(Abin<T> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return numeroNodosRec(A, A.raiz());
    }
}

int numeroNodosRec(Abin<T> A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + numeroNodosRec(A, A.hijoIzqdo(n)) + numeroNodosRec(A, A.hijoDrcho(n));
    }
}