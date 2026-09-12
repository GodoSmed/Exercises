/*
282A
*/

class BitPlus {
	int main() {
		
	return 0;
	}
};

int n = scanner.nextInt();
		int total = 0;
		for (int i = 0; i < n; i++) {
			switch (scanner.nextLine()) {
				case "X++", "++X":
					total += 1;
					break;
				case "X--", "--X":
					total -= 1;
					break;
			}
		}
		System.out.println(total);
		cou
		scanner.close();
		return 0;