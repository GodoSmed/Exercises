/*
  Productor - Consumidor, 1 a 1 sin mecanismos de comunicación o
  sincronización Solo se pueden usar ciclos vacíos o sleep para sincronizar y
  archivos para comunicación
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int productor(int tam) {

  // Retorna -1 si el stack esta lleno
  return 0;
}

int op() {

  // Operaciones entre productor y consumidor
  return 0;
}

int consumidor() {

  // Retorna -1 si el stack esta vacío
  return 0;
}

int main() {
  int tam, prod;
  FILE *com = fopen("Producer_Consumer/Files/com.txt", "w");

  if (com == NULL) {
    printf("Error al abrir los archivos\n");
    exit(0);
  }
  fclose(com);

  printf("Escriba el tamaño del almacén: \n");
  scanf("%d", &tam);

  printf("Escriba el número de productos: \n");
  scanf("%d", &prod);

  int pid = fork();
  if (pid < 0) {
    printf("Error al crear proceso\n");
    exit(0);
  }

  for (int i = 0; i < prod; i++) {
    if (pid > 0) {
      while (productor(tam) == -1)
        sleep(1);
    } else {
      while (consumidor() == -1)
        sleep(1);
    }
  }
  return 0;
}
