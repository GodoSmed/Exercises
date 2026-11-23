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

#include <climits>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits>
#include <omp.h>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
ifstream archivo;

// 1. Contar el número de espacios en blanco que tiene una cadena.
void ejercicio_01() {
  string cadena;
  int contador = 0;

  std::cout << "Escribe la cadena: ";

  cin.ignore();
  getline(cin, cadena);

#pragma omp parallel for reduction(+ : contador)
  for (int i = 0; i < cadena.length(); i++) {
    if (cadena[i] == ' ') {
      contador++;
    }
  }

  cout << contador << std::endl;
}

// 2. Contar el número de palabras (caracteres consecutivos sin espacio) y el
// número de caracteres que tiene un archivo de texto.
void ejercicio_02() {
  string ruta = "Complex-Exercises/OpenMP_Intro/Files/words-02.txt";
  vector<string> lineas;
  stringstream ss_linea;
  string linea;
  int contPal = 0;
  int contChar = 0;

  archivo.open(ruta);

  if (!archivo.is_open()) {
    return;
  }

  while (std::getline(archivo, linea)) {
    lineas.push_back(linea);
  }

  archivo.close();

#pragma omp parallel for reduction(+ : contChar) reduction(+ : contPal)
  for (string linea : lineas) {
    if (linea.empty()) {
      continue;
    }
    bool nuevaPalabra = true;

    for (char c : linea) {
      contChar++;

      if (c == ' ') {
        nuevaPalabra = true;
      } else if (nuevaPalabra) {
        contPal++;
        nuevaPalabra = false;
      }
    }
  }

  // Resultado esperado: 1047 caracteres y 146 palabras
  cout << "Letras: " << contChar << endl;
  cout << "Palabras: " << contPal << endl;
}

// 3. Sumar dos matrices cuadradas de números enteros.
void ejercicio_03() {
  int matriz1[4][4] = {
      {2, 4, 2, 5}, {3, 4, 8, 0}, {6, 2, 2, 3}, {9, 7, 21, 22}};
  int matriz2[4][4] = {
      {5, 8, 6, 4}, {10, 12, 10, 2}, {1, 18, 19, 20}, {1, 20, 2, 3}};
  int matrizR[4][4];

#pragma omp parallel for collapse(2)
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrizR[i][j] = matriz1[i][j] + matriz2[i][j];
    }
  }

  for (int i = 0; i < 4; i++) {
    cout << "{ ";
    for (int j = 0; j < 4; j++) {
      cout << matrizR[i][j] << " ";
    }
    cout << "}" << endl;
  }
}

// 4. Revisar si dos cadenas son iguales.
void ejercicio_04() {
  string cadena1, cadena2;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  std::cout << "Cadena 1: ";
  getline(cin, cadena1);

  std::cout << "Cadena 2: ";
  getline(cin, cadena2);

  if (cadena1.length() != cadena2.length()) {
    cout << "Tamaño diferente" << endl;
    return;
  }

  bool cadena_dif = false;

#pragma omp parallel for
  for (int i = 0; i < cadena1.length(); i++) {
    if (cadena_dif) {
      continue;
    }

    if (cadena1[i] != cadena2[i]) {
#pragma omp critical
      {
        cadena_dif = true;
      }
    }
  }

  if (!cadena_dif) {
    cout << "Cadenas iguales" << endl;
  } else {
    cout << "Cadenas diferentes" << endl;
  }
}

// * 5. Ordenar un conjunto de números enteros.
void ejercicio_05() {
  int conjunto[] = {19, 18, 17, 22, 55, 1,  3,  65,  2,   6,
                    7,  8,  9,  0,  10, 23, 25, 102, 100, 77};

  int mins[4];
  int min;
  int min_i;

  for (int i = 0; i < 19; i++) {
#pragma omp parallel num_threads(4) shared(mins) private(min, min_i)
    {
      min = INT_MAX;

#pragma omp parallel for schedule(static)
      for (int j = i + 1; j < 20; j++) {
        if (min > conjunto[j]) {
          min = conjunto[j];
          min_i = j;
        }
      }

      mins[omp_get_thread_num()] = min_i;
    }

    min = INT_MAX;

    for (int i : mins) {
      if (min > conjunto[i]) {
        min = conjunto[i];
        min_i = i;
      }
    }

    if (min_i != i) {
      conjunto[min_i] = conjunto[i];
      conjunto[i] = min;
    }
  }

  for (int i = 0; i < 20; i++) {
    cout << conjunto[i] << " ";
  }
  cout << endl;
}

// * 6. Revisar si una palabra se encuentra en un texto.
void ejercicio_06() {
  string texto =
      "Señor, guíame hoy con tu luz, dame paz en medio de las tormentas, cuida "
      "a quienes amo y fortalece mi corazón siempre.";
  string palabra;

  string l = texto.substr(0, texto.length() / 2);
  string r = texto.substr(texto.length() / 2);

  bool encontrada = false;

  cout << texto << endl;

  cout << "\nEscribe la palabra" << endl;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, palabra);

