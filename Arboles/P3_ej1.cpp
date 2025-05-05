/*
Implementa un subprograma que dado un árbol general nos calcule su grado.
*/

#include"agen.h"
#include<iostream>

typedef char tElto;

int numHijo(Agen<tElto> A, Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int numero = 0;
        Agen<tElto>::nodo aux = A.hijoIzqdo(n);
        while(aux != Agen<tElto>::NODO_NULO)
        {
            numero ++;
            aux = A.hermDrcho(aux);
        }
        return numero;
    }
}

int gradoRec(Agen<tElto> A, Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int numero = numHijo(A, n);
        Agen<tElto>::nodo aux = A.hijoIzqdo(n);
        while(aux != Agen<tElto>::NODO_NULO)
        {
            numero = std::max(numero, gradoRec(A, aux));
            aux = A.hermDrcho(aux);
        }
        return numero;
    }
}

int grado(Agen<tElto> A)
{
    if(!A.vacio())
    {
        return gradoRec(A, A.raiz());
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
   int grados = grado(A);
   std::cout << "El arbol A es de grado: " << grados << std::endl;
   return 0;
}