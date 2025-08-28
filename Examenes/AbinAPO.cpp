/*EsAPO -> Recibe un arbol binario, y devuelve true si es un APO o false si no*/
#include <iostream>
#include <cmath>
#include <limits>
#include "../Arboles/abin.h"

typedef char tElto;

bool EsAPORec(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if(A.hijoDrcho(n) == Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) == Abin<tElto>::NODO_NULO)
        {
            if(A.hijoIzqdo(A.hijoDrcho(A.padre(n))) != Abin<tElto>::NODO_NULO)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else if(A.hijoDrcho(n) == Abin<tElto>::NODO_NULO && A.hijoIzqdo(n) != Abin<tElto>::NODO_NULO)
        {
            return true;
        }
        else if(A.hijoIzqdo(n) == Abin<tElto>::NODO_NULO && A.hijoDrcho(n) != Abin<tElto>::NODO_NULO)
        {
            return false;
        }
        else
        {
            return EsAPORec(A, A.hijoIzqdo(n)) && EsAPORec(A, A.hijoDrcho(n));
        }
    }
}
    

bool Elementos(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if (n == Abin<tElto>::NODO_NULO)
    {
        return true; // Un nodo nulo es considerado AVL
    }
    else
    {
        if(A.elemento(n) < A.elemento(A.hijoIzqdo(n)) && A.elemento(n) < A.elemento(A.hijoDrcho(n)))
        {
            return true;
        }
        else
        {
            return Elementos(A, A.hijoIzqdo(n)) && Elementos(A, A.hijoDrcho(n));
        }
    }
}

bool EsAPO(Abin<tElto>& A)
{
    return Elementos(A, A.raiz()) && EsAPORec(A, A.raiz());
}

int main() {
    Abin<tElto> A1;
    A1.insertarRaiz('M');
    A1.insertarHijoIzqdo(A1.raiz(), 'F');
    A1.insertarHijoDrcho(A1.raiz(), 'T');
    A1.insertarHijoIzqdo(A1.hijoIzqdo(A1.raiz()), 'C');
    A1.insertarHijoDrcho(A1.hijoIzqdo(A1.raiz()), 'H');
    A1.insertarHijoIzqdo(A1.hijoDrcho(A1.raiz()), 'P');
    A1.insertarHijoDrcho(A1.hijoDrcho(A1.raiz()), 'X');

    std::cout << "¿A1 es un APO? " << (EsAPO(A1) ? "Sí" : "No") << std::endl; // Esperado: Sí

    Abin<tElto> A2;
    A2.insertarRaiz('M');
    A2.insertarHijoIzqdo(A2.raiz(), 'F');
    A2.insertarHijoIzqdo(A2.hijoIzqdo(A2.raiz()), 'C');
    A2.insertarHijoIzqdo(A2.hijoIzqdo(A2.hijoIzqdo(A2.raiz())), 'A');

    std::cout << "¿A2 es un APO? " << (EsAPO(A2) ? "Sí" : "No") << std::endl; // Esperado: No

    return 0;
}
