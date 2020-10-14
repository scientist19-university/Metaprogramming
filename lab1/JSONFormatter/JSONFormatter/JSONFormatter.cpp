#include "pch.h"
#include "JSONFormatter.h"


void JSONFormatter::Verify(Tokens & i_tokens)
{
}

Tokens JSONFormatter::Format(Tokens & i_tokens) {

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
      for (int i = 0; i < level * 2; i++)
        formatted_tokens.push_back(SPACE);
    }
    else if (token == RIGHT_BRACE || token == RIGHT_BRACKET) {
      formatted_tokens.push_back(NEW_LINE);
      level--;
      for (int i = 0; i < level * 2; i++)
        formatted_tokens.push_back(SPACE);
      formatted_tokens.push_back(token);
    }
    else if (token == COMMA) {
      formatted_tokens.push_back(token);
      formatted_tokens.push_back(NEW_LINE);
      for (int i = 0; i < level * 2; i++)
        formatted_tokens.push_back(SPACE);
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

/*
void JSONFormatter::VerifyObject(int i_level, bool i_new_line){

  if (!i_new_line) {
    //VerifySpacesAndTabs(true, 0);
    VerifySeparatingChars(0, 0, 0);

    Token next_token = NextToken();
    if (next_token.IsPrimitive()) {
      PopToken();
      return;
    }

    if (next_token == LEFT_BRACE) {
      PopToken();
      VerifySeparatingChars(0, 0, 1);
    }

    if (next_token == LEFT_BRACKET) {
      VerifyArray(i_level, false);
      return;
    }

    std::cout << "Syntax error!" << std::endl;
    return;
  }
  else{

  }


}

void JSONFormatter::VerifyArray(int i_level, bool i_new_line)
{
}

Tokens JSONFormatter::FormatObject(int i_level){
  Tokens ans;

  VerifySeparatingChars(0, 0, 0);
  Token next_token = NextToken();
  if (next_token.IsPrimitive()) {
    PopToken();
    ans.push_back(next_token);
    return ans;
  }
  
  if (next_token == LEFT_BRACKET)
    return FormatArray(i_level);

  if (next_token == LEFT_BRACE) {
    PopToken();
    VerifySeparatingChars(0, 0, 0);
    ans.push_back(Token(NEW_LINE));
    for (int i = 0; i < (i_level + 1)*g_space_number; i++)
      ans.push_back(Token(SPACE));

    while (true) {

      auto token = PopToken();
      VerifySeparatingChars(0, 0, 0);
      if (token.IsString()) {
        std::cout << "ERROR! JSON String is expected" << std::endl;
        return ans;
      }
      ans.push_back(token);

      token = PopToken();
      VerifySeparatingChars(0, 0, 0);
      if (!(token == COLON)) {
        std::cout << "ERROR! Colon char is expected" << std::endl;
        return ans;
      }
      ans.push_back(token);

      Tokens object_tokens = FormatObject(i_level + 1);
      ans.insert(ans.end(), object_tokens.begin(), object_tokens.end());

      token = PopToken();
      VerifySeparatingChars(0, 0, 0);
      if (token == COMMA) {
        ans.push_back(token);
        continue;
      }
      else
        break;
    }

    auto token = PopToken();
    VerifySeparatingChars(0, 0, 0);
    if (token == RIGHT_BRACE) {
      ans.push_back(token);
      return ans;
    }

    // error
    return ans;
  }

}

Tokens JSONFormatter::FormatArray(int i_level)
{
  return Tokens();
}

void JSONFormatter::VerifySpacesAndTabs(bool i_spaces, int i_cnt){

  int space_cnt = 0,
      tab_cnt = 0;

  while (m_cur_index < m_tokens.size()) {

    if (m_tokens[m_cur_index] == SPACE)
      space_cnt++;
    else if (m_tokens[m_cur_index] == TAB)
      tab_cnt++;
    else
      break;

    m_cur_index++;
  }

  if (!i_spaces) {
    if (space_cnt > 0)
      std::cout << "ERROR! Spaces number is not 0" << std::endl;

    if (tab_cnt != i_cnt)
      std::cout << "ERROR! TABs number is not " << i_cnt << std::endl;
  }
  else {
    if (tab_cnt > 0)
      std::cout << "ERROR! TABs number is not 0" << std::endl;

    if (space_cnt != i_cnt)
      std::cout << "ERROR! Spaces number is not " << i_cnt << std::endl;
  }
}

void JSONFormatter::VerifySeparatingChars(int i_space_cnt, int i_tab_cnt, int i_newl_cnt)
{
}

int JSONFormatter::RemoveSpaces(){
  int cnt = 0;
  while (m_cur_index < m_tokens.size() && m_tokens[m_cur_index] == SPACE) {
    m_cur_index++;
    cnt++;
  }

  return cnt;
}

int JSONFormatter::RemoveTabs()
{
  return 0;
}

Token JSONFormatter::NextToken(){
  return m_tokens[m_cur_index];
}

Token JSONFormatter::PopToken(){
  return m_tokens[m_cur_index++];
}

*/