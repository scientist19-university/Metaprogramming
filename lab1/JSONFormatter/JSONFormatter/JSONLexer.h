#pragma once

#include "Token.h"

#include <vector>

class JSONLexer {

public:
  JSONLexer() = default;
  ~JSONLexer() = default;

  static JSON::Tokens Lex(std::string& i_str);

  static JSON::Token LexNumber(std::string& i_str);
  static JSON::Token LexJsonString(std::string& i_str);
  static JSON::Token LexBool(std::string& i_str);
  static JSON::Token LexNull(std::string& i_str);
  static JSON::Token LexSpecialChar(std::string& i_str);

};

