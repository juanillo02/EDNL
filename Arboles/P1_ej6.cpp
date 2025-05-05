/*Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario, definido como el máximo desequilibrio de todos sus nodos.
El desequilibrio de un nodo se define como la diferencia entre las alturas de los subárboles del mismo. */
#include <iostream> 
#include <fstream> 
#include "abin.h" 
#include "abin_E-S.h" 
 
using namespace std; 
 
typedef char tElto; 
const tElto fin = '#';   // Fin de lectura. 

int altura(Abin<tElto> A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(altura(A, A.hijoIzqdo(n)), altura(A, A.hijoDrcho(n)));
    }
}

int desequilirbioRec(const Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + std::max(abs(altura(A, A.hijoIzqdo(n)) - altura(A, A.hijoDrcho(n))), std::max(desequilirbioRec(A, A.hijoIzqdo(n)), desequilirbioRec(A, A.hijoDrcho(n))));
    }
}

int desequilirbio(const Abin<tElto>& A)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return desequilirbioRec(A, A.raiz());
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
   int nodos = desequilirbio(A);
   cout << "El arbol A tiene " << nodos << " desequilirbio" << endl;
   cout << "Nodos: " << A.tama() << endl;
   return 0;
}