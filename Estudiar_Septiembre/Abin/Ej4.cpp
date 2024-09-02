/*
Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario, definido como el máximo desequilibrio de todos sus nodos. El desequilibrio de un nodo se
define como la diferencia entre las alturas de los subárboles del mismo.
*/

#include "abin.hpp"
#include <iostream>

typedef char T;

int Desequilibrio(Abin<T> A);
int DesequilibrioRec(Abin<T> A, Abin<T>::nodo n);
int AlturaRec(Abin<T> A, Abin<T>::nodo n);

int main()
{
    Abin<T> A;
    int des = Desequilibrio(A);
    std::cout << des << std::endl;
    return 0;
}

int Desequilibrio(Abin<T> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return DesequilibrioRec(A, A.raiz());
    }
}

int DesequilibrioRec(Abin<T> A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return std::max(abs(AlturaRec(A, A.hijoDrcho(n)) - AlturaRec(A, A.hijoIzqdo(n))), std::max(DesequilibrioRec(A, A.hijoDrcho(n)), DesequilibrioRec(A, A.hijoIzqdo(n))));
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