#pragma omp parallel sections
  {
#pragma omp section
    {
      if (l.find(palabra) != string::npos) {
#pragma omp critical
        {
          encontrada = true;
        }
      }
    }

#pragma omp section
    {
      if (r.find(palabra) != string::npos) {
#pragma omp critical
        {
          encontrada = true;
        }
      }
    }
  }

  if (encontrada) {
    cout << "Palabra encontrada\n" << endl;
  }
}

// * 7. Obtener la intersección de dos conjuntos de enteros.
void ejercicio_07() {
  vector<int> conjunto1 = {19, 18, 17, 22, 55, 1, 3, 65, 2, 6};
  unordered_set<int> conjunto2 = {2, 8, 9, 0, 22, 19, 22, 77};
  unordered_set<int> conjuntoT;

#pragma omp parallel for
  for (int i = 0; i < conjunto1.size(); i++) {
    int val = conjunto1[i];
    if (conjunto2.find(val) != conjunto2.end()) {
#pragma omp critical
      {
        conjuntoT.insert(conjunto1[i]);
      }
    }
  }

  for (int j : conjuntoT) {
    cout << j << " ";
  }
  cout << endl;
}

// 8. Calcular las raíces reales de una ecuación cuadrática.
void ejercicio_08() {
  double a, b, c, disc, raíz1, raíz2;
  bool div_0 = false, disc_neg = false;

  std::cout << "Coeficiente del termino cuadrático: ";
  std::cin >> a;
  std::cout << "Coeficiente del termino lineal: ";
  std::cin >> b;
  std::cout << "Coeficiente del termino independiente: ";
  std::cin >> c;

#pragma omp parallel sections
  {
#pragma omp section
    {
      disc = (b * b) - (4 * a * c);
      if (disc < 0) {
        disc_neg = true;
      }
    }
#pragma omp section
    {
      if (a == 0) {
        div_0 = true;
      }
    }
  }

  if (div_0) {
    cout << "Discriminate negativo" << endl;
    return;
  }

  if (disc_neg) {
    cout << "Discriminate negativo" << endl;
    return;
  }

#pragma omp parallel sections
  {
#pragma omp section
    {
      raíz1 = (-(b) + sqrt(disc)) / (2 * a);
    }
#pragma omp section
    {
      raíz2 = (-(b)-sqrt(disc)) / (2 * a);
    }
  }

  cout << "Primera raíz: " << raíz1 << endl;
  cout << "Segunda raíz: " << raíz2 << endl;
}

bool es_delimitador(char c) {
  return c == ' ' || c == ',' || c == '.' || c == ';' || c == '\t' || c == '\n';
}

// * 9. Revisar cuantas veces aparece una palabra en un texto.
void ejercicio_09() {
  string texto =
      "Mientras el sol del atardecer teñía de tonos naranjas y violetas las "
      "tranquilas aguas del antiguo puerto pesquero, el viejo marinero "
      "reparaba con mucha paciencia sus redes desgastadas sobre el muelle de "
      "madera húmeda, recordando aquellas inolvidables travesías por alta mar "
      "junto a su fiel tripulación, quienes siempre enfrentaban las feroces "
      "tormentas del crudo invierno con valentía, esperanza y un profundo "
      "respeto hacia la inmensidad del océano que durante tantas décadas les "
      "había brindado sustento, sabiduría y libertad absoluta siempre.";
  string palabra;
  int contador = 0;

  cout << texto << endl;

  cout << "\nEscribe la palabra" << endl;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, palabra);

  #pragma omp parallel for schedule(static) reduction(+ : contador)
  for (int i = 0; i < texto.size(); i++) {
    if (texto[i] == palabra[0]) {
      bool no_encontrado = false;
      int indice_fin = i + palabra.size();

      if (indice_fin > texto.size()) {
        continue;
      }

      // Limite derecho
      char r = texto[indice_fin];
      if (!es_delimitador(r)) {
        continue;
      }

      // Limite izquierdo
      if (i > 0) {
        char l = texto[i - 1];
        if (!es_delimitador(l)) {
          continue;
        }
      }

      for (int j = 1; j < palabra.size(); j++) {
        if (no_encontrado) {
          continue;
        }

        if (texto[i + j] != palabra[j]) {
          no_encontrado = true;
        }
      }

      if (!no_encontrado) {
        contador++;
      }
    }
  }
  cout << contador << endl;
}

// 10. Calcular la sumatoria de n números enteros.
void ejercicio_10() {
  int nums[20] = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                  11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  int sumatoria = 0;

#pragma omp parallel for schedule(static) reduction(+ : sumatoria)
  for (int i = 0; i < 20; i++) {
    sumatoria += nums[i];
  }

  cout << sumatoria << endl;
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
    std::cin.clear();
  }
  return 0;
}