/*
4A
*/

#include <iostream>
#include <ostream>

class Watermelon{

public:
    void Even(int i){
        if (i == 2 || (i % 2 != 0 && (i - 2) % 2 != 0)) {
            std::cout << "NO\n" << std::endl;
        } else {
            std::cout << "YES\n" << std::endl;
        }
    }
};

int main(){
    Watermelon obj;
    int i;
    std::cin >> i;
    obj.Even(i);
    return 0;
}