#include "pch.h"
#include "ConfigParser.h"

#include <vector>

const char* g_use_tabs_keyword = "use_tabs";
const char* g_indent_size_keyword = "indent_size";
const char* g_max_blank_lines_number = "max_blank_lines";
const char* g_space_after_comma_keyword = "space_after_comma";
const char* g_space_after_colon_keyword = "space_after_colon";
const char* g_keep_indents_on_empty_lines = "keep_indents_on_empty_lines";

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
    while (k < (int)i_string.size() && '0' <= i_string[k] && i_string[k] <= '9') {
      res += (i_string[k] - '0') * (int)pow(10, k);
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

  for (int i = 0; i < int(params.size()) - 1; i++) {

    // TODO: add verification for number
    if (params[i] == g_use_tabs_keyword)
      res.m_use_tabs = ParseBool(params[i + 1]);
    else if (params[i] == g_indent_size_keyword)
      res.m_indent_size = ParseNumber(params[i + 1]);
    else if (params[i] == g_max_blank_lines_number)
      res.m_max_blank_lines_number = ParseNumber(params[i + 1]);
    else if (params[i] == g_space_after_comma_keyword)
      res.m_space_after_comma = ParseBool(params[i + 1]);
    else if (params[i] == g_space_after_colon_keyword)
      res.m_space_after_colon = ParseBool(params[i + 1]);
    else if (params[i] == g_keep_indents_on_empty_lines)
      res.m_keep_indents_on_empty_lines = ParseBool(params[i + 1]);

  }

  return res;
}
