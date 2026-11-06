import java.util.Scanner;

public class CinemaConditionVariable {
  private Scanner entrada;
  private Asiento[][] asientos;

  public CinemaConditionVariable(Scanner entrada) {
    this.asientos = new Asiento[8][10];
    this.entrada = entrada;

    for (int i = 0; i < asientos.length; i++) {
      for (int j = 0; j < asientos[i].length; j++) {
        asientos[i][j] = new Asiento();
      }
    }
  }

  class Asiento {
    private boolean ocupado;
    private String nombre, edad;

    public Asiento() {
      this.ocupado = false;
    }

    void setNombre(String n) {
      this.nombre = n;
    }

    void setEdad(String e) {
      this.edad = e;
    }

    void setOcupado(boolean o) {
      this.ocupado = o;
    }

    String getNombre() {
      return nombre;
    }

    String getEdad() {
      return edad;
    }

    Boolean getOcupado() {
      return ocupado;
    }
  }

  public void asignarAsiento() {
    int fila, columna;
    String nombre, edad;

    try {
      System.out.println("Fila: ");
      fila = entrada.nextInt();
      System.out.println("Columna: ");
      columna = entrada.nextInt();
    } catch (Exception e) {
      System.err.println("Datos inválidos\n");
      return;
    }

    if (fila > 8 || columna > 10 || fila < 1 || columna < 1) {
      System.out.println("No existe ese asiento\n");
      return;
    } else if (asientos[--fila][--columna].getOcupado() == true) {
      System.out.println("\nAsiento ocupado!\n");
      return;
    }

    entrada.nextLine();
    System.out.println("Nombre: ");
    nombre = entrada.nextLine();

    System.out.println("Edad: ");
    edad = entrada.nextLine();

    try {
      Double.parseDouble(edad);
    } catch (NumberFormatException e) {
      System.err.println("La edad debe ser un número");
      return;
    }

    asientos[fila][columna].setNombre(nombre);
    asientos[fila][columna].setEdad(edad);
    asientos[fila][columna].setOcupado(true);
    System.out.println("\nAsiento asignado con éxito!");
  }

  public void liberarAsiento() {
    int fila, columna;

    try {
      System.out.println("Fila: ");
      fila = entrada.nextInt();
      System.out.println("Columna: ");
      columna = entrada.nextInt();
    } catch (Exception e) {
      System.err.println("Datos inválidos\n");
      return;
    }

    if (fila > 8 || columna > 10 || fila < 1 || columna < 1) {
      System.out.println("No existe ese asiento\n");
      return;
    } else if (asientos[--fila][--columna].getOcupado() == false) {
      System.out.println("\nEl Asiento ya estaba libre!\n");
      return;
    }

    asientos[fila][columna].setNombre("");
    asientos[fila][columna].setEdad("");
    asientos[fila][columna].setOcupado(false);
    System.out.println("\nAsiento liberado con éxito!\n");
  }

  public void buscarUsuario() {
    String nombre;
    entrada.nextLine();
    System.out.println("Nombre: ");
    nombre = entrada.nextLine();

    Thread hilo1 = new Thread(new BuscarUsuario(0, 1, nombre));
    Thread hilo2 = new Thread(new BuscarUsuario(2, 3, nombre));
    Thread hilo3 = new Thread(new BuscarUsuario(4, 5, nombre));
    Thread hilo4 = new Thread(new BuscarUsuario(6, 7, nombre));

    hilo1.start();
    hilo2.start();
    hilo3.start();
    hilo4.start();

    try {
      hilo1.join();
      hilo2.join();
      hilo3.join();
      hilo4.join();
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
      System.err.println(e.getMessage());
    }
  }

  public void mostrarDatosSala() {
    exclusionMutua.varCon = false;
    Thread hiloOcupados = new Thread(new AsientosOcupados());
    Thread hiloMostrar = new Thread(new MostrarSala());

    hiloMostrar.start();
    hiloOcupados.start();

    try {
      hiloMostrar.join();
      hiloOcupados.join();
    } catch (InterruptedException e) {
      Thread.currentThread().interrupt();
      System.err.println(e.getMessage());
    }
  }

  class BuscarUsuario implements Runnable {
    private int m1, m2;
    private String nombre;

    public BuscarUsuario(int m1, int m2, String nombre) {
      this.m1 = m1;
      this.m2 = m2;
      this.nombre = nombre;
    }

    @Override
    public void run() {
      for (int i = m1; i <= m2; i++) {
        for (int j = 0; j < 10; j++) {
          String nombreAsiento = asientos[i][j].getNombre();

          if (nombre.equals(nombreAsiento)) {
            String edadAsiento = asientos[i][j].getEdad();
            usuarioEncontrado(nombreAsiento, edadAsiento, i, j);
          }
        }
      }
    }

    public static synchronized void usuarioEncontrado(String nombre, String edad, int i, int j) {
      System.out.println("Asiento encontrado");
      System.out.println("Nombre: " + nombre);
      System.out.println("Edad: " + edad + " Años");
      System.out.println("Fila: " + (i + 1));
      System.out.println("Columna: " + (j + 1));
    }
  }

  public class exclusionMutua {
    public static final Object Monitor = new Object();
    public static boolean varCon = false;
  }

  class MostrarSala implements Runnable {
    @Override
    public void run() {
      System.out.println("\n\t <======== SALA DE CINE ========>");

      for (int i = 0; i < asientos.length; i++) {
        for (int j = 0; j < asientos[0].length; j++) {
          if (asientos[i][j].getOcupado()) {
            System.out.print(" [1] ");
          } else {
            System.out.print(" [0] ");
          }
        }
        System.out.println();
      }
      System.out.println();

      synchronized (exclusionMutua.Monitor) {
        exclusionMutua.varCon = true;
        exclusionMutua.Monitor.notifyAll();
      }
    }
  }

  class AsientosOcupados implements Runnable {
    private int libres = 0, ocupados = 0;

    @Override
    public void run() {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
          if (asientos[i][j].getOcupado()) {
            ocupados++;
          } else
            libres++;
        }
      }

      synchronized (exclusionMutua.Monitor) {
        while (!exclusionMutua.varCon) {
          try {
            exclusionMutua.Monitor.wait();
          } catch (Exception e) {
            System.err.println(e.getMessage());
          }
        }
      }

      System.out.println("Asientos Ocupados: " + ocupados);
      System.out.println("Asientos Libres: " + libres + "\n");
    }
  }

  public static void main(String[] args) {
    Scanner entrada = new Scanner(System.in);
    CinemaConditionVariable cine = new CinemaConditionVariable(entrada);
    char op;

    while (true) {
      System.out.println("\nSeleccione una opción");
      System.out.println("1. Asignar Asiento");
      System.out.println("2. Liberar Asiento");
      System.out.println("3. Buscar Usuario");
      System.out.println("4. Mostrar Información de la sala");
      System.out.println("5. Salir");
      System.out.print("Selección: ");

      op = entrada.next().charAt(0);

      switch (op) {
        case '1':
          cine.asignarAsiento();
          break;

        case '2':
          cine.liberarAsiento();
          break;

        case '3': {
          cine.buscarUsuario();
          break;
        }
        case '4': {
          cine.mostrarDatosSala();
          break;
        }
        case '5':
          entrada.close();
          System.exit(0);

        default:
          System.out.println("Opción no listada");
          break;
      }
    }
  }

}
