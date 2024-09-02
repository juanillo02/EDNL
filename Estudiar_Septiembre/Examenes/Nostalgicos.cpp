/*
    Cuenta nodos nostálgicos (tienen más ancestros que sucesores)
*/

#include "../Abin/abin.hpp"

typedef char T;

int Nostalgicos(Abin<T>& A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return NostalgicosRec(A, A.raiz());
    }
}

int NostalgicosRec(Abin<T>& A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(Sucesores(A, n) < Ancestros(A, n))
        {
            return 1 + NostalgicosRec(A, A.hijoIzqdo(n)) + NostalgicosRec(A, A.hijoDrcho(n));
        }
        else
        {
            return NostalgicosRec(A, A.hijoIzqdo(n)) + NostalgicosRec(A, A.hijoDrcho(n));
        }
    }
}

int Sucesores(Abin<T> A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return Sucesores(A, A.hijoIzqdo(n)) + Sucesores(A, A.hijoDrcho(n)) + 1;
    }
}

int Ancestros(Abin<T> A, Abin<T>::nodo n)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + Ancestros(A, A.padre(n));
    }
}