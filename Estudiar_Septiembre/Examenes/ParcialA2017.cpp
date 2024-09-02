/*
Parcial 1 - 23/03/2017
Implemente una función que modifique un árbol binario de forma que si el árbol tiene nodos con un solo hijo, se elimine toda la descendencia de dichos nodos.
NOTA: MUY IMPORTANTE EL & EN LOS ARBOLES, PARA PASARLOS POR REFERENCIA Y EL ARBOL QUE ESTÉ EN EL MAIN SEA EL QUE SE CORTA :)
*/

#include "../Abin/abin.hpp"

typedef char T;

void EliminaHijos(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        EliminaHijosRec(A, A.raiz());
    }
}

void EliminaHijosRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if((A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO) || (A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO))
        {
            EliminarDescendencia(A, n);
        }
        if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
        {
            EliminaHijosRec(A, A.hijoIzqdo(n));
            EliminaHijosRec(A, A.hijoDrcho(n));
        }
    }
}

void EliminarDescendencia(Abin<T>& A, Abin<T>::nodo n)
{
    if(n != Abin<T>::NODO_NULO)
    {
        if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
        {
            EliminarDescendencia(A, A.hijoIzqdo(n));
            EliminarDescendencia(A, A.hijoDrcho(n));
            A.eliminarHijoIzqdo(n);
            A.eliminarHijoDrcho(n);
        }
        if(A.hijoIzqdo(n) != Abin<T>::NODO_NULO && A.hijoDrcho(n) == Abin<T>::NODO_NULO)
        {
            EliminarDescendencia(A, A.hijoIzqdo(n));
            A.eliminarHijoIzqdo(n);
        }
        if(A.hijoIzqdo(n) == Abin<T>::NODO_NULO && A.hijoDrcho(n) != Abin<T>::NODO_NULO)
        {
            EliminarDescendencia(A, A.hijoDrcho(n));
            A.eliminarHijoDrcho(n);
        }
    }
}