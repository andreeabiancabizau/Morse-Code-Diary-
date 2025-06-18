#include "DiaryManager.h"
#include "MorseConverter.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <algorithm>

DiaryManager::DiaryManager(const std::string& diary, const std::string& log)
    : diaryFile(diary), logFile(log) {}

void DiaryManager::loadEntries() {
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

void DiaryManager::saveEntries() {
    std::ofstream out(diaryFile);
    for (const auto& e : entries)
        out << e.toFileString() << '\n';
}

void DiaryManager::log(const std::string& action) {
    std::ofstream out(logFile, std::ios::app);
    time_t now = time(nullptr);
    out << "[" << std::ctime(&now) << "] " << action << "\n";
}

void DiaryManager::addEntry(const Date& date, const std::string& text) {
    std::string morse = MorseConverter::encode(text);
    entries.emplace_back(date, morse);
    saveEntries();
    log("Added entry for " + date.toString());
}

void DiaryManager::deleteEntry(const Date& date) {
    entries.erase(std::remove_if(entries.begin(), entries.end(),
        [&](const Entry& e) { return e.date == date; }), entries.end());
    saveEntries();
    log("Deleted entry for " + date.toString());
}

void DiaryManager::modifyEntry(const Date& date, const std::string& newText) {
    std::string morse = MorseConverter::encode(newText);
    for (auto& e : entries) {
        if (e.date == date) {
            e.morseText = morse;
            break;
        }
    }
    saveEntries();
    log("Modified entry for " + date.toString());
}

void DiaryManager::viewEntries(bool decoded) const {
    for (const auto& e : entries) {
        std::cout << "\033[1;34m" << e.date.toString() << ":\033[0m ";
        if (decoded)
            std::cout << MorseConverter::decode(e.morseText) << "\n";
        else
            std::cout << e.morseText << "\n";
    }
}

void DiaryManager::viewLog() const {
    std::ifstream in(logFile);
    if (!in) {
        std::cerr << "Cannot open log file.\n";
        return;
    }

    std::string line;
    while (std::getline(in, line))
        std::cout << "\033[1;33m" << line << "\033[0m\n";
}
