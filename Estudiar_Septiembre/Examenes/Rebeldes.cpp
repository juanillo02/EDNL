/*
    Contar cuantos nodos del árbol booleano A son rebeldes, un nodo es rebelde si es diferente que la mayoría de sus ancestros 
    (si es distinto de lo que sea la mayoría de sus ancestros)

*/

#include "../Abin/abin.hpp"

int Contar(Abin<bool>& A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return ContarRec(A, A.raiz());
    }
}

int ContarRec(Abin<bool>& A, Abin<bool>::nodo n)
{
    if(n == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if((AntecesorIgual(A, n, A.elemento(n))) < (AntecesorDist(A, n, A.elemento(n))))
        {
            return 1 + ContarRec(A, A.hijoIzqdo(n)) + ContarRec(A, A.hijoDrcho(n));
        }
        else
        {
            return ContarRec(A, A.hijoIzqdo(n)) + ContarRec(A, A.hijoDrcho(n));
        }
    }
}


int AntecesorIgual(Abin<bool> A,Abin<bool>::nodo n,bool aux)
{
    if(A.padre(n) == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(A.elemento(A.padre(n)) == aux)
        {
            return 1 + AntecesorIgual(A,A.padre(n),aux);
        }
        else
        {
            return AntecesorIgual(A,A.padre(n),aux);
        }
    }
}

int AntecesorDist(Abin<bool> A,Abin<bool>::nodo n, bool aux)
{
    if(A.padre(n) == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(A.elemento(A.padre(n)) != aux)
        {
            return 1 + AntecesorDist(A,A.padre(n), aux);
        }
        else
        {
            return AntecesorDist(A,A.padre(n), aux);
        }
    }
}