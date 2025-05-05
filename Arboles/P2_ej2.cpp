/*
Para un árbol binario B, podemos construir el árbol binario reflejado BR cambiando los subárboles izquierdo y derecho en cada nodo.
Implementa un subprograma que devuelva el árbol binario reflejado de uno dado. 
*/

#include <iostream>
#include "abin.h"
#include "abin_E-S.h"

typedef char tElto;

void reflejadoRec(Abin<tElto> A, Abin<tElto>::nodo ni, Abin<tElto>::nodo nd, Abin<tElto> &Refle, Abin<tElto>::nodo naux)
{
    if(ni != Abin<tElto>::NODO_NULO && nd != Abin<tElto>::NODO_NULO)
    {
        Refle.insertarHijoDrcho(naux, A.elemento(ni));
        Refle.insertarHijoIzqdo(naux, A.elemento(nd));
        reflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(ni), Refle, Refle.hijoDrcho(naux));
        reflejadoRec(A, A.hijoIzqdo(nd), A.hijoDrcho(nd), Refle, Refle.hijoIzqdo(naux));
    }
    if(ni != Abin<tElto>::NODO_NULO && nd == Abin<tElto>::NODO_NULO)
    {
        Refle.insertarHijoDrcho(naux, A.elemento(ni));
        reflejadoRec(A, A.hijoIzqdo(ni), A.hijoDrcho(ni), Refle, Refle.hijoDrcho(naux));
    }
    if(ni == Abin<tElto>::NODO_NULO && nd != Abin<tElto>::NODO_NULO)
    {
        Refle.insertarHijoIzqdo(naux, A.elemento(nd));
        reflejadoRec(A, A.hijoIzqdo(nd), A.hijoDrcho(nd), Refle, Refle.hijoIzqdo(naux));
    }
}

Abin<tElto> reflejado(Abin<tElto> A)
{
    if(!A.vacio())
    {
        Abin<tElto> aux;
        aux.insertarRaiz(A.elemento(A.raiz()));
        reflejadoRec(A, A.hijoIzqdo(A.raiz()), A.hijoDrcho(A.raiz()), aux, aux.raiz());
        return aux;
    }
    else
    {
        return A;
    }
}

int main () 
{ 
   Abin<tElto> A; 
   A.insertarRaiz('a');
   A.insertarHijoIzqdo(A.raiz(), 'b');
   A.insertarHijoDrcho(A.raiz(), 'g');
   A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 'c');
   A.insertarHijoDrcho(A.hijoIzqdo(A.raiz()), 'e');
   A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 'd');
   A.insertarHijoDrcho(A.hijoDrcho(A.hijoIzqdo(A.raiz())), 'f');
   A.insertarHijoIzqdo(A.hijoDrcho(A.raiz()), 'h');
   A.insertarHijoDrcho(A.hijoDrcho(A.raiz()), 'i');
   A.insertarHijoIzqdo(A.hijoDrcho(A.hijoDrcho(A.raiz())), 'j');
   A.insertarHijoDrcho(A.hijoDrcho(A.hijoDrcho(A.raiz())), 'k');
   Abin<tElto> refle = reflejado(A);
   imprimirAbin(A);
   imprimirAbin(refle);
   return 0;
}