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

#include <iostream>

int main() {
  int m, n;
  std::cout << "A Rows: " << std::endl;
  std::cin >> m;

  std::cout << "A Columns: " << std::endl;
  std::cin >> n;

  int A[m][n], am = m, an = n;
  
  std::cout << "A Values: " << std::endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> A[i][j];
    }
  }

  std::cout << "B Rows: " << std::endl;
  std::cin >> m;

  std::cout << "B Columns: " << std::endl;
  std::cin >> n;

  std::cout << "B Values: " << std::endl;
  int B[m][n], bm = m, bn = n;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> B[i][j];
    }
  }

  if (an != bm) {
    std::cout << "Imposible" << std::endl;
  } else {
    int C[am][bn];

    for (int i = 0; i < am; i++) {
      for (int j = 0; j < bn; j++) {
        C[i][j] = 0;
      }
    }

    for (int k = 0; k < am; k++) {
      std::cout << "{" << std::flush;
      for (int i = 0; i < bn; i++) {
        for (int j = 0; j < bm; j++) {
          C[k][i] += A[k][j] * B[j][i];
        }
        std::cout << " " << C[k][i] << " " << std::flush;
      }
      std::cout << "}" << std::endl;
    }
  }

  return 0;
}