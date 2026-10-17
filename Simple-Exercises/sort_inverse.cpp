/*
Dado un conjunto de números en un arreglo, invertir el arreglo, es decir, el
primer elemento deberá aparecer al final, y el último deberá aparecer como el
primer elemento, y así sucesivamente (Hilos aplicados)
*/

#include <iostream>
#include <ostream>
#include <thread>
#include <vector>

class inversor_arreglo {
private:
  std::pmr::vector<int> arr, arr_inv;

public:

  void inicializar_arr() {
    std::cout << "Arreglo original: " << std::endl;
    for (int i = 0; i < 100; i++) {
      arr.push_back(i);
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }

  void invertir_arr(int m1, int m2) {
    for (int i = m2; i >= m1; i--) {
      arr_inv.push_back(arr[i]);
      std::cout << arr_inv.back() << " ";
    }
  }

  int get_tam() { return arr.size(); }
};

int main() {

  inversor_arreglo inversor;
  inversor.inicializar_arr();

  std::cout << "Arreglo invertido: " << std::endl;

  std::thread t1(&inversor_arreglo::invertir_arr, &inversor, 0, 24);
  std::thread t2(&inversor_arreglo::invertir_arr, &inversor, 25, 49);
  std::thread t3(&inversor_arreglo::invertir_arr, &inversor, 50, 74);
  std::thread t4(&inversor_arreglo::invertir_arr, &inversor, 75, 99);

  t1.join();
  t2.join();
  t3.join();
  t4.join();
  std::cout << std::endl;

  return 0;
}