/*
Cuenta nodos nostálgicos (tienen más ancestros que sucesores)
*/
#include "../Arboles/abin.hpp"

typedef char T;

int nostalgico(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        return nostalgicoRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

int nostalgicoRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(sucesores(A, n) < ancestros(A, n))
        {
            return 1 + nostalgicoRec(A, A.hijoIzqdo(n)) + nostalgicoRec(A, A.hijoDrcho(n));
        }
        else
        {
            return nostalgicoRec(A, A.hijoIzqdo(n)) + nostalgicoRec(A, A.hijoDrcho(n));
        }
    }
}

int sucesores(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + sucesores(A, A.hijoDrcho(n)) + sucesores(A, A.hijoIzqdo(n));
    }
}

int ancestros(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + ancestros(A, A.padre(n));
    }
}