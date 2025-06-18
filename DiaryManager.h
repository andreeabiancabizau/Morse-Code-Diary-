#ifndef DIARY_MANAGER_H
#define DIARY_MANAGER_H

#include "Entry.h"
#include <vector>

class DiaryManager {
public:
    DiaryManager(const std::string& diaryFile, const std::string& logFile);
    void loadEntries();
    void saveEntries();

    void addEntry(const Date& date, const std::string& text);
    void deleteEntry(const Date& date);
    void modifyEntry(const Date& date, const std::string& newText);
    void viewEntries(bool decoded) const;
    void viewLog() const;

private:
    std::vector<Entry> entries;
    std::string diaryFile;
    std::string logFile;

    void log(const std::string& action);
};

#endif
