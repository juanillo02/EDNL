/*
Implementa un subprograma que calcule la altura de un árbol binario.
*/

#include "abin.hpp"
#include <iostream>

typedef char T;

int Altura(Abin<T> A);
int AlturaRec(Abin<T> A, Abin<T>::nodo n);

int main()
{
    Abin<T> A;
    int alt = Altura(A);
    std::cout << alt << std::endl;
    return 0;
}

int Altura(Abin<T> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return AlturaRec(A, A.raiz());
    }
}

int AlturaRec(Abin<T> A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(AlturaRec(A, A.hijoIzqdo(n)), AlturaRec(A, A.hijoDrcho(n)));
    }
}