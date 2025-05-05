/*Implementa un subprograma que determine si un árbol binario es o no pseudocompleto. En este problema entenderemos que un árbol es
pseudocompleto, si en el penúltimo nivel del mismo cada uno de los nodos tiene dos hijos o ninguno. */
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

int profundidad(Abin<tElto> A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + profundidad(A, A.padre(n));
    }
}

bool pseudocompletoRec(const Abin<tElto>& A, Abin<tElto>::nodo n, int alt)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(profundidad(A, n) == alt - 1)
        {
            if((A.hijoIzqdo(n) == Abin<tElto>::NODO_NULO && A.hijoDrcho(n) == Abin<tElto>::NODO_NULO) || (A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO && A.hijoDrcho(n) != Abin<tElto>::NODO_NULO))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return pseudocompletoRec(A, A.hijoIzqdo(n), alt) && pseudocompletoRec(A, A.hijoDrcho(n), alt);
        }
    }
}

bool pseudocompleto(const Abin<tElto>& A)
{
    if(A.vacio())
    {
        return false;
    }
    else
    {
        int alt = altura(A,  A.raiz());
        return pseudocompletoRec(A, A.raiz(), alt);
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
   if(pseudocompleto(A))
   {
        cout << "El arbol es pseudocompleto";
   }
   else
   {
        cout << "El arbol no es pseudocompleto";
   }
   return 0;
}