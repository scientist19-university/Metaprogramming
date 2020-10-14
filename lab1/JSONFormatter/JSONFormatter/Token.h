#pragma once

#include <string>
#include <vector>
#include <set>

namespace JSON {

  static const char SPACE = ' ';
  static const char TAB = '\t';
  static const char NEW_LINE = '\n';
  static const char COLON = ':';
  static const char COMMA = ',';
  static const char LEFT_BRACE = '{';
  static const char RIGHT_BRACE = '}';
  static const char LEFT_BRACKET = '[';
  static const char RIGHT_BRACKET = ']';
  static const char QUOTE = '\"';

  static const std::set<char> SPECIAL_CHARS = {
    SPACE,
    TAB,
    NEW_LINE,
    COLON,
    COMMA,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    QUOTE
  };

  static const std::string TRUE = "true";
  static const std::string FALSE = "false";
  static const std::string NULL_ = "null";


  struct Token {
    int m_line_number = -1; // means unknown
    std::string m_str;

    Token(const std::string& i_str)
      : m_str(i_str)
    {
    }

    Token(char i_char) {
      m_str += i_char;
    }

    bool Empty() {
      return m_str.empty();
    }

    bool operator==(const Token& i_token) {
      return m_str == i_token.m_str;
    }

    bool operator==(const char c) {
      return (m_str.size() == 1 && m_str[0] == c);
    }

    bool IsSpecialChar() {
      if (m_str.size() != 1)
        return false;
      return SPECIAL_CHARS.find(m_str[0]) != SPECIAL_CHARS.end();
    }

    bool IsPrimitive() {
      return !IsSpecialChar();
    }

    bool IsString() {
      return m_str[0] == '"';
    }
  };


  typedef std::vector<Token> Tokens;
  static const Token EMPTY_TOKEN = Token("");
}

