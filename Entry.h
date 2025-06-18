#ifndef ENTRY_H
#define ENTRY_H

#include "Date.h"
#include <string>

class Entry {
public:
    Date date;
    std::string morseText;

    Entry(const Date& d, const std::string& morse);
    std::string toFileString() const;
};

#endif // ENTRY_H
