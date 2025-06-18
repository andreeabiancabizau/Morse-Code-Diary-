#include "Date.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cstdio>  // for sscanf

Date::Date(int y, int m, int d) : day(d), month(m), year(y) {
    if (!isValidDate(year, month, day)) {
        std::ostringstream msg;
        msg << "Invalid date (int constructor): "
            << std::setfill('0') << std::setw(4) << y << "-"
            << std::setw(2) << m << "-" << std::setw(2) << d;
        throw std::invalid_argument(msg.str());
    }
}

Date::Date(const std::string& dateStr) {
    int y, m, d;

    if (sscanf(dateStr.c_str(), "%4d-%2d-%2d", &y, &m, &d) != 3) {
        throw std::invalid_argument("Invalid date format: " + dateStr);
    }

    if (!isValidDate(y, m, d)) {
        throw std::invalid_argument("Invalid date value: " + dateStr);
    }

    year = y;
    month = m;
    day = d;
}

std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(4) << year << "-"
        << std::setw(2) << month << "-" << std::setw(2) << day;
    return oss.str();
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::isValidDate(int y, int m, int d) {
    if (y < 1900 || y > 2100) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1) return false;

    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // pt an bisect
    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) {
        daysInMonth[1] = 29;
    }

    return d <= daysInMonth[m - 1];
}
