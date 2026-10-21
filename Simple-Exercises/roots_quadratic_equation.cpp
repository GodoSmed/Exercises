/*
Determinar las raíces reales de una ecuación cuadrática mediante la fórmula
general. (Hilos ya implementados)
Agregar hilos para comprobar los posibles errores 
*/

#include <cmath>
#include <iostream>
#include <ostream>
#include <thread>

class formula_general {
private:
  double a, b, c, disc;

public:
  void set_valores() {
    std::cout << "Coeficiente del termino cuadrático: ";
    std::cin >> a;
    std::cout << "Coeficiente del termino lineal: ";
    std::cin >> b;
    std::cout << "Coeficiente del termino independiente: ";
    std::cin >> c;

    if (std::cin.fail()) {
      std::cout << "¡Error! Uno de los tres valores no es válido." << std::endl;
    }
  }

  int comprobar_errores() {
    disc = (b * b) - (4 * a * c);

    if (a == 0) {
      std::cout << "División entre 0" << std::endl;
      return -1;
    } else if (disc < 0) {
      std::cout << "Raíz Compleja" << std::endl;
      return -1;
    }

    return 1;
  }

  void calcular_raíces() {
    std::thread t1(&formula_general::raíz_1, this, a, b, c, disc);
    std::thread t2(&formula_general::raíz_2, this, a, b, c, disc);

    t1.join();
    t2.join();
  }

private:
  void raíz_1(double a, double b, double c, double disc) {
    std::cout << "Primer Raíz: " << (-(b) + std::sqrt(disc)) / (2 * a)
              << std::endl;
  }

  void raíz_2(double a, double b, double c, double disc) {
    std::cout << "Segunda Raíz: " << (-(b) - std::sqrt(disc)) / (2 * a)
              << std::endl;
  }
};

int main() {

  formula_general calculadora;

  calculadora.set_valores();

  if (calculadora.comprobar_errores() != -1) {
    calculadora.calcular_raíces();
  }

  return 0;
}