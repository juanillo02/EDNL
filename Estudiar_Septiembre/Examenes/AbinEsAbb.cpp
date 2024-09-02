#include <iostream>
#include "../Abin/abin.hpp"

typedef char T;

bool EsAbb(Abin<T>& A)
{
    if(A.arbolVacio())
    {
        return true;
    }
    else
    {
        return EsAbbRec(A, A.raiz(), ' ');
    }
}

bool EsAbbRec(Abin<T>& A, Abin<T>::nodo n, char c)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(EsMenorIzq(A, n, c) && EsMayorDcha(A, n, c))
        {
            return EsAbbRec(A, A.hijoIzqdo(n), c) && EsAbbRec(A, A.hijoDrcho(n), c);
        }
        else
        {
            return false;
        }
    }
}

bool EsMenorIzq(Abin<T>& A, Abin<T>::nodo n, char c)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(A.elemento(n) >= c)
        {
            return false;
        }
        else
        {
            return EsMenorIzq(A, A.hijoIzqdo(n), c) && EsMenorIzq(A, A.hijoDrcho(n), c);
        }
    }
}

bool EsMayorDcha(Abin<T>& A, Abin<T>::nodo n, char c)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(A.elemento(n) <= c)
        {
            return true;
        }
        else
        {
            return EsMayorDcha(A, A.hijoIzqdo(n), c) && EsMayorDcha(A, A.hijoDrcho(n), c);
        }
    }
}