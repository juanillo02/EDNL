/*
Implementa un subprograma que, dados un árbol binario y un nodo del mismo, determine la profundidad de este nodo en dicho árbol.
*/

#include "abin.hpp"
#include <iostream>

typedef char T;

int Profundidad(Abin<T> A, Abin<T>::nodo n);
int ProfundidadRec(Abin<T> A, Abin<T>::nodo n);

int main()
{
    Abin<T> A;
    Abin<T>::nodo n = A.hijoDrcho(A.hijoIzqdo(A.hijoDrcho(A.raiz())));
    int prof = Profundidad(A, n);
    std::cout << prof << std::endl;
    return 0;
}

int Profundidad(Abin<T> A, Abin<T>::nodo n)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return ProfundidadRec(A, n);
    }
}

int ProfundidadRec(Abin<T> A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + ProfundidadRec(A, A.padre(n));
    }
}