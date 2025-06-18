#include "MorseConverter.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>

std::unordered_map<char, std::string> MorseConverter::charToMorse;
std::unordered_map<std::string, char> MorseConverter::morseToChar;

void MorseConverter::loadMap(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) throw std::runtime_error("Failed to open morse_map.txt");

    char c;
    std::string code;
    while (fin >> c >> code) {
        charToMorse[c] = code;
        morseToChar[code] = c;
    }
}

std::string MorseConverter::encode(const std::string& text) {
    std::ostringstream oss;
    for (char c : text) {
        if (c == ' ') oss << "/ ";
        else oss << charToMorse[toupper(c)] << " ";
    }
    return oss.str();
}

std::string MorseConverter::decode(const std::string& morse) {
    std::istringstream iss(morse);
    std::string token, result;
    while (iss >> token) {
        if (token == "/") result += ' ';
        else result += morseToChar[token];
    }
    return result;
}
