/*
    Productor - Consumidor, sin mecanismos de comunicación o sincronización
    Solo se pueden usar ciclos vacíos o sleep para sincronizar
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int leer() { 
  
  return 0;
}

int escribir(){
  
  return 0;
}

int main() {
  int tam, cons;
  FILE *datos = fopen("./Files/Almacén.txt", "w");
  if (datos == NULL) {
    printf("Error al abrir el archivo");
    exit(0);
  }
  fclose(datos);

  printf("Escriba el tamaño del almacén: \n");
  scanf("%d", &tam);

  printf("Escriba el número de consumidores: \n");
  scanf("%d", &cons);

  for (int i = 0; i < cons; i++) {
    int pid = fork();

    if (pid < 0) {
      printf("Error al crear proceso\n");
      exit(0);
    }

    if (pid > 0) { // Productor
      //while (escribir() == 0)
        sleep(1);
    }

    if (pid == 0) { // Consumidores
      //while (leer() == 0)
        sleep(1);

      exit(0);
    }
  }

  return 0;
}
