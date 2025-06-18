#include "DiaryReader.h"
#include "MorseConverter.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./app_2 <command> [args]\n";
        return 1;
    }

    try {
        MorseConverter::loadMap("morse_map.txt");
        DiaryReader reader("diary.txt");
        reader.loadEntries();

        std::string cmd = argv[1];
        if (cmd == "view_entry") {
            if (argc < 5) {
                std::cerr << "Usage: ./app_2 view_entry <YYYY> <MM> <DD> [--decoded]\n";
                return 1;
            }
            Date d(std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]));
            bool decoded = (argc == 6 && std::string(argv[5]) == "--decoded");
            reader.viewEntry(d, decoded);
        } else if (cmd == "search_word") {
            if (argc != 3) {
                std::cerr << "Usage: ./app_2 search_word <word>\n";
                return 1;
            }
            reader.searchWord(argv[2]);
        } else if (cmd == "export_search_results") {
            reader.exportSearchResults();
        } else if (cmd == "view_export") {
            reader.viewExport();
        } else {
            std::cerr << "Unknown command.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mError: " << e.what() << "\033[0m\n";
        return 1;
    }

    return 0;
}
