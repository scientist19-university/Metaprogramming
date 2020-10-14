#pragma once

#include "Token.h"

using namespace JSON;

class JSONFormatter
{
public:
  JSONFormatter() = default;
  ~JSONFormatter() = default;

  static void Verify(Tokens& i_tokens);
  static Tokens Format(Tokens& i_tokens);

private:
  /*
  void VerifyObject(int i_level, bool i_new_line);
  void VerifyArray(int i_level, bool i_new_line);

  Tokens FormatObject(int i_level);
  Tokens FormatArray(int i_level);

  void VerifySpacesAndTabs(bool i_spaces, int i_cnt);
  void VerifySeparatingChars(int i_space_cnt, int i_tab_cnt, int i_newl_cnt);

  int RemoveSpaces();
  int RemoveTabs();

  Token NextToken();
  Token PopToken();

  Tokens m_tokens;
  int m_cur_index;
  */
};

