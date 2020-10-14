#include "pch.h"
#include "ConfigParser.h"

#include <vector>

const char* g_use_tabs_keyword = "use_tabs";
const char* g_spaces_in_tab_keyword = "spaces_in_tab";
const char* g_spaces_per_level_keyword = "spaces_per_level";
const char* g_tabs_per_level_keyword = "tabs_per_level";

namespace {

  // TODO: replace this function to utils
  std::vector<std::string> _SplitLine(const std::string& i_line) {
    std::vector<std::string> res;
    std::string cur_word;

    for (char c : i_line)
      if (c == ' ' || c == '\n' || c == '\t') {
        if (!cur_word.empty())
          res.push_back(cur_word);
        cur_word = "";
      }
      else
        cur_word += c;

    if (!cur_word.empty())
      res.push_back(cur_word);

    return res;
  }

  int ParseNumber(const std::string& i_string) {
    int k = 0;
    int res = 0;
    while (k < i_string.size() && '0' <= i_string[k] && i_string[k] <= '9') {
      res += (i_string[k] - '0') * pow(10, k);
      k++;
    }

    return res;
  }

  // TODO: rewrite function with optional
  bool ParseBool(const std::string& i_string) {
    return i_string == "true";
  }

}

ConfigInfo ConfigParser::Parse(const std::string & i_string){

  ConfigInfo res;
  auto params = _SplitLine(i_string);

  for (int i = 0; i < params.size() - 1; i++) {

    // TODO: add verification for number
    if (params[i] == g_use_tabs_keyword)
      res.m_use_tabs = ParseBool(params[i + 1]);
    else if (params[i] == g_spaces_in_tab_keyword)
      res.m_spaces_in_tab = ParseNumber(params[i + 1]);
    else if (params[i] == g_tabs_per_level_keyword)
      res.m_tabs_per_level = ParseNumber(params[i + 1]);
    else if (params[i] == g_spaces_per_level_keyword)
      res.m_spaces_per_level = ParseNumber(params[i + 1]);

  }

  return res;
}
