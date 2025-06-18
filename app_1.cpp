#include "DiaryManager.h"
#include "MorseConverter.h"
#include <iostream>
#include <stdexcept>
#include <string>

Date safeParseDateFromArgs(char* argv2, char* argv3, char* argv4) {
    try {
        int year = std::stoi(argv2);
        int month = std::stoi(argv3);
        int day = std::stoi(argv4);
        return Date(year, month, day);
    } catch (...) {
        throw std::invalid_argument("Failed to parse date from arguments.");
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./app_1 <command> [args]\n";
        return 1;
    }

    try {

        std::cout << "";
        for (int i = 0; i < argc; ++i) {
            std::cout << "";
        }

        MorseConverter::loadMap("morse_map.txt");
        DiaryManager manager("diary.txt", "logs.txt");
        manager.loadEntries();

        std::string cmd = argv[1];

        if (cmd == "view_entries") {
            bool decoded = (argc >= 3 && std::string(argv[2]) == "--decoded");
            manager.viewEntries(decoded);
        } else if (cmd == "add_entry") {
            if (argc < 6) {
                std::cerr << "Usage: ./app_1 add_entry <YYYY> <MM> <DD> <text>\n";
                return 1;
            }
            Date d = safeParseDateFromArgs(argv[2], argv[3], argv[4]);
            std::string text;
            for (int i = 5; i < argc; ++i) text += std::string(argv[i]) + " ";
            manager.addEntry(d, text);
        } else if (cmd == "delete_entry") {
            if (argc != 5) {
                std::cerr << "Usage: ./app_1 delete_entry <YYYY> <MM> <DD>\n";
                return 1;
            }
            Date d = safeParseDateFromArgs(argv[2], argv[3], argv[4]);
            manager.deleteEntry(d);
        } else if (cmd == "modify_entry") {
            if (argc < 6) {
                std::cerr << "Usage: ./app_1 modify_entry <YYYY> <MM> <DD> <new_text>\n";
                return 1;
            }
            Date d = safeParseDateFromArgs(argv[2], argv[3], argv[4]);
            std::string text;
            for (int i = 5; i < argc; ++i) text += std::string(argv[i]) + " ";
            manager.modifyEntry(d, text);
        } else if (cmd == "view_log") {
            manager.viewLog();
        } else {
            std::cerr << "Unknown command.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m\n";
        return 1;
    }

    return 0;
}
