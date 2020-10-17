#pragma once

#include "Token.h"

class Controller {

public:
  Controller() = default;
  ~Controller() = default;

  void Start();

private:
  void PrintHelp();
  void PrintUnknownCommandMessage();

  void ParseCommand(const std::vector<std::string>& i_args);
  void ParseFormatCommand(const std::vector<std::string>& i_args);
  void ParseVerifyCommand(const std::vector<std::string>& i_args);

  bool m_proceed = true;
};

