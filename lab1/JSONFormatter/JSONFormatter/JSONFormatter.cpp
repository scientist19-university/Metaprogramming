#include "pch.h"
#include "JSONFormatter.h"

#include <algorithm>

namespace {

  void _AddWhitespaces(Tokens& i_tokens, int i_level, const ConfigInfo& i_config_info) {

    int chars_for_level = i_config_info.m_use_tabs ? i_config_info.m_tabs_per_level : i_config_info.m_spaces_per_level;
    char ch = i_config_info.m_use_tabs ? TAB : SPACE;

    for (int i = 0; i < i_level * chars_for_level; i++)
      i_tokens.push_back(ch);
  }

  Tokens _PopWhitespaces(Tokens& i_tokens) {
    Tokens res;
    int k = 0;
    while (k < (int)i_tokens.size() && i_tokens[k].IsWhitespace()) {
      res.push_back(i_tokens[k]);
      k++;
    }

    i_tokens.erase(i_tokens.begin(), i_tokens.begin() + k);    
    return res;
  }

  void _VerifyWhitespaces(const Tokens& i_actual_tokens, const Tokens& i_ref_tokens, const Logger& i_logger, const Token& i_last_token) {
    int k = 0;
    int actual_size = i_actual_tokens.size(),
        ref_size = i_ref_tokens.size();

    int min_size = std::min(actual_size, ref_size);

    while (k < min_size && i_actual_tokens[k] == i_ref_tokens[k])
      k++;

    if (k == min_size) {
      if (actual_size == ref_size)
        return;
      else if (actual_size < ref_size) {
        int line_number = k > 0 ? i_actual_tokens[k - 1].m_line_number : i_last_token.m_line_number;
        i_logger.PrintErrorMissingChar(line_number, i_ref_tokens[k]);
        return;
      }
      else {
        i_logger.PrintErrorExtraChar(i_actual_tokens[k]);
        return;
      }
    }
    else {
      i_logger.PrintErrorWrongChar(i_actual_tokens[k], i_ref_tokens[k]);
    }
  }
}

void JSONFormatter::Verify(const Tokens& i_tokens, const ConfigInfo& i_config_info, const Logger& i_logger){
  Tokens tokens = i_tokens;
  Tokens ws = _PopWhitespaces(tokens);
  _VerifyWhitespaces(ws, {}, i_logger, EMPTY_TOKEN);

  Tokens prev_ws_actual;
  int level = 0;
  while (!tokens.empty()) {
    Token cur_token = tokens.front();
    tokens.erase(tokens.begin());

    Tokens ws_actual = _PopWhitespaces(tokens);

    Tokens ws_ref;
    if (cur_token == LEFT_BRACE || cur_token == LEFT_BRACKET) {
      ws_ref.push_back(NEW_LINE);
      level++;
      _AddWhitespaces(ws_ref, level, i_config_info);
      _VerifyWhitespaces(ws_actual, ws_ref, i_logger, cur_token);
    }
    else if (cur_token == COMMA) {
      ws_ref.push_back(NEW_LINE);
      _AddWhitespaces(ws_ref, level, i_config_info);
      _VerifyWhitespaces(ws_actual, ws_ref, i_logger, cur_token);
    }
    else if (cur_token == COLON) {
      _VerifyWhitespaces(prev_ws_actual, ws_ref, i_logger, cur_token);
      ws_ref.push_back(SPACE);
      _VerifyWhitespaces(ws_actual, ws_ref, i_logger, cur_token);
    }
    else if (cur_token == RIGHT_BRACE || cur_token == RIGHT_BRACKET) {
      ws_ref.push_back(NEW_LINE);
      level--;
      _AddWhitespaces(ws_ref, level, i_config_info);
      _VerifyWhitespaces(prev_ws_actual, ws_ref, i_logger, cur_token);
    }

    prev_ws_actual = ws_actual;
  }
}

Tokens JSONFormatter::Format(const Tokens& i_tokens, const ConfigInfo& i_config_info) {

  Tokens simple_tokens;
  for (const Token& token : i_tokens)
    if (!token.IsWhitespace())
      simple_tokens.push_back(token);
  
  Tokens formatted_tokens;
  int level = 0;
  for (Token& token : simple_tokens) {
  
    if (token == LEFT_BRACE || token == LEFT_BRACKET) {
      formatted_tokens.push_back(token);
      formatted_tokens.push_back(NEW_LINE);
      level++;
      _AddWhitespaces(formatted_tokens, level, i_config_info);
    }
    else if (token == RIGHT_BRACE || token == RIGHT_BRACKET) {
      formatted_tokens.push_back(NEW_LINE);
      level--;
      _AddWhitespaces(formatted_tokens, level, i_config_info);
      formatted_tokens.push_back(token);
    }
    else if (token == COMMA) {
      formatted_tokens.push_back(token);
      formatted_tokens.push_back(NEW_LINE);
      _AddWhitespaces(formatted_tokens, level, i_config_info);
    }
    else if (token == COLON) {
      formatted_tokens.push_back(token);
      formatted_tokens.push_back(SPACE);
    }
    else
      formatted_tokens.push_back(token);
  }

  return formatted_tokens;
}
