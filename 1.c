#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

bool isPalindrome(const std::string& str) {
    int left = 0;
    int right = str.length() - 1;
    
    while (left < right) {
        // Пропускаем не-буквы слева
        while (left < right && !std::isalpha(static_cast<unsigned char>(str[left]))) {
            left++;
        }
        // Пропускаем не-буквы справа
        while (left < right && !std::isalpha(static_cast<unsigned char>(str[right]))) {
            right--;
        }
        
        // Сравниваем буквы (без учета регистра)
        if (std::tolower(static_cast<unsigned char>(str[left])) != 
            std::tolower(static_cast<unsigned char>(str[right]))) {
            return false;
        }
        
        left++;
        right--;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " \"string to check\"" << std::endl;
        return 1;
    }
    
    std::string input = argv[1];
    bool result = isPalindrome(input);
    
    std::cout << (result ? "true" : "false") << std::endl;
    
    return 0;
}
