#pragma once

#include <string>

// default parameters
struct ConfigInfo {
  bool m_use_tabs = false;
  bool m_space_after_comma = false;
  bool m_space_before_comma = false;
  bool m_space_after_colon = true;
  bool m_space_before_colon = false;
  bool m_keep_indents_on_empty_lines = false;
  int m_indent_size = 4;
  int m_max_blank_lines_number = 1;
};

class ConfigParser{

public:
  ConfigParser() = default;
  ~ConfigParser() = default;

  static ConfigInfo Parse(const std::string& i_string);
};

