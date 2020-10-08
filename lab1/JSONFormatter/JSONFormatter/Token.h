#pragma once

#include <string>

struct Token {
  int m_line_number = -1; // means unknown
  std::string m_str;

  Token(const std::string& i_str)
    : m_str(i_str)
  {
  }

  bool operator==(const Token& i_token){
    return m_str == i_token.m_str;
  }

};
 

