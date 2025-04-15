#include <iostream>
// #include <sstream>

std::string toUpper(const std::string &str) {
    const int offset = 'a' - 'A'; // 32
    std::string out = str;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') out[i] = (str[i] - offset);
    }
    return out;
}

std::string rand(size_t length) {
    std::string result;
    result.reserve(length);
    for (size_t i = 0; i < length; i++) {
        result += 'a' + (std::rand() % 26);
    }
    return result;
}

// int longestWordLength2(const std::string &str) {
//     std::stringstream ss(str);
//     std::string word;
//     int maxLen = 0;

//     while (ss >> word) {
//         if (word.length() > maxLen) maxLen = word.length();
//     }
//     return maxLen;
// }

int longestWordLength(const std::string &str) {
    int curLen = 0;
    int maxLen = 0;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == ' ') curLen = 0;
        else {
            curLen++;
            if (curLen > maxLen) maxLen = curLen;
        }
    }
    return maxLen;
}


int main() {
    srand(time(NULL));
    std::cout << toUpper("test") << std::endl;
    std::cout << rand(20) << std::endl;
    std::cout << longestWordLength("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.") << std::endl;
    // std::cout << longestWordLength2("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.") << std::endl;

    return 0;
}
