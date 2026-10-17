/*
Determinar el conjunto intersección entre dos conjuntos de cadenas.
*/

#include <iostream>
#include <ostream>
#include <string>
#include <thread>

class intersección {
private:
  std::string inters;

public:
  void operar(std::string cad1, std::string cad2, int inicio, int fin) {
    for (int i = inicio; i < fin; i++) {
      char c = cad1[i];
      if (cad2.find(c) != std::string::npos &&
          inters.find(c) == std::string::npos) {
        inters += c;
        inters += ", ";
      }
    }
  }

  std::string get_inter() { return inters; }
};

int main() {
  intersección in;
  std::string cad1, cad2;
  int mitad_cad1;

  std::cout << "Cadena 1: ";
  std::getline(std::cin, cad1);
  std::cout << "Cadena 2: ";
  std::getline(std::cin, cad2);

  for (char &c : cad1) {
    if (c >= 'A' && c <= 'Z') {
      c += 32;
    }
  }

  for (char &c : cad2) {
    if (c >= 'A' && c <= 'Z') {
      c += 32;
    }
  }

  mitad_cad1 = cad1.size() / 2;

  std::thread t1(&intersección::operar, &in, cad1, cad2, 0, mitad_cad1);
  std::thread t2(&intersección::operar, &in, cad1, cad2, mitad_cad1,
                 cad1.size());

  t1.join();
  t2.join();

  std::cout << in.get_inter() << std::endl;

  return 0;
}