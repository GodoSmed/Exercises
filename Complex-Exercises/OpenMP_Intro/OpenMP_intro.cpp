/*

1. Contar el número de espacios en blanco que tiene una cadena.
2. Contar el número de palabras (caracteres consecutivos sin espacio) y el
número de caracteres que tiene un archivo de texto.
3. Sumar dos matrices cuadradas de números enteros.
4. Revisar si dos cadenas son iguales.
5. Ordenar un conjunto de números enteros.
6. Revisar si una palabra se encuentra en un texto.
7. Obtener la intersección de dos conjuntos de enteros.
8. Calcular las raíces reales de una ecuación cuadrática.
9. Revisar cuantas veces aparece una palabra en un texto.
10. Calcular la sumatoria de n números enteros.


Compilar: g++ -fopenmp
*/

#include <iostream>
#include <omp.h>
#include <ostream>
#include <string>

// 1. Contar el número de espacios en blanco que tiene una cadena.
void ejercicio_01(){

}

// 2. Contar el número de palabras (caracteres consecutivos sin espacio) y el
// número de caracteres que tiene un archivo de texto.
void ejercicio_02(){

}

// 3. Sumar dos matrices cuadradas de números enteros.
void ejercicio_03(){

}

// 4. Revisar si dos cadenas son iguales.
void ejercicio_04(){

}

// 5. Ordenar un conjunto de números enteros.
void ejercicio_05(){

}

// 6. Revisar si una palabra se encuentra en un texto.
void ejercicio_06(){

}

// 7. Obtener la intersección de dos conjuntos de enteros.
void ejercicio_07(){

}

// 8. Calcular las raíces reales de una ecuación cuadrática.
void ejercicio_08(){

}

// 9. Revisar cuantas veces aparece una palabra en un texto.
void ejercicio_09(){

}

// 10. Calcular la sumatoria de n números enteros.
void ejercicio_10(){

}

int main() {
  std::string op;

  while (1) {
    std::cout << "Seleccione una opción" << std::endl;
    std::cout
        << "1. Contar el número de espacios en blanco que tiene una cadena."
        << std::endl;

    std::cout
        << "2. Contar el número de palabras (caracteres consecutivos sin "
           "espacio) y el número de caracteres que tiene un archivo de texto."
        << std::endl;

    std::cout << "3. Sumar dos matrices cuadradas de números enteros."
              << std::endl;

    std::cout << "4. Revisar si dos cadenas son iguales." << std::endl;

    std::cout << "5. Ordenar un conjunto de números enteros." << std::endl;

    std::cout << "6. Revisar si una palabra se encuentra en un texto."
              << std::endl;

    std::cout << "7. Obtener la intersección de dos conjuntos de enteros."
              << std::endl;

    std::cout << "8. Calcular las raíces reales de una ecuación cuadrática."
              << std::endl;

    std::cout << "9. Revisar cuantas veces aparece una palabra en un texto."
              << std::endl;

    std::cout << "10. Calcular la sumatoria de n números enteros." << std::endl;

    std::cout << "11. Salir\n" << std::endl;

    std::cout << "Selección: ";

    std::cin >> op;

    if (op == "1") {
      ejercicio_01();
    } else if (op == "2") {
      ejercicio_02();
    } else if (op == "3") {
      ejercicio_03();
    } else if (op == "4") {
      ejercicio_04();
    } else if (op == "5") {
      ejercicio_05();
    } else if (op == "6") {
      ejercicio_06();
    } else if (op == "7") {
      ejercicio_07();
    } else if (op == "8") {
      ejercicio_08();
    } else if (op == "9") {
      ejercicio_09();
    } else if (op == "10") {
      ejercicio_10();
    } else if (op == "11") {
      exit(0);
    }
  }
  return 0;
}