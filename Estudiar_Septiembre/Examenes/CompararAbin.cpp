#include "../Abin/abin.hpp"

typedef char T;

bool Similar(Abin<T>& A, Abin<T>& B)
{
    if(!A.arbolVacio() && !B.arbolVacio())
    {
        return SimilarRec(A, B, A.raiz(), B.raiz());
    }
    else
    {
        return true;
    }
}

bool SimilarRec(Abin<T>& A, Abin<T>& B, Abin<T>::nodo na, Abin<T>::nodo nb)
{
    if(na == Abin<T>::NODO_NULO && Abin<T>::NODO_NULO)
    {
        return true;
    }
    else if((na == Abin<T>::NODO_NULO && nb != Abin<T>::NODO_NULO) || (na != Abin<T>::NODO_NULO && nb == Abin<T>::NODO_NULO))
    {
        return false;
    }
    else
    {
        return SimilarRec(A, B, A.hijoIzqdo(na), B.hijoIzqdo(na)) && SimilarRec(A, B, A.hijoDrcho(na), B.hijoDrcho(na));
    }
}