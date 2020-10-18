#include "pch.h"
#include "Logger.h"

namespace {

  const char* _HumanReadable(const Token& i_token) {
    if (i_token == SPACE)
      return "Space";
    else if (i_token == TAB)
      return "TAB";
    else if (i_token == NEW_LINE)
      return "NewLine";

    return "";
  }

}

Logger::Logger(const char * i_log_path)
  : m_log_file(i_log_path)
{
}

Logger::~Logger() {
  m_log_file.close();
}

void Logger::SetCurFileName(const char* i_file_name) {
  m_cur_file_name = i_file_name;
}

void Logger::PrintError(int i_line_number, const std::string& i_message) const{
  m_log_file << m_cur_file_name << ": Line " << i_line_number << " - " << i_message << std::endl;
}

void Logger::PrintErrorExtraChar(const Token & i_extra_token) const{
  m_log_file << m_cur_file_name << ": Line " << i_extra_token.m_line_number 
              << " - " << "Extra " << _HumanReadable(i_extra_token) << " character." << std::endl;
}

void Logger::PrintErrorMissingChar(int i_line_number, const Token & i_missing_token) const {
  m_log_file << m_cur_file_name << ": Line " << i_line_number
             << " - " << _HumanReadable(i_missing_token) << " character is missing." << std::endl;
}

void Logger::PrintErrorWrongChar(const Token & i_actual_token, const Token & i_expected_token) const {
  m_log_file << m_cur_file_name << ": Line " << i_actual_token.m_line_number
             << " - " << _HumanReadable(i_actual_token) << " character is wrong. "
             << _HumanReadable(i_expected_token) << " is expected." << std::endl;
}
