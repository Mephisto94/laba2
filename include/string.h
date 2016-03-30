#ifndef CPP_STRING_H
#define CPP_STRING_H
//one definition rule

class String {
private:
    size_t length; //length of actual string, w/o EOL symvol
    char * string;
public:
    static char position;
    String();
    String(const char *str);
    String(const char *str, unsigned count);
    String(char ch, unsigned count);
    String(const String &other);
    String(String &&other);
    ~String();
    String & operator=(const String &other);
    String & operator=(String &&other);

    String & operator+=(const String &suffix);
    String & operator+=(const char *suffix);
    String & operator+=(char suffix);
    void swap(String &other);
    char & operator[](size_t pos);
    const char operator[](size_t pos) const;
/**
throws an exception if pos >= size()
*/
    char & at(size_t pos);

/**
throws an exception if pos >= size()
*/
    const char at(size_t pos) const;
/**
/return pointer to '\0' terminated C-style string
*/
    const char * data() const;
    size_t size() const;
    friend bool operator==(const String &lhs, const String &rhs);
    friend bool operator<(const String &lhs, const String &rhs);
};
String operator+(const String &lhs, const String &rhs);
String operator+(const String &lhs, const char *rhs);
String operator+(const char *lhs, const String &rhs);
bool operator!=(const String &lhs, const String &rhs);
bool operator<=(const String &lhs, const String &rhs);
bool operator>(const String &lhs, const String &rhs);
bool operator>=(const String &lhs, const String &rhs);
#endif




