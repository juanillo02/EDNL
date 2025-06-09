/*Implementa un subprograma que devuelva el porcentaje de descendientes propios de un arbol general que sean multiplo de 3*/

#include <iostream>
#include "../Arboles/agen.h"

using namespace std;
typedef size_t tElto;

using namespace std;
typedef float tElto;

float descendientesPropios(Agen<tElto>& A, Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t suma = 0;
        Agen<tElto>::nodo aux = A.hijoIzqdo(n);
        while(aux != Agen<tElto>::NODO_NULO)
        {
            suma++;
            aux = A.hermDrcho(aux);
        }
        aux = A.hijoIzqdo(n);
        while(aux != Agen<tElto>::NODO_NULO)
        {
            suma += descendientesPropios(A, aux);
            aux = A.hermDrcho(aux);
        }
        return suma;
    }
}

float totalNodos(Agen<tElto>& A, Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t suma = 1;
        Agen<tElto>::nodo aux = A.hijoIzqdo(n);
        while(aux != Agen<tElto>::NODO_NULO)
        {
            suma += totalNodos(A, A.hijoIzqdo(n));
            aux = A.hermDrcho(aux);
        }
        return suma;
    }
}

float descendientesRec(Agen<tElto>& A, Agen<tElto>::nodo n)
{
    if(n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        size_t suma = 0, propios = descendientesPropios(A, n);
        if(propios % 3 == 0 && propios != 0)
        {
            suma++;
        }
        Agen<tElto>::nodo aux = A.hijoIzqdo(n);
        while(aux != Agen<tElto>::NODO_NULO)
        {
            suma += descendientesRec(A, aux);
            aux = A.hermDrcho(aux);
        }
        return suma;
    }
}

float descendientes(Agen<tElto>& A)
{
    if(A.raiz() != Agen<tElto>::NODO_NULO)
    {
        return (descendientesRec(A, A.raiz())) / totalNodos(A, A.raiz()) * 100;
    }
    else
    {
        return 0;
    }
}

int main() {
    Agen<tElto> A;

    A.insertarRaiz(1);

    A.insertarHijoIzqdo(A.raiz(), 3);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 6);
    A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz())), 9);

    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 4);

    A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())), 7);

    A.insertarHijoIzqdo(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 5);
    A.insertarHermDrcho(A.hijoIzqdo(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz())))), 8);
    A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz()))))), 11);

    float porcentaje = descendientes(A);
    cout << "Porcentaje de nodos con descendientes propios múltiplos de 3: " 
         << porcentaje << "%" << endl;

    return 0;
}