
#include <fstream>
#include <ostream>
#include <semaphore.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

std::string ruta_p = "Complex-Exercises/Producer_Consumer/Files/producer.txt";
std::string ruta_c = "Complex-Exercises/Producer_Consumer/Files/consumer.txt";
std::ofstream archivo_p(ruta_p);
std::ofstream archivo_c(ruta_c);
int almacén[8];
std::vector<int> producido, consumo;
int ap_r = 0, ap_e = 0;
sem_t vacios;
sem_t llenos;

void productor() {
  int ap = 0;
  while (1) {
    if (ap == 10000000)
      return;

    if (ap % 100 == 0)
      archivo_p << std::endl;

    producido.push_back(ap);
    archivo_p << producido[ap] << ", ";
    sem_wait(&vacios);
    almacén[ap_e] = producido[ap++];
    ap_e = ++ap_e % 8;
    sem_post(&llenos);
  }
}

void consumidor() {
  int ap = 0;
  while (1) {
    if (ap == 10000000)
      return;

    if (ap % 100 == 0)
      archivo_c << std::endl;

    sem_wait(&llenos);
    consumo.push_back(almacén[ap_r]); // Tomar
    archivo_c << consumo[ap++] << ", ";
    almacén[ap_r] = -1; // Consumir
    ap_r = ++ap_r % 8;
    sem_post(&vacios);
  }
}

int main() {
  if (!archivo_p.is_open() || !archivo_c.is_open()) {
    return 0;
  }

  sem_init(&vacios, 0, 8);
  sem_init(&llenos, 0, 0);

  for (int i = 0; i < 8; i++) {
    almacén[i] = -1;
  }

  std::thread t1(productor);
  std::thread t2(consumidor);

  t1.join();
  t2.join();

  archivo_c.close();
  archivo_p.close();
}