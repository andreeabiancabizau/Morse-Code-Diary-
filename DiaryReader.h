#ifndef DIARY_READER_H
#define DIARY_READER_H

#include "Entry.h"
#include <vector>

class DiaryReader {
public:
    DiaryReader(const std::string& diaryFile);
    void loadEntries();
    void viewEntry(const Date& date, bool decoded) const;
    void searchWord(const std::string& word);
    void exportSearchResults();
    void viewExport();

private:
    std::vector<Entry> entries;
    std::string diaryFile;
    std::vector<Entry> searchResults;
};

#endif
