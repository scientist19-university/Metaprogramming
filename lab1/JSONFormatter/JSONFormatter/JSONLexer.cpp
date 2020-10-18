#include "pch.h"
#include "JSONLexer.h"

namespace {
  bool _IsCloseQuote(const std::string& i_string, int i_index) {
    return i_string[i_index] == '"' && i_string[i_index - 1] != '\\';
  }
}


Tokens JSONLexer::Lex(std::string& i_str){
  Tokens tokens;

  int cur_line_number = 1;
  while (!i_str.empty()) {

    auto bool_token = LexBool(i_str);
    bool_token.m_line_number = cur_line_number;
    if (!bool_token.Empty()) {
      tokens.push_back(bool_token);
      continue;
    }

    auto null_token = LexNull(i_str);
    null_token.m_line_number = cur_line_number;
    if (!null_token.Empty()) {
      tokens.push_back(null_token);
      continue;
    }

    auto json_token = LexJsonString(i_str);
    json_token.m_line_number = cur_line_number;
    if (!json_token.Empty()) {
      tokens.push_back(json_token);
      continue;
    }

    auto char_token = LexSpecialChar(i_str);
    char_token.m_line_number = cur_line_number;
    if (char_token == NEW_LINE)
      cur_line_number++;
    if (!char_token.Empty()) {
      tokens.push_back(char_token);
      continue;
    }

    auto number_token = LexNumber(i_str);
    number_token.m_line_number = cur_line_number;
    if (!number_token.Empty()) {
      tokens.push_back(number_token);
      continue;
    }

    // log error 'Unexpected character'
    i_str.erase(0, 1);
  }

  return tokens;
}

Token JSONLexer::LexNumber(std::string & i_str){

  size_t pos;
  try {
    std::stof(i_str, &pos);
  }
  catch (...) {
    return EMPTY_TOKEN;
  }

  auto str_number = i_str.substr(0, pos);
  i_str.erase(0, pos);

  return Token(str_number);
}

Token JSONLexer::LexJsonString(std::string & i_str){
  std::string json_string;

  if (i_str[0] != QUOTE)
    return EMPTY_TOKEN;

  json_string += QUOTE;

  int k = 1;
  while (k < (int)i_str.size() && !_IsCloseQuote(i_str, k)) {
    json_string += i_str[k];
    k++;
  }

  if (k < (int)i_str.size()) {
    json_string += i_str[k];
    i_str.erase(0, k+1);

    return Token(json_string);
  }

  i_str.erase(i_str.begin(), i_str.end());

  // log error "No closing quote found"

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

  // TODO: replace with new method
  if (SPECIAL_CHARS.find(c) != SPECIAL_CHARS.end()) {
    i_str.erase(i_str.begin());
    return Token(c);
  }

  return EMPTY_TOKEN;
}
