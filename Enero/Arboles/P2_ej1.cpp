/*
Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación, es decir, ambos son vacíos, o en caso contrario, tienen
subárboles izquierdo y derecho similares. Implementa un subprograma que determine si dos árboles binarios son similares.
*/
#include "abin.hpp"

typedef char T;

bool similares(Abin<T>& A, Abin<T>& B)
{
    if(!(A.arbolVacio() && B.arbolVacio()))
    {
        return similaresRec(A, B, A.raiz(), B.raiz());
    }
    else
    {
        return true;
    }
}

bool similaresRec(Abin<T>& A, Abin<T>& B, Abin<T>::nodo nA, Abin<T>::nodo nB)
{
    if(nA == Abin<T>::NODO_NULO && nB == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if((nA != Abin<T>::NODO_NULO && nB == Abin<T>::NODO_NULO) || (nA == Abin<T>::NODO_NULO && nB != Abin<T>::NODO_NULO))
        {
            return false;
        }
        else
        {
            return similaresRec(A, B, A.hijoIzqdo(nA), B.hijoIzqdo(nB)) && similaresRec(A, B, A.hijoDrcho(nA), B.hijoDrcho(nB));
        }
    }
}