/*
Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación, es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y derecho
similares. Implementa un subprograma que determine si dos árboles binarios son similares.
*/

#include "abin.hpp"
#include <iostream>

typedef char T;

bool Similar(Abin<T> A, Abin<T> B);
bool SimilarRec(Abin<T> A, Abin<T> B, Abin<T>::nodo nA, Abin<T>::nodo nB);

int main()
{
    Abin<T> A, B;
    if(Similar(A, B))
    {
        std::cout << "Es Similar" << std::endl;
    }
    else
    {
        std::cout << "No es Similar" << std::endl;
    }
    return 0;
}

bool Similar(Abin<T> A, Abin<T> B)
{
    if(A.arbolVacio() && B.arbolVacio())
    {
        return true;
    }
    else
    {
        return  SimilarRec(A, B, A.raiz(), B.raiz());
    }
}

bool SimilarRec(Abin<T> A, Abin<T> B, Abin<T>::nodo nA, Abin<T>::nodo nB)
{
    if(nA == Abin<T>::NODO_NULO && nB == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(nA == Abin<T>::NODO_NULO && nB != Abin<T>::NODO_NULO || nA != Abin<T>::NODO_NULO && nB == Abin<T>::NODO_NULO)
        {
            return false;
        }
        else
        {
            return SimilarRec(A, B, A.hijoIzqdo(nA), B.hijoIzqdo(nB)) && SimilarRec(A, B, A.hijoDrcho(nA), B.hijoDrcho(nB));
        }
        
    }
}