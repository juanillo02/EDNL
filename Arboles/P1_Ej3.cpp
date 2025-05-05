/*Implementa un subprograma que, dados un árbol binario y un nodo del mismo, determine la profundidad de este nodo en dicho árbol.*/
#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
 
using namespace std; 
 
typedef char tElto; 
const tElto fin = '#';   // Fin de lectura. 

int profundidadRec(const Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + profundidadRec(A, A.padre(n));
    }
}

int profundidad(const Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return profundidadRec(A, n);
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
   int nodos = profundidad(A, A.hijoIzqdo(A.hijoDrcho((A.hijoDrcho(A.raiz())))));
   cout << "El arbol A tiene " << nodos << " profundidad" << endl;
   cout << "Nodos: " << A.tama() << endl;
   return 0;
}