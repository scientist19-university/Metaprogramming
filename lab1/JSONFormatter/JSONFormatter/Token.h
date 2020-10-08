#pragma once

#include <string>
#include <vector>

namespace JSON {

  struct Token {
    int m_line_number = -1; // means unknown
    std::string m_str;

    Token(const std::string& i_str)
      : m_str(i_str)
    {
    }

    bool Empty() {
      return m_str.empty();
    }

    bool operator==(const Token& i_token) {
      return m_str == i_token.m_str;
    }

  };

  typedef std::vector<Token> Tokens;

  static const char SPACE = ' ';
  static const char TAB = '/t';
  static const char NEW_LINE = '/n';
  static const char COLON = ':';
  static const char COMMA = ',';
  static const char LEFT_BRACE = '{';
  static const char RIGHT_BRACE = '}';
  static const char LEFT_BRACKET = '[';
  static const char RIGHT_BRACKET = ']';
}
