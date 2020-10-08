#pragma once

#include "Token.h"

#include <vector>

class JSONLexer {

public:
  JSONLexer() = default;
  ~JSONLexer() = default;

  static std::vector<Token> lex(const std::string& i_str);
};

