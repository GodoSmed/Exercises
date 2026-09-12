/*
71A
*/

class WayToLongWords{
	int main(){

		return 0;
	}
}

public class WayToLongWords {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int num = scanner.nextInt();
        scanner.nextLine();
        for (int i = 0; i < num; i++) {
            String word = scanner.nextLine();
            if (word.length() <= 10) {
                System.out.println(word);
            } else
                System.out.println(ToLong(word));
        }
        scanner.close();
    }

    static String ToLong(String word) {
        char[] num = String.valueOf(word.length() - 2).toCharArray();
        char[] cWord = word.toCharArray();
        char[] shtWord = new char[2 + num.length];

        shtWord[0] = cWord[0];
        shtWord[shtWord.length - 1] = cWord[cWord.length - 1];
        for (int i = 1; i < num.length + 1; i++)
            shtWord[i] = num[i - 1];

        word = new String(shtWord);
        return word;
    }
}