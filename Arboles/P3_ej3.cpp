#include "agen.h"
#include <iostream>
#include <algorithm>
#include <limits>

typedef char tElto;

int alturaRec(const Agen<tElto>& A, typename Agen<tElto>::nodo n) {
    if (n == Agen<tElto>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        int maxAltura = -1;
        Agen<tElto>::nodo hijo = A.hijoIzqdo(n);
        while (hijo != Agen<tElto>::NODO_NULO)
        {
            maxAltura = std::max(maxAltura, alturaRec(A, hijo));
            hijo = A.hermDrcho(hijo);
        }
        return maxAltura + 1;
    }
}

int desequilibrioRec(const Agen<tElto>& A, typename Agen<tElto>::nodo n)
{
    if (n == Agen<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        Agen<tElto>::nodo hijo = A.hijoIzqdo(n);
        // Inicializamos con la altura del primer hijo para evitar valores arbitrarios
        int minAltura = alturaRec(A, hijo);
        int maxAltura = minAltura;
        // Recorrer todos los hijos para encontrar alturas mínimas y máximas
        while (hijo != Agen<tElto>::NODO_NULO)
        {
            int alturaHijo = alturaRec(A, hijo);
            minAltura = std::min(minAltura, alturaHijo);
            maxAltura = std::max(maxAltura, alturaHijo);
            hijo = A.hermDrcho(hijo);
        }
        // Desequilibrio en este nodo
        int desequilibrioNodo = maxAltura - minAltura;
        // Buscar el máximo desequilibrio en los subárboles
        int maxDesequilibrioHijos = 0;
        hijo = A.hijoIzqdo(n);
        while (hijo != Agen<tElto>::NODO_NULO)
        {
            maxDesequilibrioHijos = std::max(maxDesequilibrioHijos, desequilibrioRec(A, hijo));
            hijo = A.hermDrcho(hijo);
        }
        return std::max(desequilibrioNodo, maxDesequilibrioHijos);
    }
}

int desequilibrio(const Agen<tElto>& A)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return desequilibrioRec(A, A.raiz());
    }
}

int main()
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
    int desequilibrios = desequilibrio(A);
    std::cout << "El desequilibrio del árbol es: " << desequilibrios << std::endl;
    return 0;
}