#pragma once

#include <string>

// default parameters
struct ConfigInfo {
  bool m_use_tabs = false;
  int m_spaces_in_tab = 4;
  int m_spaces_per_level = 2;
  int m_tabs_per_level = 1;
};

class ConfigParser{

public:
  ConfigParser() = default;
  ~ConfigParser() = default;

  static ConfigInfo Parse(const std::string& i_string);
};

