/* Contar descendientes: 'Dado un árbol binario, contar el número de nodos de dicho árbol que tienen 4 descendientes.*/
#include <iostream>
#include "../Arboles/abin.h"
#include "../Arboles/abin_E-S.h"

typedef char tElto;

int Contar(const Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + Contar(A, A.hijoIzqdo(n)) + Contar(A, A.hijoDrcho(n));
    }
}

int DescendientesRec(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        std::cout << "Nodo: " << A.elemento(n) << ", Descendientes: " << Contar(A, n) -1 << std::endl;
        if((Contar(A, n)) - 1 == 4)
        {
            return 1 + DescendientesRec(A, A.hijoIzqdo(n)) + DescendientesRec(A, A.hijoDrcho(n));
        }
        else
        {
            return DescendientesRec(A, A.hijoIzqdo(n)) + DescendientesRec(A, A.hijoDrcho(n));
        }
    }
}

int Descendientes(Abin<tElto>& A)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return DescendientesRec(A, A.raiz());
    }
}

int main()
{
    Abin<tElto> A;
    A.insertarRaiz('A'); // nivel 0
    // Nivel 1
    A.insertarHijoIzqdo(A.raiz(), 'B');
    A.insertarHijoDrcho(A.raiz(), 'C');
    // Nivel 2
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 'D');
    A.insertarHijoDrcho(A.hijoIzqdo(A.raiz()), 'E');
    A.insertarHijoIzqdo(A.hijoDrcho(A.raiz()), 'F');
    A.insertarHijoDrcho(A.hijoDrcho(A.raiz()), 'G');
    // Nivel 3
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 'H');
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 'I');
    A.insertarHijoIzqdo(A.hijoDrcho(A.hijoIzqdo(A.raiz())), 'J');
    // Nivel 4 - Vamos a hacer que 'D' tenga 4 descendientes (5 nodos en su subárbol)
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), 'K');
    A.insertarHijoDrcho(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))), 'L');
    // Nivel 5
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())))), 'M');
    // Nivel 6 (profundidad máxima)
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz()))))), 'N');
    int resultado = Descendientes(A);
    std::cout << "Número de nodos con exactamente 4 descendientes: " << resultado << std::endl;
    return 0;
}