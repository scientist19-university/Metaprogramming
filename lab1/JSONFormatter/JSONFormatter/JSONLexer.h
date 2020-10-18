#pragma once

#include "Token.h"
#include "Logger.h"

#include <vector>

using namespace JSON;


class JSONLexer {

public:
  JSONLexer() = default;
  ~JSONLexer() = default;

  static Tokens Lex(std::string& i_str, const Logger& i_logger);

  static Token LexNumber(std::string& i_str);
  static Token LexJsonString(std::string& i_str);
  static Token LexBool(std::string& i_str);
  static Token LexNull(std::string& i_str);
  static Token LexSpecialChar(std::string& i_str);

};

