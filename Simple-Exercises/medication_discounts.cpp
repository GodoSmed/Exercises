/*
cSpell:disable
Suponga que se requiere conocer si una persona podrá obtener un descuento
en la compra de sus medicamentos. Una persona puede obtener un descuento
del 20% sobre su compra total en la compra de al menos $1000.00, o un
descuento del 30% en la compra de $1500, o un descuento del 10% en la
compra de al menos un anti-ácido de cualquier costo. Los descuentos no son
acumulables en la misma compra (Hilos aplicados)
*/

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

class farmacia {
public:
  std::pmr::vector<std::string> productos, carrito;
  double c_total, descuento;

  farmacia() {
    c_total = 0;
    descuento = 0;
  }

public:
  void add_producto(std::string a) { productos.push_back(a); }

  void mostrar_catalogo() {
    std::cout << "\nID Producto\t\t\tCategoría\t\tPrecio" << std::endl;
    for (int i = 0; i < productos.size(); i++) {
      std::cout << i + 1 << ". " << productos[i] << std::endl;
    }
    std::cout << std::endl;
  }

  void mostrar_carrito() {
    if (carrito.empty()) {
      std::cout << "\nCarrito Vacío!\n" << std::endl;
      return;
    }
    std::cout << "\nID Producto\t\t\tCategoría\t\tPrecio" << std::endl;
    for (int i = 0; i < carrito.size(); i++) {
      std::cout << i + 1 << ". " << carrito[i] << std::endl;
    }
    std::cout << std::endl;

    if (descuento == 0) {
      std::cout << "Total a pagar: " << c_total << std::endl;
    } else {
      std::cout << "Total con descuento aplicado: "
                << c_total - (c_total * descuento) << std::endl;
    }

    std::cout << std::endl;
  }

  void agregar_producto() {
    std::string sel;
    double precio;
    int id;
    std::cout << "\nEscriba la ID del producto a agregar: " << std::endl;
    std::cin >> sel;

    precio = obtenerPrecio(sel);
    if (precio == 0) {
      std::cout << "\nProducto no listado\n" << std::endl;
      return;
    }

    id = std::stoi(sel) - 1;
    this->c_total += precio;
    carrito.push_back(productos[id]);

    std::thread t1(&farmacia::descuento_10, this);
    std::thread t2(&farmacia::descuento_30, this);
    std::thread t3(&farmacia::descuento_ant, this);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "\nProducto agregado con exito\n" << std::endl;
  }

  void eliminar_producto() {
    std::string sel;
    int id;
    double precio;
    std::cout << "\nEscriba la ID del producto a eliminar: " << std::endl;
    std::cin >> sel;

    try {

      id = std::stoi(sel) - 1;

      for (int i = 0; i < productos.size(); i++) {
        if (carrito[id] == productos[i]) {
          this->c_total -= obtenerPrecio(std::to_string(i + 1));
          carrito.erase(carrito.begin() + id);
          std::cout << "\nProducto eliminado con exito\n" << std::endl;
          return;
        }
      }

      std::cout << "\nID inválida\n" << std::endl;
      return;

    } catch (...) {
      std::cout << "\nProducto no listado\n" << std::endl;
      return;
    }
  }

private:
  void descuento_10() { // 20% 1000
    if (carrito.empty()) {
      return;
    }
    if ((c_total >= 1000 && c_total < 1500) && (descuento < 0.2)) {
      std::cout << "\nDescuento del 20" << "% " << "aplicado\n" << std::endl;
      this->descuento = 0.2;
    }
  }

  void descuento_30() { // 30% 1500
    if (carrito.empty()) {
      return;
    }
    if (c_total >= 1500 && descuento < 0.3) {
      std::cout << "\nDescuento del 30" << "% " << "aplicado\n" << std::endl;
      this->descuento = 0.3;
    }
  }

  void descuento_ant() { // Antiácido buscar si esta en el carrito
    if (carrito.empty()) {
      return;
    }

    for (int i = 0; i < carrito.size(); i++) {
      if ((carrito[i] == productos[2]) && (descuento == 0)) {
        std::cout << "\nDescuento del 10" << "% " << "aplicado\n" << std::endl;
        this->descuento = 0.1;
        return;
      }
    }
  }

