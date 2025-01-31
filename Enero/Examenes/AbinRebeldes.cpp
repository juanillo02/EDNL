/*
Contar cuantos nodos del árbol booleano A son rebeldes, un nodo es rebelde si es diferente que la mayoría de sus ancestros (si es distinto de
lo que sea la mayoría de sus ancestros)
*/
#include "../Arboles/abin.hpp"

int contarnodos(Abin<bool>& A)
{
    if(!A.arbolVacio())
    {
        return contarnodosRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

int contarnodosRec(Abin<bool>& A, Abin<bool>::nodo n)
{
    if(n == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(contariguales(A, n, A.padre(n)) < (contar(A, n)/2))
        {
            return 1 + contarnodosRec(A, A.hijoIzqdo(n)) + contarnodosRec(A, A.hijoDrcho(n));
        }
        else
        {
            return contarnodosRec(A, A.hijoIzqdo(n)) + contarnodosRec(A, A.hijoDrcho(n));
        }
    }
}

int contariguales(Abin<bool>& A, Abin<bool>::nodo n, bool aux)
{
    if(A.padre(n) == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(A.elemento(A.padre(n)) == aux)
        {
            return 1 + contariguales(A, A.padre(n), aux);
        }
        else
        {
            return contariguales(A, A.padre(n), aux);
        }
    }
}

int contar(Abin<bool>& A, Abin<bool>::nodo n)
{
    if(n == Abin<bool>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + contar(A, A.padre(n));
    }
}