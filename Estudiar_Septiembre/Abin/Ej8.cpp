/*
El TAD árbol binario puede albergar expresiones matemáticas mediante un árbol de expresión. Dentro del árbol binario los nodos hojas contendrán los operandos, y el resto
de los nodos los operadores.
a) Define el tipo de los elementos del árbol para que los nodos puedan almacenar operadores y operandos.
b) Implementa una función que tome un árbol binario de expresión (aritmética) y devuelva el resultado de la misma. Por simplificar el problema se puede asumir que el
árbol representa una expresión correcta. Los operadores binarios posibles en la expresión aritmética serán suma, resta, multiplicación y división.
Ejemplo: El siguiente árbol binario representa la expresión infija 7 × (15  3,2) / 2.
Nota: En el programa de prueba podemos usar las funciones rellenarAbin() de abin_ES.h para introducir por teclado o desde un fichero el árbol de expresión a evaluar. Sin
embargo, en este caso, será necesario sobrecargar los operadores utilizados internamente
en dichas funciones, es decir >>, << y != para el tipo de los elementos del árbol.
*/

#include "abin.hpp"
#include <iostream>

struct T
{
    char operador;
    double operando;
    T(double ope):operador{'\0'}, operando{ope} {}
    T(char op):operador{op},  operando{0} {}
};

double Operacion(Abin<T>);
double OperacionRec(Abin<T>, Abin<T>::nodo);

int main()
{
    Abin<T> A;
    A.insertarRaiz(T{'*'});
    Abin<T>::nodo n = A.raiz();
    A.insertarHijoIzqdo(n, T{7.0});
    A.insertarHijoDrcho(n, T{'/'});
    n = A.hijoDrcho(n);
    A.insertarHijoDrcho(n, T{2.0});
    A.insertarHijoIzqdo(n, T{'-'});
    n = A.hijoIzqdo(n);
    A.insertarHijoIzqdo(n, T{15.0});
    A.insertarHijoDrcho(n, T{3.2});
    double resultado = Operacion(A);
    std::cout << "El resultado de la operacion es de: " << resultado << std::endl;
    return 0;
}

double Operacion(Abin<T> A)
{
    if(A.arbolVacio())
    {
        return 0;
    }
    else
    {
        return OperacionRec(A, A.raiz());
    }
}

double OperacionRec(Abin<T> A, Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    if(A.elemento(n).operador == '\0')
    {
        return A.elemento(n).operando;
    }
    else
    {
        switch(A.elemento(n).operador)
        {
            case '+':
                return OperacionRec(A, A.hijoIzqdo(n)) + OperacionRec(A, A.hijoDrcho(n));
                break;
            case '-':
                return OperacionRec(A, A.hijoIzqdo(n)) - OperacionRec(A, A.hijoDrcho(n));
                break;
            case '*':
                return OperacionRec(A, A.hijoIzqdo(n)) * OperacionRec(A, A.hijoDrcho(n));
                break;
            case '/':
                if(A.hijoDrcho(n) != Abin<T>::NODO_NULO && A.elemento(A.hijoDrcho(n)).operador == '/' && OperacionRec(A, A.hijoDrcho(n)) == 0)
                {
                    std::cout << "No se puede realizar la operacion" << std::endl;
                    return 0;
                }
                return OperacionRec(A, A.hijoIzqdo(n)) / OperacionRec(A, A.hijoDrcho(n));
                break;
            default:
                std::cerr << "Error: Operador desconocido '" << A.elemento(n).operador << "'" << std::endl;
                return 0;
        }
    }
}