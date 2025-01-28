#include "../hpp/UniStr.hpp"

UniStr::UniStr(const std::string& str)
{
    int i = 0;
    while (i < str.length())
    {
        std::string buff = "";

        unsigned char first_byte = str[i];
        
        if (first_byte <= 0x7f)
        {
            buff += str[i];
            i += 1;
        }
        else if ((first_byte >> 5) == 0x6)
        {
            if (i + 1 >= str.size()) throw std::invalid_argument("Invalid utf-8 sequence.");
            buff += str[i];
            buff += str[i + 1];
            i += 2;
        }
        else if ((first_byte >> 4) == 0xe)
        {
            if (i + 2 >= str.size()) throw std::invalid_argument("Invalid utf-8 sequence.");
            buff += str[i];
            buff += str[i + 1];
            buff += str[i + 2];
            i += 3;
        }
        else if ((first_byte >> 3) == 0x1e)
        {
            if (i + 3 >= str.size()) throw std::invalid_argument("Invalid utf-8 sequence.");
            buff += str[i];
            buff += str[i + 1];
            buff += str[i + 2];
            buff += str[i + 3];
            i += 4;
        }
        else
        {
            throw std::invalid_argument("Invalid utf-8 sequence.");
        }

        this->content.push_back(buff);
        
    }
}

UniStr::~UniStr() {}

int UniStr::length()
{
    return content.size();
}

std::string UniStr::getUniChar(int i)
{
    if (i < 0 || i >= this->content.size()) return "";
    return this->content[i];
}

std::string UniStr::get() const
{
    std::string output;
    for (const std::string& buff : this->content)
    {
        output += buff;
    }
    return output;
}

// operators:

std::ostream& operator<<(std::ostream& os, const UniStr& obj)
{
    os << obj.get();
    return os;
}

UniStr UniStr::operator=(const std::string& str)
{
    return UniStr(str);
}