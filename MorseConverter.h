#ifndef MORSE_CONVERTER_H
#define MORSE_CONVERTER_H

#include <string>
#include <unordered_map>

class MorseConverter {
public:
    static void loadMap(const std::string& filename);
    static std::string encode(const std::string& text);
    static std::string decode(const std::string& morse);

private:
    static std::unordered_map<char, std::string> charToMorse;
    static std::unordered_map<std::string, char> morseToChar;
};

#endif // MORSE_CONVERTER_H
