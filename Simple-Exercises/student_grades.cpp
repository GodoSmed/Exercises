/*
Mostrar el nombre de los alumnos que han aprobado el curso de matemáticas.
Para aprobar el curso cada examen parcial debe ser aprobado con una
calificación mayor o igual que 6. Cada estudiante ha realizado 3 exámenes
parciales que valen el 50% de su calificación, y 4 actividades que valen el 50%
de su calificación. De cada estudiante se sabe el nombre, la edad y las
calificaciones.
*/

#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <vector>
class alumno {
private:
  std::string nombre;
  int edad;
  bool aprobado;
  double cal_e1, cal_e2, cal_e3, num_act, cal_t;

public:
  alumno(std::string n, int e, double c_e1, double c_e2, double c_e3,
         double n_a) {
    this->nombre = n;
    this->edad = e;
    this->cal_e1 = c_e1;
    this->cal_e2 = c_e2;
    this->cal_e3 = c_e3;
    this->num_act = n_a;
    aprobado = false;
  }

  void set_nom(std::string nom) { this->nombre = nom; }
  void set_edad(int e) { this->edad = e; }

  void set_cal_p1(double cal) { this->cal_e1 = cal; }
  void set_cal_p2(double cal) { this->cal_e2 = cal; }
  void set_cal_p3(double cal) { this->cal_e3 = cal; }
  void set_num_act(double num) { this->num_act = num; }

  std::string get_nom() { return nombre; }
  int get_edad() { return edad; }

  double get_cal_p1() { return cal_e1; }
  double get_cal_p2() { return cal_e2; }
  double get_cal_p3() { return cal_e3; }
  double get_num_act() { return num_act; }

  bool get_aprobado() {
    this->cal_t = ((((cal_e1 + cal_e2 + cal_e3) / 3) * 0.5) + (1.25 * num_act));
    if (cal_e1 >= 6 && cal_e2 >= 6 && cal_e3 >= 6 && cal_t >= 6) {
      this->aprobado = true;
    }
    return aprobado;
  }

  double get_cal_t() { return cal_t; }
};

class matemáticas {
private:
  std::pmr::vector<alumno> alumnos, aprobados;

public:
  void add_alumno(alumno a) { alumnos.push_back(a); }

  void calificaciones(int m1, int m2) {
    for (int i = m1; i < m2; i++) {
      if (alumnos[i].get_aprobado()) {
        aprobados.push_back(alumnos[i]);
      }
    }
  }

  void imprimir_aprobados() {
    std::string nombre; 
    int edad;
    double cal_e1, cal_e2, cal_e3, num_act, cal_t;

    std::cout << "\t\t\tMatemáticas Calificaciones 2026" << std::endl;
    std::cout << "Nombre del alumno\tEdad"
                 "\tNum. Acts."
                 "\tExamen 1\tExamen 2\tExamen 3"
                 "\tCalif. Total"
              << std::endl;
    for (int i = 0; i < aprobados.size(); i++) {
      nombre = alumnos[i].get_nom();
      edad = alumnos[i].get_edad();
      num_act = alumnos[i].get_num_act();
      cal_e1 = alumnos[i].get_cal_p1();
      cal_e2 = alumnos[i].get_cal_p2();
      cal_e3 = alumnos[i].get_cal_p3();
      cal_t = alumnos[i].get_cal_t();
      std::cout << std::fixed << std::setprecision(2);
      std::cout << nombre << "\t" << edad << "\t" << num_act << "\t\t" << cal_e1
                << "\t\t" << cal_e2 << "\t\t" << cal_e3 << "\t\t" << cal_t
                << std::endl;
    }
  }

  int get_num_alumnos() { return alumnos.size(); }
};

int main() {
  matemáticas clase1;
  alumno alumno1("Alejandro Pérez Gómez", 16, 4, 5, 5, 2);
  alumno alumno2("Carmen Rodríguez López", 17, 9, 9, 10, 4);
  alumno alumno3("Carlos Martínez Sánchez", 16, 5, 8, 4, 1);
  alumno alumno4("Sofía Fernández Díaz", 17, 10, 10, 9, 4);
  alumno alumno5("Miguel Gómez Moreno", 16, 3, 4, 5, 0);
  alumno alumno6("Elena García Jiménez", 18, 9, 8, 9, 4);
  alumno alumno7("Javier Ruiz Romero", 17, 5, 6, 5, 2);
  alumno alumno8("Lucía Navarro Torres", 16, 10, 9, 10, 4);
  alumno alumno9("Daniel Domínguez Gil", 17, 4, 3, 2, 1);
  alumno alumno10("Carmen Moreno Vázquez", 16, 9, 10, 10, 4);
  alumno alumno11("Mateo Hernández Ruiz", 17, 8, 7, 8, 3);
  alumno alumno12("Valentina Ortiz Morales", 16, 10, 9, 9, 4);
  alumno alumno13("Diego Alonso Castro", 18, 4, 5, 6, 1);
  alumno alumno14("Valeria Jiménez Vargas", 17, 9, 10, 9, 4);
  alumno alumno15("Gabriel Silva Ramos", 16, 6, 7, 6, 2);
  alumno alumno16("Mariana Mendoza Vega", 17, 8, 9, 8, 3);
  alumno alumno17("Andrés Castillo Reyes", 16, 3, 3, 4, 0);
  alumno alumno18("Renata Flores Cruz", 18, 10, 10, 10, 4);
  alumno alumno19("Emilio Romero Navarro", 17, 5, 4, 5, 1);
  alumno alumno20("Camila Duarte Medina", 16, 9, 8, 9, 3);

  clase1.add_alumno(alumno1);
  clase1.add_alumno(alumno2);
  clase1.add_alumno(alumno3);
  clase1.add_alumno(alumno4);
  clase1.add_alumno(alumno5);
  clase1.add_alumno(alumno6);
  clase1.add_alumno(alumno7);
  clase1.add_alumno(alumno8);
  clase1.add_alumno(alumno9);
  clase1.add_alumno(alumno10);
  clase1.add_alumno(alumno11);
  clase1.add_alumno(alumno12);
  clase1.add_alumno(alumno13);
  clase1.add_alumno(alumno14);
  clase1.add_alumno(alumno15);
  clase1.add_alumno(alumno16);
  clase1.add_alumno(alumno17);
  clase1.add_alumno(alumno18);
  clase1.add_alumno(alumno19);
  clase1.add_alumno(alumno20);

  int tam = clase1.get_num_alumnos() / 4;
  std::thread t1(&matemáticas::calificaciones, &clase1, 0, tam);
  std::thread t2(&matemáticas::calificaciones, &clase1, tam, tam * 2);
  std::thread t3(&matemáticas::calificaciones, &clase1, tam * 2, tam * 3);
  std::thread t4(&matemáticas::calificaciones, &clase1, tam * 3,
                 clase1.get_num_alumnos());

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  clase1.imprimir_aprobados();

  return 0;
}