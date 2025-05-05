/*
Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación, es decir, ambos son vacíos, o en caso contrario, tienen
subárboles izquierdo y derecho similares. Implementa un subprograma que determine si dos árboles binarios son similares.
*/
#include <iostream>
#include "abin.h"

typedef char tElto;

bool similaresRec(Abin<tElto>& A, Abin<tElto>& B, Abin<tElto>::nodo na, Abin<tElto>::nodo nb)
{
    if(na == Abin<tElto>::NODO_NULO && nb == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if((na != Abin<tElto>::NODO_NULO && nb == Abin<tElto>::NODO_NULO) || (na == Abin<tElto>::NODO_NULO && nb != Abin<tElto>::NODO_NULO))
        {
            return false;
        }
        else
        {
            return similaresRec(A, B, A.hijoIzqdo(na), B.hijoIzqdo(nb)) && similaresRec(A, B, A.hijoDrcho(na), B.hijoDrcho(nb));
        }
    }
}

bool similares(Abin<tElto>& A, Abin<tElto>& B)
{
    if(A.vacio() && B.vacio())
    {
        return true;
    }
    else
    {
        return similaresRec(A, B, A.raiz(), B.raiz());
    }
}

int main () 
{ 
   Abin<tElto> A, B; 
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
   B.insertarRaiz('a');
   B.insertarHijoIzqdo(B.raiz(), 'b');
   B.insertarHijoDrcho(B.raiz(), 'g');
   B.insertarHijoIzqdo(B.hijoIzqdo(B.raiz()), 'c');
   B.insertarHijoDrcho(B.hijoIzqdo(A.raiz()), 'e');
   B.insertarHijoIzqdo(B.hijoIzqdo(B.hijoIzqdo(B.raiz())), 'd');
   B.insertarHijoDrcho(B.hijoDrcho(B.hijoIzqdo(B.raiz())), 'f');
   B.insertarHijoIzqdo(B.hijoDrcho(B.raiz()), 'h');
   B.insertarHijoDrcho(B.hijoDrcho(B.raiz()), 'i');
   B.insertarHijoIzqdo(B.hijoDrcho(B.hijoDrcho(B.raiz())), 'j');
   B.insertarHijoDrcho(B.hijoDrcho(B.hijoDrcho(B.raiz())), 'k');
   if(similares(A, B))
   {
        std::cout << "Los arboles son similares";
   }
   else
   {
        std::cout << "Los arboles no son similares";
   }
   return 0;
}