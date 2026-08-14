package Exercises;

import java.util.Scanner;
	
public class BitPlus 
{
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int n = scanner.nextInt();
		scanner.nextLine();
		int total = 0;
		for (int i=0; i < n; i++){ 
			switch(scanner.nextLine()){
				case "X++", "++X":
					total += 1;
					break;
				case "X--", "--X":
					total -= 1;
					break;
			}
		}
		System.out.println(total);
		scanner.close();
	}
}
