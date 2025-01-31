/*
    PRIMER PARCIAL 2022
    Dado un arbol binario de un tipo generico T calcular el numero de nodos que siendo hermanos entre si, 
    tienen la misma raiz y sus subarboles son reflejados (respecto a sus elementos)
    Ejemplo :                             a
                                    b          b
                                c       d   d     c

    Hay 2 nodos reflejados.
    Otro ejemplo :                        a
                                    b          b
                                  c   c      c   c
    
    Hay 6 nodos reflejados.
*/
#include "../Arboles/abin.hpp"

typedef char T;

int contarnodos(Abin<T>& A)
{
    if(!A.arbolVacio())
    {
        return contarnodosRec(A, A.hijoIzqdo(A.raiz()), A.hijoDrcho(A.raiz()));
    }
    else
    {
        return 0;
    }
}

int contarnodosRec(Abin<T>& A, Abin<T>::nodo ni, Abin<T>::nodo nd)
{
    if(ni == Abin<T>::NODO_NULO && nd == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(ni != Abin<T>::NODO_NULO && nd == Abin<T>::NODO_NULO)
        {
            return contarnodosRec(A, A.hijoIzqdo(ni), A.hijoDrcho(ni));
        }
        if(ni == Abin<T>::NODO_NULO && nd != Abin<T>::NODO_NULO)
        {
            return contarnodosRec(A, A.hijoIzqdo(nd), A.hijoDrcho(nd));
        }
        if(ni != Abin<T>::NODO_NULO && nd != Abin<T>::NODO_NULO)
        {
            if(A.elemento(ni) == A.elemento(nd))
            {
                return 2 + contarnodosRec(A, A.hijoIzqdo(ni), A.hijoDrcho(ni)) + contarnodosRec(A, A.hijoIzqdo(nd), A.hijoDrcho(nd));
            }
        }
    }
}