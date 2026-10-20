/*
La información de los pacientes pediátricos de una clínica de medicina general,
se encuentran en un archivo de texto. La información de cada paciente es la
siguiente: nombre; fecha de nacimiento; lista de vacunas recibidas; lista de
vacunas próximas. a realizarse.

8. Mostrar en orden alfabético los nombres de todos los pacientes
13. Mostrar el número de determinada vacuna próxima a aplicarse (siguiente mes)
*/

#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <mutex>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

class ordenador {
private:
  std::vector<std::string> arr;

public:
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

  void add_palabra(std::string a) { arr.push_back(a); }

  std::vector<std::string> get_arreglo() { return arr; }
};

class vacuna {
private:
  std::string nom_v;
  int dia, mes, año;

public:
  vacuna(std::string n, int d, int m, int a) {
    this->nom_v = n;
    this->dia = d;
    this->mes = m;
    this->año = a;
  }
  std::string get_nom() { return nom_v; }
  int get_dia() { return dia; }
  int get_mes() { return mes; }
  int get_año() { return año; }
};

class paciente {
private:
  std::string nombre, fecha_nac;
  std::vector<vacuna> vacunas_apl, vacunas_pend;

public:
  void set_nombre(std::string n) { this->nombre = n; }
  void set_fecha_n(std::string fn) { this->fecha_nac = fn; }
  void registrar_vacuna_apl(std::string n, int d, int m, int a) {
    vacuna v(n, d, m, a);
    this->vacunas_apl.push_back(v);
  }
  void registrar_vacuna_pend(std::string n, int d, int m, int a) {
    vacuna v(n, d, m, a);
    this->vacunas_pend.push_back(v);
  }
  std::string get_nombre() { return nombre; }
  std::string get_fecha_nac() { return fecha_nac; }
  std::vector<vacuna> get_vacunas_pen() { return vacunas_pend; }
};

class hospital {
private:
  std::vector<paciente> pacientes;
  std::ifstream datos_pacientes;
  std::string ruta;
  std::mutex mtx;
  time_t fecha_sistema;
  tm *fecha;
  int dia_a, mes_a, año_a, contador_vac;

public:
  hospital() {
    this->ruta = "Complex-Exercises/Hospital/Files/patient_data.txt";
    this->fecha_sistema = time(nullptr);
    this->fecha = localtime(&fecha_sistema);
    this->dia_a = fecha->tm_mday;
    this->mes_a = fecha->tm_mon + 1;
    this->año_a = fecha->tm_year + 1900;
    this->contador_vac = 0;
  }

  void cargar_datos_pacientes() {
    datos_pacientes.open(ruta);
    if (!datos_pacientes.is_open()) {
      throw std::runtime_error("Error al abrir archivo");
    }
    std::string linea, bloque, dato, temp, dia, mes, año;
    std::stringstream ss_linea, ss_bloque, ss_fecha;
    while (std::getline(datos_pacientes, linea)) {
      paciente p;
      ss_linea.clear();
      ss_linea.str(linea);
      std::getline(ss_linea, bloque, ';'); // bloque del nombre completo

      ss_bloque.clear();
      ss_bloque.str(bloque); // Leer Bloque Nombre

      temp = "";
      while (std::getline(ss_bloque, dato, ',')) { // Nombre Completo
        temp += dato;
      }
      p.set_nombre(temp);

      std::getline(ss_linea, bloque, ';'); // Bloque fecha nacimiento
      p.set_fecha_n(bloque);

      std::getline(ss_linea, bloque, ';'); // Bloque vacunas aplicadas
      if (!bloque.empty() && bloque != " ") {
        ss_bloque.clear();
        ss_bloque.str(bloque);

        while (std::getline(ss_bloque, dato, ',')) {
          temp = dato;                        // Nombre vacuna
          std::getline(ss_bloque, dato, ','); // Fecha de aplicación
          ss_fecha.clear();
          ss_fecha.str(dato);
          std::getline(ss_fecha, dia, '/');
          std::getline(ss_fecha, mes, '/');
          std::getline(ss_fecha, año, '/');

          p.registrar_vacuna_apl(temp, stoi(dia), stoi(mes), stoi(año));
        }
      }

      std::getline(ss_linea, bloque, '.'); // Bloque vacunas pendientes
      if (!bloque.empty() && bloque != " ") {
        ss_bloque.clear();
        ss_bloque.str(bloque);
        while (std::getline(ss_bloque, dato, ',')) {
          temp = dato;                        // Nombre vacuna
          std::getline(ss_bloque, dato, ','); // Fecha de aplicación
          ss_fecha.clear();
          ss_fecha.str(dato);
          std::getline(ss_fecha, dia, '/');
          std::getline(ss_fecha, mes, '/');
          std::getline(ss_fecha, año, '/');

          p.registrar_vacuna_pend(temp, stoi(dia), stoi(mes), stoi(año));
        }
      }
      pacientes.push_back(p);
    }
    datos_pacientes.close();
  }

