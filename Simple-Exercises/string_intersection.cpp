/*
Determinar el conjunto intersección entre dos conjuntos de cadenas.
*/

#include <iostream>
#include <mutex>
#include <ostream>
#include <string>
#include <thread>
#include <vector>

class intersección {
private:
  std::vector<std::string> inters, c_cad1, c_cad2;

public:
  void addCad_c1(std::string cad) { c_cad1.push_back(cad); }
  void addCad_c2(std::string cad) { c_cad2.push_back(cad); }

  void operar(int inicio, int fin) {
    for (int i = inicio; i < fin; i++) {
      std::string pal = c_cad1[i];
      bool cad2 = find_cad2(pal), inter = find_inters(pal);

      if (cad2 && !inter) {
        inters.push_back(pal);
      }
    }
  }

  bool find_cad2(std::string cad) {
    for (int i = 0; i < c_cad2.size(); i++) {
      if (cad == c_cad2[i]) {
        return true;
      }
    }
      return false;
  }

  bool find_inters(std::string cad) {
    if (inters.empty()) {
      return false;
    }
    for (int i = 0; i < inters.size(); i++) {
      if (inters[i] == cad) {
        return true;
      }
    }
      return false;
  }

  void imprimir_cadena() {
    for (int i = 0; i < inters.size(); i++) {
      std::cout << inters[i] << " ";
    }
    std::cout << std::endl;
  }

  int get_size() { return c_cad1.size(); }
};

int main() {
  intersección in;
  in.addCad_c1("Hola");
  in.addCad_c1("Buenos");
  in.addCad_c1("Adios");
  in.addCad_c1("Hasta");
  in.addCad_c1("Luego");
  in.addCad_c1("Ayer");
  in.addCad_c2("Adios");
  in.addCad_c2("Hasta");
  in.addCad_c2("Buenos");
  in.addCad_c2("Hola");
  in.addCad_c2("Tares");
  in.addCad_c2("Amanecer");

  int rango = in.get_size() / 2;

  std::thread t1(&intersección::operar, &in, 0, rango);
  std::thread t2(&intersección::operar, &in, rango, in.get_size());

  t1.join();
  t2.join();

  in.imprimir_cadena();

  return 0;
}