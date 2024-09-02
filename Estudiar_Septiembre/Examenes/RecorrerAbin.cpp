#include "../Abin/abin.hpp"

typedef char T;

bool Recorrer(Abin<T>& A, char n)
{
    if(A.arbolVacio())
    {
        return false;
    }
    else
    {
        return RecorrerRec(A, A.raiz(), n);
    }
}

bool RecorrerRec(Abin<T>& A, Abin<T>::nodo n, char c)
{
    if(n == Abin<T>::NODO_NULO)
    {
        return false;
    }
    else
    {
        if(A.elemento(n) == c)
        {
            return true;
        }
        else
        {
            return RecorrerRec(A, A.hijoIzqdo(n), c) || RecorrerRec(A, A.hijoDrcho(n), c);
        }
    }
}