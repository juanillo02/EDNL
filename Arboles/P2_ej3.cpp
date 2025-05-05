/*
El TAD árbol binario puede albergar expresiones matemáticas mediante un árbol de expresión. Dentro del árbol binario los nodos hojas contendrán
los operandos, y el resto de los nodos los operadores. 
a) Define el tipo de los elementos del árbol para que los nodos puedan almacenar operadores y operandos. 
b) Implementa una función que tome un árbol binario de expresión (aritmética) y devuelva  el resultado de  la misma.
Por simplificar el problema se puede asumir que el árbol representa una expresión correcta. Los operadores binarios posibles en la expresión
aritmética serán suma, resta, multiplicación y división. Ejemplo: El siguiente árbol binario representa la expresión infija 7 × (15 + 3,2) / 2. 
*/
#include <iostream>
#include "abin.h"

struct aritmetica{
    double operandos;
    char operador;
    aritmetica(char c): operador{c}, operandos {0} {}
    aritmetica(double d): operador{'\0'}, operandos {d} {}
};

double operacionRec(Abin<aritmetica> A, Abin<aritmetica>::nodo n)
{
    if(n == Abin<aritmetica>::NODO_NULO)
    {
        return 0;
    }
    if(A.elemento(n).operador == '\0')
    {
        return A.elemento(n).operandos;
    }
    else
    {
        switch(A.elemento(n).operador)
        {
        case '+':   return operacionRec(A, A.hijoIzqdo(n)) + operacionRec(A, A.hijoDrcho(n));
        case '-':   return operacionRec(A, A.hijoIzqdo(n)) - operacionRec(A, A.hijoDrcho(n));
        case '*':   return operacionRec(A, A.hijoIzqdo(n)) * operacionRec(A, A.hijoDrcho(n));
        case '/':   if(A.hijoDrcho(n) == Abin<aritmetica>::NODO_NULO && A.elemento(A.hijoDrcho(n)).operandos == 0 && A.elemento(A.hijoDrcho(n)).operador == '\0')
                    {
                        throw std::runtime_error("Error: División por 0.");
                    }
                    else
                    {
                        return operacionRec(A, A.hijoIzqdo(n)) / operacionRec(A, A.hijoDrcho(n));
                    }
        default:    throw std::runtime_error("Error: Operador desconocido.");
        }
    }
}

double operacion(Abin<aritmetica> A)
{
    if(A.vacio())
    {
        return 0;
    }
    else
    {
        return operacionRec(A, A.raiz());
    }
}

int main () 
{
    try {
        Abin<aritmetica> A; 
        A.insertarRaiz(aritmetica('*'));
        A.insertarHijoIzqdo(A.raiz(), aritmetica(7.0));
        A.insertarHijoDrcho(A.raiz(), aritmetica('/'));
        A.insertarHijoIzqdo(A.hijoDrcho(A.raiz()), aritmetica('-'));
        A.insertarHijoDrcho(A.hijoDrcho(A.raiz()), aritmetica(2.0));
        A.insertarHijoIzqdo(A.hijoIzqdo(A.hijoDrcho(A.raiz())), aritmetica(15.0));
        A.insertarHijoDrcho(A.hijoIzqdo(A.hijoDrcho(A.raiz())), aritmetica(3.2));
        double resultado = operacion(A);
        std::cout << "El resultado es: " << resultado << std::endl;
    }catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
   return 0;
}