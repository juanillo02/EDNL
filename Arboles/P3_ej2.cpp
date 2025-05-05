/*
Implementa un subprograma que dados un árbol y un nodo dentro de dicho árbol determine la profundidad de éste nodo en el árbol. 
*/

#include"agen.h"
#include<iostream>

typedef char tElto;

int profundidadRec(Agen<tElto> A, Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + profundidadRec(A, A.padre(n));
    }
}

int profundidad(Agen<tElto>& A, Agen<tElto>::nodo n)
{
    if(!A.vacio())
    {
        return profundidadRec(A, n);
    }
    else
    {
        return 0;
    }
}

int main () 
{ 
   Agen<tElto> A; 
   A.insertarRaiz('a');
   A.insertarHijoIzqdo(A.raiz(), 'b');
   A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 'g');
   A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 'c');
   A.insertarHermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 'e');
   A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 'd');
   A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz())), 'f');
   A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())), 'h');
   A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())), 'i');
   A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())))), 'j');
   A.insertarHermDrcho(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz()))))), 'k');
   int profundidades = profundidad(A, A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))));
   std::cout << "La profundidad del arbol es: " << profundidades << std::endl;
   return 0;
}