#include "DiaryReader.h"
#include "MorseConverter.h"
#include <fstream>
#include <iostream>
#include <algorithm>

DiaryReader::DiaryReader(const std::string& diary) : diaryFile(diary) {}

void DiaryReader::loadEntries() {
    entries.clear();
    std::ifstream in(diaryFile);
    if (!in) return;

    std::string line;
    while (std::getline(in, line)) {
        size_t delim = line.find('|');
        if (delim != std::string::npos) {
            Date d(line.substr(0, delim));
            std::string morse = line.substr(delim + 1);
            entries.emplace_back(d, morse);
        }
    }
}

void DiaryReader::viewEntry(const Date& date, bool decoded) const {
    for (const auto& e : entries) {
        if (e.date == date) {
            std::cout << "\033[1;32m" << date.toString() << ":\033[0m ";
            if (decoded)
                std::cout << MorseConverter::decode(e.morseText) << "\n";
            else
                std::cout << e.morseText << "\n";
            return;
        }
    }
    std::cerr << "Entry not found.\n";
}

void DiaryReader::searchWord(const std::string& word) {
    searchResults.clear();
    for (const auto& e : entries) {
        std::string decoded = MorseConverter::decode(e.morseText);
        std::string decoded_lower = decoded;
        std::transform(decoded_lower.begin(), decoded_lower.end(), decoded_lower.begin(), ::tolower);
        std::string word_lower = word;
        std::transform(word_lower.begin(), word_lower.end(), word_lower.begin(), ::tolower);
        if (decoded_lower.find(word_lower) != std::string::npos)
            searchResults.push_back(e);
    std::ofstream out("search_results.txt");
    for (const auto& se : searchResults)
        out << se.date.toString() << ": " << MorseConverter::decode(se.morseText) << "\n";
    out.flush();
    }
    for (const auto& e : searchResults) {
        std::cout << "\033[1;35m" << e.date.toString() << ":\033[0m "
                  << MorseConverter::decode(e.morseText) << "\n";
    }
}


void DiaryReader::viewExport() {
    std::ifstream in("exported_results.txt");
    if (!in.is_open()) {
        std::cerr << "\033[1;31mError: exported_results.txt not found.\033[0m\n";
        return;
    }

    std::string line;
    bool hasLines = false;

    std::cout << "\033[1;36m--- Exported Results ---\033[0m\n";
    while (std::getline(in, line)) {
        if (!line.empty()) {
            std::cout << "\033[1;36m" << line << "\033[0m\n";
            hasLines = true;
        }
    }

    if (!hasLines) {
        std::cout << "\033[1;33m(No entries to display)\033[0m\n";
    }

    std::cout << "\033[1;36m------------------------\033[0m\n";
}


void DiaryReader::exportSearchResults() {
    std::ifstream in("search_results.txt");
    if (!in.is_open()) {
        std::cerr << "\033[1;31mError: search_results.txt not found. Please run search_word first.\033[0m\n";
        return;
    }


    std::string preview;
    std::getline(in, preview);
    if (preview.empty()) {
        std::cerr << "\033[1;33mWarning: search_results.txt is empty. Nothing to export.\033[0m\n";
        return;
    }

    in.clear();
    in.seekg(0);

    std::ofstream out("exported_results.txt", std::ios::app); // append mode
    if (!out.is_open()) {
        std::cerr << "\033[1;31mError: Cannot write to exported_results.txt.\033[0m\n";
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) {
            out << line << "\n";
        }
    }

    std::cout << "\033[1;32mExported results appended to exported_results.txt.\033[0m\n";
}