  double obtenerPrecio(const std::string &op) {
    if (op == "1")
      return 34.00; // Paracetamol 500mg
    if (op == "2")
      return 95.00; // Ibuprofeno 400mg
    if (op == "3")
      return 128.00; // Omeprazol 20mg
    if (op == "4")
      return 58.00; // Loratadina 10mg
    if (op == "5")
      return 149.00; // Amoxicilina 500mg
    if (op == "6")
      return 70.00; // Alcohol Etílico 70°
    if (op == "7")
      return 36.00; // Gasa Estéril
    if (op == "8")
      return 122.00; // Termómetro Digital
    if (op == "9")
      return 94.00; // Vitamina C 1000mg
    if (op == "10")
      return 79.00; // Jarabe para la Tos
    if (op == "11")
      return 128.00; // Crema Hipoalergénica
    if (op == "12")
      return 318.00; // Bloqueador Solar FPS 50
    if (op == "13")
      return 86.00; // Gotas Oftálmicas
    if (op == "14")
      return 36.00; // Suero Oral
    if (op == "15")
      return 41.00; // Curas Adhesivas
    if (op == "16")
      return 31.00; // Jabón Neutro
    if (op == "17")
      return 50.00; // Gel Antibacterial
    if (op == "18")
      return 115.00; // Oxímetro de Pulso
    if (op == "19")
      return 65.00; // Mascarillas
    if (op == "20")
      return 36.00; // Cepillo Dental Suave

    return 0; // Default
  }
};

int main() {
  char op;
  farmacia farmacia;

  farmacia.add_producto("Paracetamol 500mg\t\tAnalgésico\t\t$34");
  farmacia.add_producto("Ibuprofeno 400mg\t\tAntiinflamatorio\t$95");
  farmacia.add_producto("Omeprazol 20mg\t\tAntiácido\t\t$128");
  farmacia.add_producto("Loratadina 10mg\t\tAntihistamínico\t\t$58");
  farmacia.add_producto("Amoxicilina 500mg\t\tAntibiótico\t\t$149");
  farmacia.add_producto("Alcohol Etílico 70°\t\tAntiséptico\t\t$70");
  farmacia.add_producto("Gasa Estéril\t\t\tMaterial Quirúrgico\t$36");
  farmacia.add_producto("Termómetro Digital\t\tDispositivo Médico\t$122");
  farmacia.add_producto("Vitamina C 1000mg\t\tSuplemento\t\t$94");
  farmacia.add_producto("Jarabe para la Tos\t\tRespiratorio\t\t$79");
  farmacia.add_producto("Crema Hipoalergénica\tDermatología\t\t$128");
  farmacia.add_producto("Bloqueador Solar\t\tCuidado Personal\t$318");
  farmacia.add_producto("Gotas Oftálmicas\t\tOftalmología\t\t$86");
  farmacia.add_producto("Suero Oral\t\t\tHidratación\t\t$36");
  farmacia.add_producto("Curas Adhesivas\t\tPrimeros Auxilios\t$41");
  farmacia.add_producto("Jabón Neutro\t\tHigiene\t\t\t$31");
  farmacia.add_producto("Gel Antibacterial\t\tHigiene\t\t\t$50");
  farmacia.add_producto("Oxímetro de Pulso\t\tDispositivo Médico\t$115");
  farmacia.add_producto("Mascarillas\t\t\tProtección\t\t$65");
  farmacia.add_producto("Cepillo Dental Suave\tHigiene Oral\t\t$36");

  while (1) {
    std::cout << "Seleccione una opción" << std::endl;
    std::cout << "1. Mostrar Productos" << std::endl;
    std::cout << "2. Mostrar Carrito" << std::endl;
    std::cout << "3. Agregar Producto" << std::endl;
    std::cout << "4. Eliminar Producto" << std::endl;
    std::cout << "5. Salir\n" << std::endl;

    std::cout << "Selección: ";

    std::cin >> op;

    switch (op) {
    case '1':
      farmacia.mostrar_catalogo();
      break;

    case '2':
      farmacia.mostrar_carrito();

      break;

    case '3': {
      farmacia.agregar_producto();

      break;
    }
    case '4': {
      farmacia.eliminar_producto();

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