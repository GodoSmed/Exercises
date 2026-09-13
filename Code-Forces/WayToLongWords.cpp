/*
71A
*/

#include <cstring>
#include <iostream>
#include <ostream>
#include <string>

class WayToLongWords{
    public:
        std::string ToLong(const std::string& word){
            std::string newWord;

            newWord += word[0];
            newWord += std::to_string(word.length() - 2);
            newWord += word[word.length() - 1];

            return newWord;
        }
};

int main(){
    WayToLongWords obj;
    int num;
    std::cin >> num;
    for (int i = 0; i < num; i++) {
        std::string word;
        std::cin >> word;
        if (word.length() <= 10) {
            std::cout << word << std::endl;
        } else {
            std::string toLong;
            toLong = obj.ToLong(word);
            std::cout << toLong <<std::endl;
        }
    }

    return 0;
}


