import java.util.Scanner;

public class CinemaConditionVariable {
  private Scanner entrada;
  private Asiento[][] asientos;

  public CinemaConditionVariable(Scanner entrada) {
    this.asientos = new Asiento[8][10];
    this.entrada = entrada;
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

  }

  public void liberarAsiento() {

  }

  public void buscarUsuario() {

  }

  public void mostrarDatosSala() {
    exclusionMutua.varCon = false;
    Thread hiloMostrar = new Thread(new MostrarSala());
    Thread hiloOcupados = new Thread(new AsientosOcupados());

    hiloMostrar.start();
    hiloOcupados.start();
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
      System.out.println("Edad: " + edad + "Años");
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
      synchronized (exclusionMutua.Monitor) {
        // ToDo: Operaciones Mostrar sala

        exclusionMutua.varCon = true;
        exclusionMutua.Monitor.notifyAll();
      }
    }
  }

  class AsientosOcupados implements Runnable {
    @Override
    public void run() {
      synchronized (exclusionMutua.Monitor) {
        while (!exclusionMutua.varCon) {
          try {
            // ToDo operaciones
            
            exclusionMutua.Monitor.wait();
          } catch (Exception e) {
            // ToDo: handle exception
          } 
        }

        // ToDo: Mostrar datos sala
      }
    }
  }

  public static void main(String[] args) {
    Scanner entrada = new Scanner(System.in);
    CinemaConditionVariable cine = new CinemaConditionVariable(entrada);
    char op;

    while (true) {
      System.out.println("Seleccione una opción");
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
          System.exit(0);

        default:
          System.out.println("Opción no listada");
          break;
      }
    }
  }

}
