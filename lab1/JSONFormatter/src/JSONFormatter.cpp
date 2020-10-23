#include "pch.h"
#include "JSONFormatter.h"

#include <algorithm>

namespace {

  void _AddWhitespaces(Tokens& i_tokens, int i_level, const ConfigInfo& i_config_info) {

    int chars_for_level = i_config_info.m_use_tabs ? 1 : i_config_info.m_indent_size;
    char ch = i_config_info.m_use_tabs ? TAB : SPACE;

    for (int i = 0; i < i_level * chars_for_level; i++)
      i_tokens.push_back(ch);
  }

  void _AddWhitespacesWithNL(Tokens& i_tokens, int i_level, int i_nl_number, const ConfigInfo& i_config_info) {
    int nl_number = std::max(1, std::min(i_nl_number, i_config_info.m_max_blank_lines_number + 1));

    for (int i = 0; i < nl_number; i++) {
      i_tokens.push_back(NEW_LINE);

      // for the last new line indent should always be present as there is next non-white token
      if (i == nl_number - 1 || i_config_info.m_keep_indents_on_empty_lines)
        _AddWhitespaces(i_tokens, i_level, i_config_info);
    }
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

  int _CountNewLines(const Tokens& i_tokens) {
    int ans = 0;
    for (const Token& token : i_tokens)
      if (token == NEW_LINE)
        ans++;
    return ans;
  }

  bool _NeedWrap(const Token& i_token, const ConfigInfo& i_config_info) {
    bool is_brace = (i_token == LEFT_BRACE || i_token == RIGHT_BRACE);
    bool is_bracket = (i_token == LEFT_BRACKET || i_token == RIGHT_BRACKET);
    return ((is_brace && i_config_info.m_wrap_objects) || (is_bracket && i_config_info.m_wrap_arrays));
  }

  bool _NeedSpaceWithin(const Token& i_token, const ConfigInfo& i_config_info) {
    bool is_brace = (i_token == LEFT_BRACE || i_token == RIGHT_BRACE);
    bool is_bracket = (i_token == LEFT_BRACKET || i_token == RIGHT_BRACKET);
    return ((is_brace && i_config_info.m_space_within_braces) || (is_bracket && i_config_info.m_space_within_brackets));
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
    int actual_nl_number = _CountNewLines(ws_actual);

    Tokens ws_ref;
    if (cur_token == LEFT_BRACE || cur_token == LEFT_BRACKET) {

      level++;

      if (_NeedWrap(cur_token, i_config_info))
        _AddWhitespacesWithNL(ws_ref, level, actual_nl_number, i_config_info);
      else if (_NeedSpaceWithin(cur_token, i_config_info))
        ws_ref.push_back(SPACE);

      _VerifyWhitespaces(ws_actual, ws_ref, i_logger, cur_token);
    }
    else if (cur_token == COMMA) {

      if (i_config_info.m_space_before_comma)
        _VerifyWhitespaces(prev_ws_actual, { SPACE }, i_logger, cur_token);
      else
        _VerifyWhitespaces(prev_ws_actual, {}, i_logger, cur_token);

      if (i_config_info.m_space_after_comma)
        ws_ref.push_back(SPACE);
      _AddWhitespacesWithNL(ws_ref, level, actual_nl_number, i_config_info);

      _VerifyWhitespaces(ws_actual, ws_ref, i_logger, cur_token);
    }
    else if (cur_token == COLON) {

      if (i_config_info.m_space_before_colon)
        _VerifyWhitespaces(prev_ws_actual, { SPACE }, i_logger, cur_token);
      else
        _VerifyWhitespaces(prev_ws_actual, {}, i_logger, cur_token);

      if (i_config_info.m_space_after_colon)
        ws_ref.push_back(SPACE);

      _VerifyWhitespaces(ws_actual, ws_ref, i_logger, cur_token);
    }
    else if (cur_token == RIGHT_BRACE || cur_token == RIGHT_BRACKET) {

      level--;

      if (_NeedWrap(cur_token, i_config_info))
        _AddWhitespacesWithNL(ws_ref, level, _CountNewLines(prev_ws_actual), i_config_info);
      else if (_NeedSpaceWithin(cur_token, i_config_info))
        ws_ref.push_back(SPACE);

      _VerifyWhitespaces(prev_ws_actual, ws_ref, i_logger, cur_token);
    }

    prev_ws_actual = ws_actual;
  }
}

Tokens JSONFormatter::Format(const Tokens& i_tokens, const ConfigInfo& i_config_info) {
  
  Tokens tokens = i_tokens;
  Tokens formatted_tokens;

  Tokens prev_ws;
  int level = 0;

  while (!tokens.empty()) {

    Token cur_token = tokens.front();
    tokens.erase(tokens.begin());

    Tokens ws = _PopWhitespaces(tokens);
    int nl_number = _CountNewLines(ws);
  
    if (cur_token == LEFT_BRACE || cur_token == LEFT_BRACKET) {

      formatted_tokens.push_back(cur_token);
      level++;

      if (_NeedWrap(cur_token, i_config_info)) 
        _AddWhitespacesWithNL(formatted_tokens, level, nl_number, i_config_info);
      else if (_NeedSpaceWithin(cur_token, i_config_info))
        formatted_tokens.push_back(SPACE);

    }
    else if (cur_token == RIGHT_BRACE || cur_token == RIGHT_BRACKET) {

      level--;

      if (_NeedWrap(cur_token, i_config_info))
        _AddWhitespacesWithNL(formatted_tokens, level, _CountNewLines(prev_ws), i_config_info);
      else if (_NeedSpaceWithin(cur_token, i_config_info))
        formatted_tokens.push_back(SPACE);

      formatted_tokens.push_back(cur_token);
    }
    else if (cur_token == COMMA) {
      if (i_config_info.m_space_before_comma)
        formatted_tokens.push_back(SPACE);

      formatted_tokens.push_back(cur_token);

      if (i_config_info.m_space_after_comma)
        formatted_tokens.push_back(SPACE);

      _AddWhitespacesWithNL(formatted_tokens, level, nl_number, i_config_info);
    }
    else if (cur_token == COLON) {
      if (i_config_info.m_space_before_colon)
        formatted_tokens.push_back(SPACE);

      formatted_tokens.push_back(cur_token);

      if (i_config_info.m_space_after_colon)
        formatted_tokens.push_back(SPACE);
    }
    else
      formatted_tokens.push_back(cur_token);

    prev_ws = ws;
  }

  return formatted_tokens;
}
