/*Implementa un subprograma que calcule el número de nodos de un árbol binario.*/
#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
 
using namespace std; 
 
typedef char tElto; 
const tElto fin = '#';   // Fin de lectura. 

int numNodosRec(const Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + numNodosRec(A, A.hijoIzqdo(n)) + numNodosRec(A, A.hijoDrcho(n));
    }
}

int numNodos(const Abin<tElto>& A)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return numNodosRec(A, A.raiz());
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
   int nodos = numNodos(A);
   cout << "El arbol A tiene " << nodos << " nodos" << endl;
   cout << "Nodos: " << A.tama() << endl;
   return 0;
}