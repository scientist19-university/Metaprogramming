#include "pch.h"
#include "JSONFormatter.h"

namespace {

  void _AddSeparatingChars(Tokens& i_tokens, int i_level, ConfigInfo& i_config_info) {

    int chars_for_level = i_config_info.m_use_tabs ? i_config_info.m_tabs_per_level : i_config_info.m_spaces_per_level;
    char ch = i_config_info.m_use_tabs ? TAB : SPACE;

    for (int i = 0; i < i_level * chars_for_level; i++)
      i_tokens.push_back(ch);
  }

}

void JSONFormatter::Verify(Tokens & i_tokens)
{
}

Tokens JSONFormatter::Format(Tokens & i_tokens, ConfigInfo& i_config_info) {

  Tokens simple_tokens;
  for (Token& token : i_tokens)
    if (!(token == SPACE || token == TAB || token == NEW_LINE))
      simple_tokens.push_back(token);
  
  Tokens formatted_tokens;
  int level = 0;
  for (Token& token : simple_tokens) {
  
    if (token == LEFT_BRACE || token == LEFT_BRACKET) {
      formatted_tokens.push_back(token);
      formatted_tokens.push_back(NEW_LINE);
      level++;
      _AddSeparatingChars(formatted_tokens, level, i_config_info);
    }
    else if (token == RIGHT_BRACE || token == RIGHT_BRACKET) {
      formatted_tokens.push_back(NEW_LINE);
      level--;
      _AddSeparatingChars(formatted_tokens, level, i_config_info);
      formatted_tokens.push_back(token);
    }
    else if (token == COMMA) {
      formatted_tokens.push_back(token);
      formatted_tokens.push_back(NEW_LINE);
      _AddSeparatingChars(formatted_tokens, level, i_config_info);
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
