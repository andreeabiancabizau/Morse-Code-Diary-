#include "Entry.h"

Entry::Entry(const Date& d, const std::string& morse) : date(d), morseText(morse) {}

std::string Entry::toFileString() const {
    return date.toString() + "|" + morseText;
}
