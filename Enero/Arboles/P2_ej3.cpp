/*
El TAD árbol binario puede albergar expresiones matemáticas mediante un árbol de expresión. Dentro del árbol binario los nodos hojas contendrán
los operandos, y el resto de los nodos los operadores. 
a) Define el tipo de los elementos del árbol para que los nodos puedan almacenar operadores y operandos. 
b) Implementa una función que tome un árbol binario de expresión (aritmética) y devuelva  el resultado de  la misma.
Por simplificar el problema se puede asumir que el árbol representa una expresión correcta. Los operadores binarios posibles en la expresión
aritmética serán suma, resta, multiplicación y división. Ejemplo: El siguiente árbol binario representa la expresión infija 7 × (15 + 3,2) / 2. 
*/
#include "abin.hpp"
#include <iostream>

struct expresion
{
    char operador;
    double operando;
};

double expresionaritmetica(Abin<expresion>& A)
{
    if(!A.arbolVacio())
    {
        return expresionaritmeticaRec(A, A.raiz());
    }
    else
    {
        return 0;
    }
}

double expresionaritmeticaRec(Abin<expresion>& A, Abin<expresion>::nodo n)
{
    if(n == Abin<expresion>::NODO_NULO)
    {
        return 0;
    }
    if(A.elemento(n).operador == '\0')
    {
        return A.elemento(n).operando;
    }
    switch(A.elemento(n).operador)
    {
        case '+': return expresionaritmeticaRec(A, A.hijoIzqdo(n)) + expresionaritmeticaRec(A, A.hijoDrcho(n)); break;
        case '-': return expresionaritmeticaRec(A, A.hijoIzqdo(n)) - expresionaritmeticaRec(A, A.hijoDrcho(n)); break;
        case '*': return expresionaritmeticaRec(A, A.hijoIzqdo(n)) * expresionaritmeticaRec(A, A.hijoDrcho(n)); break;
        case '/': if(expresionaritmeticaRec(A, A.hijoDrcho(n)) == 0 && A.hijoDrcho(n) != Abin<expresion>::NODO_NULO && A.elemento(A.hijoDrcho(n)).operador == '\0')
        {
            std::cout << "No se puede dividir un numero por 0." << std::endl;
        }
        else
        {
            return expresionaritmeticaRec(A, A.hijoIzqdo(n)) / expresionaritmeticaRec(A, A.hijoDrcho(n));
        }
        break;
        default: std::cout << "Operador desconocido." << A.elemento(A.hijoDrcho(n)).operador << std::endl; break;
    }
}