/*
Parcial 1 - 23/03/2017
Implemente una función que modifique un árbol binario de forma que si el árbol tiene nodos con un solo hijo, se elimine toda la descendencia de dichos nodos.
NOTA: MUY IMPORTANTE EL & EN LOS ARBOLES, PARA PASARLOS POR REFERENCIA Y EL ARBOL QUE ESTÉ EN EL MAIN SEA EL QUE SE CORTA :)
*/

#include <iostream>
#include "../Arboles/abin.h"

typedef char tElto;
using namespace std;

void eliminarSubarbol(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if (n != Abin<tElto>::NODO_NULO)
    {
        eliminarSubarbol(A, A.hijoIzqdo(n));
        eliminarSubarbol(A, A.hijoDrcho(n));
        Abin<tElto>::nodo padre = A.padre(n);
        if (padre != Abin<tElto>::NODO_NULO)
        {
            if (A.hijoIzqdo(padre) == n)
            {
                A.eliminarHijoIzqdo(padre);
            }
            else if (A.hijoDrcho(padre) == n)
            {
                A.eliminarHijoDrcho(padre);
            }
        }
        else
        {
            A.eliminarRaiz(); // Si n es la raíz
        }
    }
}

void eliminarRec(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if (n != Abin<tElto>::NODO_NULO)
    {
        Abin<tElto>::nodo hi = A.hijoIzqdo(n);
        Abin<tElto>::nodo hd = A.hijoDrcho(n);

        // Recorremos primero los hijos
        eliminarRec(A, hi);
        eliminarRec(A, hd);

        // Si tiene solo un hijo, eliminar su único hijo y toda su descendencia
        if ((hi == Abin<tElto>::NODO_NULO && hd != Abin<tElto>::NODO_NULO))
        {
            eliminarSubarbol(A, hd);
        } else if ((hd == Abin<tElto>::NODO_NULO && hi != Abin<tElto>::NODO_NULO))
        {
            eliminarSubarbol(A, hi);
        }
    }
}

void eliminar(Abin<tElto>& A)
{
    if (!A.vacio())
    {
        eliminarRec(A, A.raiz());
    }
}

void imprimirPreorden(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if (n != Abin<tElto>::NODO_NULO)
    {
        cout << A.elemento(n) << " ";
        imprimirPreorden(A, A.hijoIzqdo(n));
        imprimirPreorden(A, A.hijoDrcho(n));
    }
}


int main() {
    Abin<tElto> A;

    // Nivel 1
    A.insertarRaiz('A');
    // Nivel 2
    A.insertarHijoIzqdo(A.raiz(), 'B');
    A.insertarHijoDrcho(A.raiz(), 'C');
    // Nivel 3
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 'D');
    A.insertarHijoDrcho(A.hijoIzqdo(A.raiz()), 'E');
    A.insertarHijoIzqdo(A.hijoDrcho(A.raiz()), 'F');

    // Nivel 4
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 'G');
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 'H');
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoDrcho(A.raiz())), 'I');

    // Nivel 5
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), 'J');
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), 'K');
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoDrcho(A.raiz()))), 'L');

    // Nivel 6
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())))), 'M');

    // Nivel 7
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))))), 'N');

    cout << "Árbol antes de eliminar descendencia (preorden): ";
    imprimirPreorden(A, A.raiz());
    cout << endl;

    eliminar(A);

    cout << "Árbol después de eliminar descendencia (preorden): ";
    imprimirPreorden(A, A.raiz());
    cout << endl;

    return 0;
}