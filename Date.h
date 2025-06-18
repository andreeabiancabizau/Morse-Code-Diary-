#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
public:
    int day, month, year;

    Date(int y, int m, int d);
    Date(const std::string& dateStr);

    std::string toString() const;
    bool operator==(const Date& other) const;

    static bool isValidDate(int y, int m, int d);
};

#endif // DATE_H
