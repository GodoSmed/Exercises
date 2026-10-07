/*
La sala tiene 8 x 10 asientos. En el momento de asignación del asiento se debe
registrar nombre y la edad. El usuario debe poder elegir el asiento siempre y
cuando este desocupado. El sistema, ademas de asignar asiento, deberá permitir
liberar el asiento, buscar a un usuario en la sala (por nombre) y
mostrar información de la sala.
*/
#include <array>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <limits>
#include <mutex>
#include <ostream>
#include <string>
#include <thread>

class asiento {
public:
  std::string nombre;
  std::string edad;
  bool ocupado{false};

  void set_nombre(std::string n) { this->nombre = n; }
  void set_edad(std::string e) { this->edad = e; }
  void set_ocupado(bool o) { this->ocupado = o; }

  std::string get_nombre() { return nombre; }
  std::string get_edad() { return edad; }
  bool get_ocupado() { return ocupado; }
};

class cine {
public:
  std::array<std::array<asiento, 10>, 8> asientos; // Matriz 8x10
  std::mutex mtx;
  std::condition_variable cv; // Variable de condición
  bool impreso, encontrado;
  int hilos_c;

public:
  void asignar_asiento(int fila, int columna, std::string nombre,
                       std::string edad) {
    if (asientos[fila][columna].get_ocupado() == true) {
      std::cout << "\nAsiento ocupado!\n" << std::endl;
      return;
    }

    asientos[fila][columna].set_nombre(nombre);
    asientos[fila][columna].set_edad(edad);
    asientos[fila][columna].set_ocupado(true);
    std::cout << "\nAsiento asignado con éxito!\n" << std::endl;
  }

  void liberar_asiento(int fila, int columna) {
    if (asientos[fila][columna].get_ocupado() == false) {
      std::cout << "\nEl asiento ya estaba libre!\n" << std::endl;
      return;
    }

    asientos[fila][columna].set_nombre("");
    asientos[fila][columna].set_edad("");
    asientos[fila][columna].set_ocupado(false);
    std::cout << "\nAsiento liberado con éxito!\n" << std::endl;
  }

  void buscar_usuario(int m1, int m2, std::string nombre) {
    for (int i = m1; i <= m2; i++) {
      for (int j = 0; j < 10; j++) {
        {
          std::unique_lock<std::mutex> lock(mtx);
          if (encontrado)
            return;
        }

        if (nombre == asientos[i][j].get_nombre()) {
          std::unique_lock<std::mutex> lock(mtx);

          std::cout << "Asiento encontrado" << std::endl;
          std::cout << "Ocupado por: " << asientos[i][j].get_nombre()
                    << std::endl;
          std::cout << asientos[i][j].get_edad() << " años" << std::endl;
          std::cout << "Fila: " << i + 1 << std::endl;
          std::cout << "Columna: " << j + 1 << "\n" << std::endl;

          this->encontrado = true;
          cv.notify_one();
          return;
        }
      }
    }
    {
      std::unique_lock<std::mutex> lock(mtx);
      this->hilos_c++;
      cv.notify_one();
    }
  }

  void mostrar_sala() {

    std::cout << std::endl;
    std::cout << "\t <======== SALA DE CINE ========>" << std::endl;

    {
      std::unique_lock<std::mutex> lock(mtx);
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
          asientos[i][j].get_ocupado() ? std::cout << " [1] "
                                       : std::cout << " [0] ";
        }
        std::cout << std::endl;
      }
      this->impreso = true;
    }

    cv.notify_one();
  }

  void num_asientos_libres_ocupados() {
    int libres = 0, ocupados = 0;

    {
      std::unique_lock<std::mutex> lock(mtx);
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
          asientos[i][j].get_ocupado() ? ocupados++ : libres++;
        }
      }
    }

    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]() { return impreso; });
    std::cout << std::endl;
    std::cout << "Asientos Libres: " << libres << std::endl;
    std::cout << "Asientos Ocupados: " << ocupados << "\n" << std::endl;
  }

  void set_encontrado(bool e) { this->encontrado = e; }

  void set_impreso(bool i) { this->impreso = i; }

  void set_hilos_c(int h) { this->hilos_c = h; }

  bool get_encontrado() { return encontrado; }

  bool get_impreso() { return impreso; }

  int get_hilos_c() { return hilos_c; }
};

int main() {
  char op;
  std::string nom, edad;
  cine c;
  int m, n;

  while (1) {
    std::cout << "Seleccione una opción" << std::endl;
    std::cout << "1. Asignar Asiento" << std::endl;
    std::cout << "2. Liberar Asiento" << std::endl;
    std::cout << "3. Buscar Usuario" << std::endl;
    std::cout << "4. Mostrar Información de la sala" << std::endl;
    std::cout << "5. Salir\n" << std::endl;

    std::cout << "Selección: ";

    std::cin >> op;

    switch (op) {
    case '1':
      std::cout << "Fila: ";
      std::cin >> m;
      std::cout << "Columna: ";
      std::cin >> n;
      if (m > 8 || n > 10 || m < 1 || n < 1) {
        std::cout << "No existe ese asiento\n" << std::endl;
        break;
      }

      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      std::cout << "Nombre: ";
      std::getline(std::cin, nom);
      std::cout << "Edad: ";
      std::cin >> edad;
      c.asignar_asiento(m - 1, n - 1, nom, edad);
      break;

    case '2':
      std::cout << "Fila: ";
      std::cin >> m;
      std::cout << "Columna: ";
      std::cin >> n;
      if (m > 8 || n > 10 || m < 1 || n < 1) {
        std::cout << "No existe ese asiento\n" << std::endl;
        break;
      }
      c.liberar_asiento(m - 1, n - 1);
      break;

    case '3': {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      c.set_encontrado( false);
      c.set_hilos_c(0);

      std::cout << "Nombre: ";
      std::getline(std::cin, nom);
      std::cout << std::endl;

      // CO-BEGIN
      std::thread t1(&cine::buscar_usuario, &c, 0, 1, nom);
      std::thread t2(&cine::buscar_usuario, &c, 2, 3, nom);
      std::thread t3(&cine::buscar_usuario, &c, 4, 5, nom);
      std::thread t4(&cine::buscar_usuario, &c, 6, 7, nom);
      // CO-END

      {
        std::unique_lock<std::mutex> lock(c.mtx);
        c.cv.wait(lock, [&c]() { return c.get_encontrado() || c.get_hilos_c() == 4; });
      }

      if (!c.get_encontrado()) {
        std::cout << "Asiento no encontrado!\n" << std::endl;
      }

      t1.join();
      t2.join();
      t3.join();
      t4.join();

      break;
    }
    case '4': {
      c.set_impreso(false);

      // CO-BEGIN
      std::thread t1(&cine::mostrar_sala, &c);
      std::thread t2(&cine::num_asientos_libres_ocupados, &c);
      // CO-END

      t1.join();
      t2.join();

      break;
    }
    case '5':
      return 0;

    default:
      std::cout << "Opción no listada\n" << std::endl;
      break;
    }
  }
  return 0;
}