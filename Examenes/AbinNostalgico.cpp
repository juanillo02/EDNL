/*Cuenta nodos nostálgicos (tienen más ancestros que sucesores)*/

#include <iostream>
#include "../Arboles/abin.h"

typedef char tElto;
using namespace std;

// --- Funciones auxiliares ---
int ancestros(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + ancestros(A, A.padre(n));
    }
}

int sucesores(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + sucesores(A, A.hijoIzqdo(n)) + sucesores(A, A.hijoDrcho(n));
    }
}

// --- Nueva función para imprimir nodos nostálgicos ---
int NostalgicosRec(Abin<tElto>& A, Abin<tElto>::nodo n)
{
    if(n == Abin<tElto>::NODO_NULO)
    {
        return 0;
    }
    int cuenta = 0;
    int anc = ancestros(A, n);
    int suc = sucesores(A, n);

    if(anc > suc) {
        cout << "Nodo nostálgico: " << A.elemento(n) 
             << " (Ancestros: " << anc-1 << ", Sucesores: " << suc - 1 << ")" << endl;
        cuenta = 1;
    }
    cuenta += NostalgicosRec(A, A.hijoIzqdo(n));
    cuenta += NostalgicosRec(A, A.hijoDrcho(n));
    return cuenta;
}

int Nostalgico(Abin<tElto>& A)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return NostalgicosRec(A, A.raiz());
    }
}

// --- MAIN ---
int main() {
    Abin<tElto> A;

    // Nivel 1
    A.insertarRaiz('A');  // raíz

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

    cout << "Nodos nostálgicos:\n";
    int total = Nostalgico(A);
    cout << "\nTotal de nodos nostálgicos: " << total << endl;

    return 0;
}