/*
4A
*/
import java.util.Scanner;

public class Watermelon {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Even(scanner.nextInt());
        scanner.close();
    }

    static void Even(int i) {
        if (i == 2 || (i % 2 != 0 && (i - 2) % 2 != 0)) {
            System.out.println("NO");
        } else {
            System.out.println("YES");
        }
    }
}
