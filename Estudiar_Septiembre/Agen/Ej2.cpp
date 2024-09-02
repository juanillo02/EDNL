/*
Implementa un subprograma que dados un árbol y un nodo dentro de dicho árbol determine la profundidad de éste nodo en el árbol. 
*/

#include <iostream>
#include "agen.hpp"

typedef char T;

int profundidad(Agen<T>, Agen<T>::nodo);
int profundidadRec(Agen<T>, Agen<T>::nodo);

int main()
{
    Agen<T> A;
    Agen<T>::nodo n = A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())));
    int g = profundidad(A, n);
    std::cout << "La profundidad del arbol es: " << g << std::endl;
    return 0;
}

int profundidad(Agen<T> A, Agen<T>::nodo n)
{
    if(!(A.raiz() == Agen<T>::NODO_NULO))
    {
        return profundidadRec(A, n);
    }
    else
    {
        return 0;
    }
}

int profundidadRec(Agen<T> A, Agen<T>::nodo n)
{
    if(n == Agen<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + profundidadRec(A, A.padre(n));
    }
}