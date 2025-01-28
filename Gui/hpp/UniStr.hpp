#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

class UniStr{
public:

    UniStr(const std::string& str);
    ~UniStr();

    int length();

    std::string getUniChar(int i);
    std::string get() const;

    // operators:
    
    friend std::ostream& operator<<(std::ostream& os, const UniStr& obj);

    UniStr operator=(const std::string& str);

private:

    std::vector<std::string> content;

};