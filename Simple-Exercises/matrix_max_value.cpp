/*
Determinar el valor máximo de una matriz de NXM. (Hilos ya implementados)
*/

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <thread>

class matriz_op {
private:
  int matriz[10][10];             // Solo lectura
  int max_arr[5], ap = 0, numero; // Recurso compartido

public:
  matriz_op() {
    srand(time(NULL)); 
  }

  void in_matriz(){
    for (int i = 0; i < 10; i++) {
      std::cout << "{";
      for (int j = 0; j < 10; j++) {
        numero = rand() % 1000;
        matriz[i][j] = numero;
        printf("%4d", numero);
      }
      std::cout << " }" << std::endl;
    }
    std::cout << std::endl;
  }

  void max_val_matriz(int m1, int m2) {
    int max = 0;

    for (int i = m1; i <= m2; i++) {
      for (int j = 0; j < 10; j++) {
        if (matriz[i][j] > max) {
          max = matriz[i][j];
        }
      }
    }
    std::cout << "Hilo Max: " << max << std::endl;
    max_arr[ap++] = max;
  }

  int get_max_matriz() {
    int max = 0;
    std::cout << "\nContenido max[] = { ";
    for (int i = 0; i < 5; i++) {
      if (max_arr[i] > max) {
        max = max_arr[i];
        std::cout << max_arr[i] << " ";
      }
    }
    std::cout << "}" << std::endl;

    return max;
  }
};

int main() {

  matriz_op matriz1;

  matriz1.in_matriz();

  std::thread t1(&matriz_op::max_val_matriz, &matriz1, 0, 1);
  std::thread t2(&matriz_op::max_val_matriz, &matriz1, 2, 3);
  std::thread t3(&matriz_op::max_val_matriz, &matriz1, 4, 5);
  std::thread t4(&matriz_op::max_val_matriz, &matriz1, 6, 7);
  std::thread t5(&matriz_op::max_val_matriz, &matriz1, 8, 9);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();

  std::cout << "Valor Máximo: " << matriz1.get_max_matriz() << std::endl;

  return 0;
}