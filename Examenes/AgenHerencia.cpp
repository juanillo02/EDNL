/*
Dado un árbol general donde sus nodos pueden estar vivos o muertos, implementa una función en C++ que, dado un nodo n de éste con una riqueza
acumulada, simule un reparto entre todos sus herederos. Son herederos de un nodo n sus hijos vivos y sus hijos muertos con descendientes vivos.
Para hacer el reparto se divide en cantidades exactamente iguales entre todos sus herederos y, en cuyo caso no sea exacto, el resto se lo quedará
el erario público. Un nodo seguirá heredando hasta el final, si sigue cumpliendo la condición, o hasta que no quede más riqueza que repartir.
*/
#include "../Arboles/Agen.hpp"
#include <vector>
#include <iostream>

using namespace std;

bool descendientes(Agen<double>& A, Agen<double>::nodo n)
{
    Agen<double>::nodo aux = A.hijoIzqdo(n);
    while(aux != Agen<double>::NODO_NULO)
    {
        if(A.elemento(aux) > 0 || descendientes(A, aux))
        {
            return true;
        }
        aux = A.hermDrcho(aux);
    }
    return false;
}

int Herederos(Agen<double>& A, Agen<double>::nodo n)
{
    int numero = 0;
    Agen<double>::nodo aux = A.hijoIzqdo(n);
    while(aux != Agen<double>::NODO_NULO)
    {
        if(A.elemento(aux) > 0 || descendientes(A, aux))
        {
            numero++;
        }
        aux = A.hermDrcho(aux);
    }
    return numero;
}

void riqueza(Agen<double>& A, Agen<double>::nodo n)
{
    if(n != Agen<double>::NODO_NULO)
    {
        int numero = Herederos(A, n);
        if(numero > 0)
        {
            double total = A.elemento(n);
            double cantidad_entera = static_cast<int>(total / numero);
            double resto = total - cantidad_entera * numero;
            A.elemento(n) = 0; // padre reparte toda su riqueza

            Agen<double>::nodo aux = A.hijoIzqdo(n);
            while(aux != Agen<double>::NODO_NULO)
            {
                if(A.elemento(aux) > 0 || descendientes(A, aux))
                {
                    A.elemento(aux) += cantidad_entera;  // sumamos la parte a cada heredero
                    riqueza(A, aux);                      // recursividad
                }
                aux = A.hermDrcho(aux);
            }

            // resto queda en erario público (no asignado)
        }
        else
        {
            // No hay herederos, el nodo se queda con su riqueza
            // No hacer nada para conservarla
        }
    }
}
void mostrarRiqueza(const Agen<double>& A, typename Agen<double>::nodo n, int nivel = 0) {
    if (n == Agen<double>::NODO_NULO) return;

    // Indentamos para mostrar niveles
    //for (int i = 0; i < nivel; i++) cout << "  ";

    cout << "Nodo nivel " << nivel << ", riqueza: " << A.elemento(n) << "\n";

    // Recorremos hijos (primero hijo izquierdo, luego hermanos derechos)
    mostrarRiqueza(A, A.hijoIzqdo(n), nivel + 1);
    mostrarRiqueza(A, A.hermDrcho(n), nivel);
}

int main()
{
    Agen<double> A;
    A.insertarRaiz(1000);  // raíz con riqueza 1000
    // nivel 1
    A.insertarHijoIzqdo(A.raiz(), 0);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 0);
    A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz())), 0);
    // nivel 2
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 0);
    A.insertarHermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 200);
    A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())), 0);
    A.insertarHijoIzqdo(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 300);
    // nivel 3
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 400);
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 0);
    A.insertarHermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())))), 100);
    // nivel 4
    A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())))), 0);
    cout << "Riqueza antes del reparto:\n";
    mostrarRiqueza(A, A.raiz());
    riqueza(A, A.raiz());
    cout << "\nRiqueza después del reparto:\n";
    mostrarRiqueza(A, A.raiz());
    return 0;
}