/*
Implemente una función que modifique un árbol binario de forma que si el árbol tiene nodos con un solo hijo, se elimine toda la descendencia de
dichos nodos. NOTA: MUY IMPORTANTE EL & EN LOS ARBOLES, PARA PASARLOS POR REFERENCIA Y EL ARBOL QUE ESTÉ EN EL MAIN SEA EL QUE SE CORTA :)
*/
#include "../Arboles/abin.hpp"

typedef char T;

void eliminarHijos(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        eliminarHijosRec(A, A.raiz());
    }
}

void eliminarHijosRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
        {
            eliminarHijosRec(A, A.hijoIzqdo(n));
            eliminarHijosRec(A, A.hijoDrcho(n));
        }
        if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
        {
            eliminar(A, A.hijoIzqdo(n), n);
        }
        if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
        {
            eliminar(A, A.hijoDrcho(n), n);
        }
    }
}

void eliminar(Abin<T>& A, Abin<T>::nodo n, Abin<T>::nodo aux)
{
    if( n != Abin<T>::NODO_NULO)
    {
        if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)

        {
            eliminarRec(A, aux, n);
        }
        else
        {
            eliminar(A, A.hijoIzqdo(n), aux);
            eliminar(A, A.hijoDrcho(n), aux);
        }
    }
}

void eliminarRec(Abin<T>& A, Abin<T>::nodo aux, Abin<T>::nodo n)
{
    if(n != aux)
    {
        Abin<T>::nodo naux = A.padre(n);
        if(A.hijoIzqdo(naux) != Abin<T>::NODO_NULO && A.hijoDrcho(naux) != Abin<T>::NODO_NULO)
        {
            A.eliminarHijoIzqdo(naux);
            A.eliminarHijoDrcho(naux);
            eliminarRec(A, aux, naux);
        }
        if(A.hijoIzqdo(naux) != Abin<T>::NODO_NULO && A.hijoDrcho(naux) == Abin<T>::NODO_NULO)
        {
            A.eliminarHijoIzqdo(naux);
            eliminarRec(A, aux, naux);
        }
        if(A.hijoIzqdo(naux) == Abin<T>::NODO_NULO && A.hijoDrcho(naux) != Abin<T>::NODO_NULO)
        {
            A.eliminarHijoDrcho(naux);
            eliminarRec(A, aux, naux);
        }
    }
}