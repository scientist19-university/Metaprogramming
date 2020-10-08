#include "pch.h"
#include "JSONLexer.h"


using namespace JSON;

Tokens JSONLexer::Lex(std::string& i_str){
  Tokens tokens;

  while (!i_str.empty()) {

    auto number_token = LexNumber(i_str);
    if (!number_token.Empty()) {
      tokens.push_back(number_token);
      continue;
    }

    auto bool_token = LexBool(i_str);
    if (!bool_token.Empty()) {
      tokens.push_back(bool_token);
      continue;
    }

    auto null_token = LexNull(i_str);
    if (!null_token.Empty()) {
      tokens.push_back(null_token);
      continue;
    }

    auto json_token = LexJsonString(i_str);
    if (!json_token.Empty()) {
      tokens.push_back(json_token);
      continue;
    }

    auto char_token = LexSpecialChar(i_str);
    if (!char_token.Empty()) {
      tokens.push_back(char_token);
      continue;
    }

    // log error 'Unexpected character'
  }
}
