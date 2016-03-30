#include <stddef.h>
#include <stdexcept>
#include "MyString.h"


String::String() {
    length = 0;
    string = new char[1];
    string[0] = '\0';
}

String::String(const char *str) {
    length = 0;
    const char *temp = str;
    while (*(temp++) != '\0') {
        length++;
    }
    char *strCopy = new char[length + 1];
    for (std::size_t i = 0; i < length; i++) {
        strCopy[i] = str[i];
    }

    string = strCopy;
    string[length] = '\0';
}

//cut from beginning
String::String(const char *str, unsigned count) {
    string = new char[count + 1];
    length = count;
    for (std::size_t i = 0; i <= length; i++) {
        string[i] = str[i];
    }
}

//repeat symbol count times
String::String(char ch, unsigned count) {
    length = count;
    string = new char[length + 1];
    char *temp = string;

    for (std::size_t i = 0; i < length; ++i) {
        *(temp++) = ch;
    }
    *(temp) = '\0';

}

//copy constructor
String::String(const String &other) {
    string = new char[other.length + 1];
    length = other.length;
    for (size_t i = 0; i <= length; ++i) {
        string[i] = other.string[i];
    }
}


String::String(String &&other) {
    string = other.string;
    length = other.length;
    //other.string[0] = '\0'; //no magic
    char nully = '\0';
    other.string = &(nully); //magic
    other.length = 0;
}


String::~String() {
    if (string[0] != '\0') {
        delete[] string;
    }
}

//optize
String &String::operator=(const String &other) {
    delete[] string;
    string = new char[other.length + 1];
    length = other.length;
    for (size_t i = 0; i < length; i++) {
        string[i] = other.string[i];
    }
    string[length] = '\0';
    return *this;
}

String &String::operator=(String &&other) {
    delete[] string;
    string = other.string;
    length = other.length;

    char nully = '\0';
    other.string = &(nully); //magic #2
    other.length = 0;
    return *this;

}

String &String::operator+=(const String &suffix) {
    char *concat = new char[length + suffix.length + 1];
    for (size_t i = 0; i < length; ++i) {
        concat[i] = string[i];
    }
    for (size_t j = length; j < length + suffix.length; ++j) {
        concat[j] = suffix.string[j - length];
    }
    concat[length + suffix.length] = '\0';
    delete[] string;
    string = concat;
    length += suffix.length;

    return *this;
}

String &String::operator+=(const char *suffix) {
    size_t suffixLength = 0;
    const char *temp = suffix;
    while (*(temp++) != '\0') {
        suffixLength++;
    }

    char *concat = new char[length + suffixLength + 1];
    for (size_t i = 0; i < length; ++i) {
        concat[i] = string[i];
    }
    for (size_t j = length; j < length + suffixLength; ++j) {
        concat[j] = suffix[j - length];
    }
    concat[length + suffixLength] = '\0';
    delete[] string;
    string = concat;
    length += suffixLength;
    return *this;
}

String &String::operator+=(char suffix) {
    char *concat = new char[length + 2];
    for (size_t i = 0; i < length; ++i) {
        concat[i] = string[i];
    }
    concat[length] = suffix;
    concat[length + 1] = '\0';
    delete[] string;
    string = concat;
    length++;
    return *this;
}

void String::swap(String &other) {
    char *tmp;
    size_t tmpLength;
    tmp = string;
    tmpLength = length;
    string = other.string;
    length = other.length;
    other.string = tmp;
    other.length = tmpLength;
}

char &String::operator[](size_t pos) {
    return string[pos];
}

const char String::operator[](size_t pos) const {
    return string[pos];
}

char &String::at(size_t pos) {
    if (pos >= length) {
        throw std::out_of_range("");
    }
    return string[pos];
}

//this is the same
const char String::at(size_t pos) const {
    if (pos >= length) {
        throw std::out_of_range("");
    }
    return string[pos];
}

const char *String::data() const {
    return string;
}

size_t String::size() const {
    return length;
}

bool operator==(const String &lhs, const String &rhs) {
    if (lhs.length == rhs.length) {
        for (size_t i = 0; i < lhs.length; ++i) {
            if (lhs.string[i] != rhs.string[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool operator<(const String &lhs, const String &rhs) {
    size_t size;
    size = lhs.length <= rhs.length ? lhs.length : rhs.length;
    for (size_t i = 0; i < size; ++i) {
        if (lhs.string[i] < rhs.string[i]) {
            return true;
        } else if (lhs.string[i] > rhs.string[i]) {
            return false;
        }
    }
    if (rhs.length > lhs.length) {
        return true;
    }
    return false;
}


String operator+(const String &lhs, const String &rhs) {
    String tmp(lhs);
    tmp += rhs;
    return tmp;
//    return (String(lhs) += rhs);
}

String operator+(const String &lhs, const char *rhs) {
    return String(lhs) += rhs;
}

String operator+(const char *lhs, const String &rhs) {
    return String(rhs) += lhs;
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




























