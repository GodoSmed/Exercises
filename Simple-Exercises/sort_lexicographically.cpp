/*
Ordenar léxico-gráficamente los elementos de un arreglo de cadenas de forma
ascendente. (Hilos Aplicados)
*/

#include <climits>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <vector>

class orden_lg {
private:
  std::vector<std::string> arr;

public:
  void add_palabra(std::string a) { arr.push_back(a); }

  void ordenar_cadenas(int m1, int m2) {
    std::string min;
    int min_i;
    for (int i = m1; i < m2 - 1; i++) {
      min = "~";
      for (int j = i + 1; j < m2; j++) {
        if (min > arr[j]) {
          min = arr[j];
          min_i = j;
        }
      }
      if (min_i != i) {
        arr[min_i] = arr[i];
        arr[i] = min;
      }
    }
  }

  void imprimir_arreglo() {
    std::cout << "Arreglo ordenado:" << std::endl;
    for (int i = 0; i < arr.size(); i++) {
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }

  int get_tam() { return arr.size(); }
};

int main() {

  orden_lg ordenador;
  ordenador.add_palabra("Suspiro");
  ordenador.add_palabra("Esfuerzo");
  ordenador.add_palabra("Crepúsculo");
  ordenador.add_palabra("Solitude");
  ordenador.add_palabra("Catarsis");
  ordenador.add_palabra("Sinfonía");
  ordenador.add_palabra("Murmullo");
  ordenador.add_palabra("Melancolía");
  ordenador.add_palabra("Nostalgia");
  ordenador.add_palabra("Destello");
  ordenador.add_palabra("Aurora");
  ordenador.add_palabra("Hechizo");
  ordenador.add_palabra("Crisálida");
  ordenador.add_palabra("Efímero");
  ordenador.add_palabra("Renacer");
  ordenador.add_palabra("Elocuencia");
  ordenador.add_palabra("Eclipse");
  ordenador.add_palabra("Serendipia");
  ordenador.add_palabra("Abismo");
  ordenador.add_palabra("Atardecer");
  ordenador.add_palabra("Clandestino");
  ordenador.add_palabra("Resiliencia");
  ordenador.add_palabra("Mosaico");
  ordenador.add_palabra("Ilusión");
  ordenador.add_palabra("Universo");
  ordenador.add_palabra("Destino");
  ordenador.add_palabra("Oasis");
  ordenador.add_palabra("Fulgor");
  ordenador.add_palabra("Brújula");
  ordenador.add_palabra("Fantasía");
  ordenador.add_palabra("Susurro");
  ordenador.add_palabra("Inercia");
  ordenador.add_palabra("Sombra");
  ordenador.add_palabra("Sempiterno");
  ordenador.add_palabra("Laberinto");
  ordenador.add_palabra("Vértigo");
  ordenador.add_palabra("Enigma");
  ordenador.add_palabra("Espejismo");
  ordenador.add_palabra("Bostezar");
  ordenador.add_palabra("Aura");
  ordenador.add_palabra("Zarpar");
  ordenador.add_palabra("Relámpago");
  ordenador.add_palabra("Aventura");
  ordenador.add_palabra("Utopía");
  ordenador.add_palabra("Nebulosa");
  ordenador.add_palabra("Resplandor");
  ordenador.add_palabra("Horizonte");
  ordenador.add_palabra("Nebula");
  ordenador.add_palabra("Misterio");
  ordenador.add_palabra("Espiral");

  if (ordenador.get_tam() > 4) {
    int tam = ordenador.get_tam() / 4;
    std::thread t1(&orden_lg::ordenar_cadenas, &ordenador, 0, tam);
    std::thread t2(&orden_lg::ordenar_cadenas, &ordenador, tam, tam * 2);
    std::thread t3(&orden_lg::ordenar_cadenas, &ordenador, tam * 2, tam * 3);
    std::thread t4(&orden_lg::ordenar_cadenas, &ordenador, tam * 3,
                   ordenador.get_tam());

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    ordenador.ordenar_cadenas(0, ordenador.get_tam());
    ordenador.imprimir_arreglo();
  } else if (ordenador.get_tam() > 1) {
    int tam = ordenador.get_tam() / 2;
    std::thread t1(&orden_lg::ordenar_cadenas, &ordenador, 0, tam);
    std::thread t2(&orden_lg::ordenar_cadenas, &ordenador, tam,
                   ordenador.get_tam());
  } else {
    std::cout << "No hay suficientes elementos" << std::endl;
  }

  return 0;
}