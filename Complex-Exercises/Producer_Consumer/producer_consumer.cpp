
#include <fstream>
#include <iostream>
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

void producir(int producto){
  producido.push_back(producto);
  archivo_p << producido[producto] << std::endl;
}

void coloca(int *producto){
  std::cout << "Produciendo" << std::endl;
  almacén[ap_e] = producido[(*producto)++];
  ap_e = ++ap_e % 8;
}

void productor() {
  int ap = 0;
  while (1) {
    producir(ap);
    sem_wait(&vacios);
    coloca(&ap);
    sem_post(&llenos);
    sleep(1);
  }
}

void tomar(int producto){
  consumo.push_back(producto); 
}

void consumir(int *ap) {
  std::cout << "Consumiendo" << std::endl;
  almacén[ap_r] = -1; 
  archivo_c << consumo[(*ap)++] << std::endl;
  ap_r = ++ap_r % 8;
}

void consumidor() {
  int ap = 0;
  while (1) {
    sem_wait(&llenos);
    tomar(almacén[ap_r]);
    consumir(&ap);
    sem_post(&vacios);
    sleep(1);
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