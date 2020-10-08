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

  return tokens;
}

Token JSONLexer::LexNumber(std::string & i_str){
  std::string number;

  int k = 0;
  while (k < i_str.size() && '0' <= i_str[k] && i_str[k] <= '9') {
    number += i_str[k];
    k++;
  }
  i_str.erase(i_str.begin(), i_str.begin() + k);

  return Token(number);
}

Token JSONLexer::LexJsonString(std::string & i_str){
  std::string json_string;

  if (i_str[0] != QUOTE)
    return EMPTY_TOKEN;

  json_string += QUOTE;

  int k = 1;
  while (k < i_str.size() && i_str[k] != QUOTE) {
    json_string += i_str[k];
    k++;
  }

  if (i_str[k] == QUOTE) {
    json_string += i_str[k];

    return Token(json_string);
  }

  i_str.erase(i_str.begin(), i_str.begin() + k);

  // log error "No closing brace found

  return EMPTY_TOKEN;
}

Token JSONLexer::LexBool(std::string & i_str){

  auto true_string = i_str.substr(0, TRUE.size());
  if (true_string == TRUE) {
    i_str.erase(0, TRUE.size());
    return Token(true_string);
  }

  auto false_string = i_str.substr(0, FALSE.size());
  if (false_string == FALSE) {
    i_str.erase(0, FALSE.size());
    return Token(false_string);
  }

  return EMPTY_TOKEN;
}

Token JSONLexer::LexNull(std::string & i_str){

  auto null_string = i_str.substr(0, NULL_.size());
  if (null_string == NULL_) {
    i_str.erase(0, NULL_.size());
    return Token(null_string);
  }

  return EMPTY_TOKEN;
}

Token JSONLexer::LexSpecialChar(std::string& i_str){
  
  char c = i_str[0];
  if (SPECIAL_CHARS.find(c) != SPECIAL_CHARS.end()) {
    auto special_char = i_str.substr(0, 1);
    i_str.erase(i_str.begin());
    return Token(special_char);
  }

  return EMPTY_TOKEN;
}
