#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

class UniStr{
public:
  UniStr(const std::string& str) {
    this->generateFromString(str);
  }

  UniStr(const UniStr& str) {
    this->generateFromString(str.get());
  }

  UniStr(const char* str) {
    this->generateFromString(std::string(str));
  }

  int length() {
    return this->content.size();
  }

  std::string getUniChar(int index) const {
    if (index < 0 || index >= this->content.size()) throw std::invalid_argument("Invalid index.");
    return this->content[index];
  }

  std::string get() const {
    std::string result = "";
    for (const std::string& s : this->content) {
      result += s;
    }
    return result;
  }

  friend std::ostream& operator<<(std::ostream& os, const UniStr& str) {
    os << str.get();
    return os;
  }

private:
  void generateFromString(const std::string& str) {
    int i = 0;
    while (i < str.length()) {
      std::string buff = "";

      unsigned char first_byte = str[i];

      if (first_byte <= 0x7f) {
        buff += str[i];
        i += 1;
      }
      else if ((first_byte >> 5) == 0x6) {
        if (i + 1 >= str.size()) throw std::invalid_argument("Invalid utf-8 sequence.");
        buff += str[i];
        buff += str[i + 1];
        i += 2;
      }
      else if ((first_byte >> 4) == 0xe) {
        if (i + 2 >= str.size()) throw std::invalid_argument("Invalid utf-8 sequence.");
        buff += str[i];
        buff += str[i + 1];
        buff += str[i + 2];
        i += 3;
      }
      else if ((first_byte >> 3) == 0x1e) {
        if (i + 3 >= str.size()) throw std::invalid_argument("Invalid utf-8 sequence.");
        buff += str[i];
        buff += str[i + 1];
        buff += str[i + 2];
        buff += str[i + 3];
        i += 4;
      }
      else {
        throw std::invalid_argument("Invalid utf-8 sequence.");
      }

      this->content.push_back(buff);
    }
  }

  std::vector<std::string> content;
};