  void mostrar_orden_alfabético() {
    std::vector<std::string> arr_ordenado;
    ordenador ord;
    int tam;

    for (paciente &p : pacientes) {
      ord.add_palabra(p.get_nombre());
    }

    tam = pacientes.size() / 4;
    // COBEGIN
    std::thread t1(&ordenador::ordenar_cadenas, &ord, 0, tam);
    std::thread t2(&ordenador::ordenar_cadenas, &ord, tam, tam * 2);
    std::thread t3(&ordenador::ordenar_cadenas, &ord, tam * 2, tam * 3);
    std::thread t4(&ordenador::ordenar_cadenas, &ord, tam * 3,
                   pacientes.size());
    // COEND

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    ord.ordenar_cadenas(0, pacientes.size());
    arr_ordenado = ord.get_arreglo();

    std::cout << "Orden Alfabético de los Pacientes" << std::endl;
    for (int i = 0; i < arr_ordenado.size(); i++) {
      std::cout << arr_ordenado[i] << std::endl;
    }
  }

  std::string a_min(std::string texto) {
    std::string temp = "";
    for(int i = 0; i < texto.size(); i++){
        temp += tolower(texto[i]);
    }
    return temp;
  }

  std::string trim(std::string texto) { 
    std::string temp = "";
    for(int i = 0; i < texto.size(); i++){
      if (texto[i] != ' ') {
        temp += texto[i];
      }
    }
    return temp;
  }

  void vacunas_apl_mes(std::string n, int m1, int m2) {
    std::vector<vacuna> vacs;
    std::string nom, nom_bus = a_min(n);
    int dia, mes, año, contador = 0;
    for (int i = m1; i < m2; i++) {
      vacs = pacientes[i].get_vacunas_pen();
      for (vacuna &v : vacs) {

        nom = a_min(trim(v.get_nom()));
        dia = v.get_dia();
        mes = v.get_mes();
        año = v.get_año();

        if ((mes_a < mes && año_a == año && mes < mes_a + 2 ||
             (mes_a == 12 && mes == 1 && año == año_a + 1)) &&
            nom == nom_bus) {
          contador++;
        }
      }
    }
    {
      std::lock_guard<std::mutex> lock(mtx);
      this->contador_vac += contador;
    }
  }

  void mostrar_vacunas_apl_mes() {
    int tam;
    std::string nom_v;
    std::cout << "Ingrese el nombre de la vacuna a buscar:" << std::endl;
    std::cin >> nom_v;

    tam = pacientes.size() / 4;
    // COBEGIN
    std::thread t1(&hospital::vacunas_apl_mes, this, nom_v, 0, tam);
    std::thread t2(&hospital::vacunas_apl_mes, this, nom_v, tam, tam * 2);
    std::thread t3(&hospital::vacunas_apl_mes, this, nom_v, tam * 2, tam * 3);
    std::thread t4(&hospital::vacunas_apl_mes, this, nom_v, tam * 3,
                   pacientes.size());
    // COEND

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << nom_v << ": " << contador_vac << std::endl;
  }
};

int main() {

  try {
    hospital miPequeñoHospital;
    miPequeñoHospital.cargar_datos_pacientes();
    miPequeñoHospital.mostrar_orden_alfabético();
    miPequeñoHospital.mostrar_vacunas_apl_mes();

  } catch (std::runtime_error error) {
    std::cout << error.what() << std::endl;
  }

  return 0;
}