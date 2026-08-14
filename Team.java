package Exercises;

import java.util.Scanner;
     
public class Team
{
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		int total = 0;
		for (int i=0; i < n; i++){
			int P = scanner.nextInt();
			int V = scanner.nextInt();
			int T = scanner.nextInt();
			if ((P+V+T)>1) total++;
		}
		System.out.println(total);
		scanner.close();
	}
}
