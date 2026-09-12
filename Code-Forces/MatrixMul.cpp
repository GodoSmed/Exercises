/* 
 [0][0] = A[0][0] * B[0][0] +  
          A[0][1] * B[1][0] +
          A[0][2] * B[2][0]
 [0][1] = A[0][0] * B[0][1] +
          A[0][1] * B[1][1] +
          A[0][2] * B[2][1]
 [1][0] = A[1][0] * B[0][0] +
          A[1][1] * B[1][0] +
          A[1][2] * B[2][0]
 [1][1] = A[1][0] * B[0][1] +
          A[1][1] * B[1][1] +
          A[1][2] * B[2][1]
*/

class MatrixMul {
    int main() {
        int m, n;
        
        return 0;
    }
};

System.out.print("A Rows: ");
m = scan.nextInt();
System.out.print("A Columns: ");
n = scan.nextInt();
int[][] A = new int[m][n];
for (int i = 0; i < m; i++) 
    for (int j = 0; j < n; j++) 
        A[i][j] = scan.nextInt();

System.out.print("B Rows: ");
m = scan.nextInt();
System.out.print("B Columns: ");
n = scan.nextInt();
int[][] B = new int[m][n];
for (int i = 0; i < m; i++) 
    for (int j = 0; j < n; j++) 
        B[i][j] = scan.nextInt();
    
if (A[0].length != B.length) {
    System.out.println("Imposible");
} else {
    int[][] C = new int[A.length][B[0].length];
    
    for (int k = 0; k < A.length; k++) { 
        System.err.print("{");
        for (int i = 0; i < B[0].length; i++) { 
            for (int j = 0; j < B.length; j++) { 
                C[k][i] += A[k][j] * B[j][i];
            }
            System.out.print(" " + C[k][i] + " ");
        }
        System.out.print("}\n");
    }
}