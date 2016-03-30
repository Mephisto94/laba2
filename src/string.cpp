#include <stddef.h>
#include <stdexcept>
#include <cstring>
#include "string_header.h"

char String::null_terminator = '\0';

String::String() {
    length = 0;
    string = new char[1];
    string[0] = null_terminator;
}

String::String(const char *str) {
    length = 0;
    length = std::strlen(str);
    char *strCopy = new char[length + 1];
    std::strcpy(strCopy, str);
    string = strCopy;
}


String::String(const char *str, unsigned count) {
    string = new char[count + 1];
    length = count;
    for (std::size_t i = 0; i <= length; i++) {
        string[i] = str[i];
    }
}


String::String(char ch, unsigned count) {
    length = count;
    string = new char[length + 1];
    char *temp = string;
    for (std::size_t i = 0; i < length; ++i) {
        *(temp++) = ch;
    }
    *temp = null_terminator;
}


String::String(const String &other) {
    string = new char[other.length + 1];
    length = other.length;
    std::strcpy(string, other.string);
}


String::String(String &&other) {
    string = other.string;
    length = other.length;
    other.string = &(null_terminator);
    other.length = 0;
}


String::~String() {
    if (string[0] != null_terminator & length != 0) {
        delete[] string;
    }
}

String &String::operator=(const String &other) {
    delete[] string;
    string = new char[other.length + 1];
    length = other.length;
    std::strcpy(string, other.string);
    return *this;
}

String &String::operator=(String &&other) {
    delete[] string;
    string = other.string;
    length = other.length;
    other.string = &(null_terminator);
    other.length = 0;
    return *this;

}

String &String::operator+=(const String &suffix) {
    length += suffix.length;
    std::strcat(string, suffix.string);
    return *this;
}

String &String::operator+=(const char *suffix) {
    *this += String(suffix);
    return *this;
}

String &String::operator+=(char suffix) {
    char *concat = new char[length + 2];
    std::strcpy(concat, string);
    concat[length] = suffix;
    concat[length + 1] = null_terminator;
    delete[] string;
    string = concat;
    length++;
    return *this;
}

void String::swap(String &other) {
    std::swap(length, other.length);
    std::swap(string, other.string);
}

char &String::operator[](std::size_t pos) {
    return string[pos];
}

const char String::operator[](std::size_t pos) const {
    return string[pos];
}

char &String::at(std::size_t pos) {
    if (pos >= length) {
        throw std::out_of_range("index is out of range");
    }
    return string[pos];
}

const char String::at(std::size_t pos) const {
    if (pos >= length) {
        throw std::out_of_range("index if out of range");
    }
    return string[pos];
}

const char *String::data() const {
    return string;
}

std::size_t String::size() const {
    return length;
}

bool operator==(const String &lhs, const String &rhs) {
    if (lhs.length == rhs.length) {
        if (std::strcmp(lhs.string, rhs.string) != 0) {
            return false;
        }
        return true;
    }
    return false;
}

bool operator<(const String &lhs, const String &rhs) {
    //strcmp returns negative if lhs appears before rhs in lexicographical order
    int comp_result = std::strcmp(lhs.string, rhs.string);
    if (comp_result < 0) {
        return true;
    }
    else if (comp_result > 0) {
        return false;
    }
    if (rhs.length > lhs.length) {
        return true;
    }
    return false;
}


String operator+(const String &lhs, const String &rhs) {
    return (String(lhs) += rhs);
}

String operator+(const String &lhs, const char *rhs) {
    return String(lhs) += rhs;
}

String operator+(const char *lhs, const String &rhs) {
    return String(lhs) += rhs;
}

bool operator!=(const String &lhs, const String &rhs) {
    return !(lhs == rhs);
}

bool operator<=(const String &lhs, const String &rhs) {
    return (lhs == rhs) || (lhs < rhs);
}

bool operator>(const String &lhs, const String &rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const String &lhs, const String &rhs) {
    return !(lhs < rhs);
}


std::ostream &operator<<(std::ostream &stream, const String &A) {
    return stream << A.data();
}
