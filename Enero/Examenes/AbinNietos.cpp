/*
    Contar cuantos nodos del árbol A tienen exactamente 3 nietos.
*/
#include "../Arboles/abin.hpp"

typedef char T;

int nietos(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        return nietosRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

int nietosRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        Abin<T>::nodo ni = A.hijoIzqdo(n), nd = A.hijoDrcho(n);
        if((ni != Abin<T>::NODO_NULO && nd != Abin<T>::NODO_NULO) && ((A.hijoIzqdo(ni) != Abin<T>::NODO_NULO && A.hijoDrcho(ni) == Abin<T>::NODO_NULO && A.hijoIzqdo(nd) == Abin<T>::NODO_NULO && A.hijoDrcho(nd) == Abin<T>::NODO_NULO) || (A.hijoIzqdo(ni) == Abin<T>::NODO_NULO && A.hijoDrcho(ni) != Abin<T>::NODO_NULO && A.hijoIzqdo(nd) == Abin<T>::NODO_NULO && A.hijoDrcho(nd) == Abin<T>::NODO_NULO) || (A.hijoIzqdo(ni) == Abin<T>::NODO_NULO && A.hijoDrcho(ni) == Abin<T>::NODO_NULO && A.hijoIzqdo(nd) != Abin<T>::NODO_NULO && A.hijoDrcho(nd) == Abin<T>::NODO_NULO) || (A.hijoIzqdo(ni) == Abin<T>::NODO_NULO && A.hijoDrcho(ni) == Abin<T>::NODO_NULO && A.hijoIzqdo(nd) == Abin<T>::NODO_NULO && A.hijoDrcho(nd) != Abin<T>::NODO_NULO)))
        {
            return 1 + nietosRec(A, ni) + nietosRec(A, nd);
        }
        else
        {
            return nietosRec(A, ni) + nietosRec(A, nd);
        }
    }
}