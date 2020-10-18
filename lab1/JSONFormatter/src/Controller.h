#pragma once

#include "Token.h"

class Controller {

public:
  Controller() = default;
  ~Controller() = default;

  static void HandleCommand(const std::vector<std::string>& i_args);

private:
  static void PrintHelp();
  static void PrintUnknownCommandMessage(const std::string& i_command);

  static void HandleFormatCommand(const std::vector<std::string>& i_args);
  static void HandleVerifyCommand(const std::vector<std::string>& i_args);
};

