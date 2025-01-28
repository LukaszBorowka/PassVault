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
    std::string get();

private:

    std::vector<std::string> content;

};