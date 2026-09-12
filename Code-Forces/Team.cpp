/*
231A
*/

#include <iostream>
int main(){
	int n, P, V, T, total = 0;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		std::cin >> P;
		std::cin >> V;
		std::cin >> T;

		if ((P + V + T) > 1) {
			total++;
		}
	}
	std::cout << total <<std::endl;

	return 0;
}

