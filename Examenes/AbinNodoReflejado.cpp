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

#include <iostream>
#include "../Arboles/abin.h"
#include "../Arboles/abin_E-S.h"

typedef char tElto;

int reflejadoRec(Abin<tElto>& A, Abin<tElto>::nodo ni, Abin<tElto>::nodo nd)
{
    if(ni == Abin<tElto>::NODO_NULO && nd == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        if(ni != Abin<tElto>::NODO_NULO && nd == Abin<tElto>::NODO_NULO)
        {
            return reflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(ni));
        }
        else if(ni == Abin<tElto>::NODO_NULO && nd != Abin<tElto>::NODO_NULO)
        {
            return reflejadoRec(A, A.hijoIzqdo(nd), A.hijoDrcho(nd));
        }
        else if(ni != Abin<tElto>::NODO_NULO && nd != Abin<tElto>::NODO_NULO)
        {
            if(A.elemento(ni) == A.elemento(nd))
            {
                return 2 + reflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(ni)) + reflejadoRec(A, A.hijoIzqdo(nd), A.hijoDrcho(nd));
            }
            else
            {
                return reflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(ni)) + reflejadoRec(A, A.hijoIzqdo(nd), A.hijoDrcho(nd));
            }
        }
    }
}

int reflejado(Abin<tElto>& A)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return reflejadoRec(A, A.hijoIzqdo(A.raiz()), A.hijoDrcho(A.raiz()));
    }
}

int main()
{
    // EJEMPLO 1: árbol con 2 nodos reflejados
    Abin<tElto> A1;
    A1.insertarRaiz('a');
    A1.insertarHijoIzqdo(A1.raiz(), 'b');
    A1.insertarHijoDrcho(A1.raiz(), 'b');
    A1.insertarHijoIzqdo(A1.hijoIzqdo(A1.raiz()), 'c');
    A1.insertarHijoDrcho(A1.hijoIzqdo(A1.raiz()), 'd');
    A1.insertarHijoIzqdo(A1.hijoDrcho(A1.raiz()), 'd');
    A1.insertarHijoDrcho(A1.hijoDrcho(A1.raiz()), 'c');

    std::cout << "Ejemplo 1 - Nodos reflejados: " << reflejado(A1) << std::endl; // Esperado: 2

    // EJEMPLO 2: árbol con 6 nodos reflejados
    Abin<tElto> A2;
    A2.insertarRaiz('a');
    A2.insertarHijoIzqdo(A2.raiz(), 'b');
    A2.insertarHijoDrcho(A2.raiz(), 'b');
    A2.insertarHijoIzqdo(A2.hijoIzqdo(A2.raiz()), 'c');
    A2.insertarHijoDrcho(A2.hijoIzqdo(A2.raiz()), 'c');
    A2.insertarHijoIzqdo(A2.hijoDrcho(A2.raiz()), 'c');
    A2.insertarHijoDrcho(A2.hijoDrcho(A2.raiz()), 'c');

    std::cout << "Ejemplo 2 - Nodos reflejados: " << reflejado(A2) << std::endl; // Esperado: 6

    return 0;
}