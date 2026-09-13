/*
282A
*/

#include <iostream>
#include <string>
int main() {
  int n, total = 0;
  std::string in;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::cin >> in;

    if (in == "X++" || in == "++X") {
      total++;
    } else if (in == "X--" || in == "--X") {
      total--;
    }
  }

  std::cout << total <<std::endl;

  return 0;
}
