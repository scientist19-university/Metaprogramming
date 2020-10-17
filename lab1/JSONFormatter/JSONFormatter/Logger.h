#pragma once

#include "Token.h"

#include <fstream>

using namespace JSON;

class Logger {

public:
  Logger(const char* i_log_path);
  ~Logger();

  void SetCurFileName(const char* i_file_name);

  void PrintError(int i_line_number, const char* i_message) const;
  void PrintErrorExtraChar(const Token& i_extra_token) const;
  void PrintErrorMissingChar(int i_line_number, const Token& i_missing_token) const;
  void PrintErrorWrongChar(const Token& i_actual_token, const Token& i_expected_token) const;

private:
  mutable std::ofstream m_log_file;
  const char* m_cur_file_name;
};

