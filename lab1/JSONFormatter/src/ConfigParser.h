#pragma once

#include <string>

// default parameters
struct ConfigInfo {
  bool m_use_tabs = false;
  int m_indent_size = 4;

  int m_max_blank_lines_number = 1;
  bool m_keep_indents_on_empty_lines = false;

  bool m_space_after_comma = false;
  bool m_space_before_comma = false;

  bool m_space_after_colon = true;
  bool m_space_before_colon = false;

  bool m_wrap_arrays = true;
  bool m_wrap_objects = true;

  bool m_space_within_braces = true;
  bool m_space_within_brackets = true;
};

class ConfigParser{

public:
  ConfigParser() = default;
  ~ConfigParser() = default;

  static ConfigInfo Parse(const std::string& i_string);
};

