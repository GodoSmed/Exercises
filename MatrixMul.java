public class MatrixMul {
    public static void main(String[] args) {
        int A[][] = { // [2][3]
                { 1, 2, 3 },
                { 4, 5, 6 }
        };
        int B[][] = { // [3][2]
                { 10, 11 },
                { 20, 21 },
                { 30, 31 }
        };

        if (A[0].length != B.length) {
            System.out.println("Imposible");
        } else {
            int[][] C = new int[A.length][B[0].length];

            for (int k = 0; k < C[0].length; k++) { //2
                for (int i = 0; i < A.length; i++) { //2
                    for (int j = 0; j < B.length; j++) { //3
                        C[k][i] = C[k][i] + A[i][j] * B[j][i];
                        System.err.println(C[k][i]);
                    }
                }
            }

            for (int i = 0; i < C.length; i++) {
                System.err.print("{");
                for (int j = 0; j < C[0].length; j++) {
                    System.out.print(" " + C[i][j] + " ");
                }
                System.out.print("}\n");
            }
        }
    }
}
// [0][0] = A[0][0] * B[0][0] +
//          A[0][1] * B[1][0] +
//          A[0][2] * B[2][0]
// [0][1] = A[0][0] * B[0][1] +
//          A[0][1] * B[1][1] +
//          A[0][2] * B[2][1]
// [1][0] = A[1][0] * B[0][0] +
//          A[1][1] * B[1][0] +
//          A[1][2] * B[2][0]
// [1][1] = A[1][0] * B[0][1] +
//          A[1][1] * B[1][1] +
//          A[1][2] * B[2][1]