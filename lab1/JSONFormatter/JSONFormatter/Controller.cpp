#include "pch.h"
#include "Controller.h"

#include "JSONLexer.h"
#include "JSONFormatter.h"
#include "ConfigParser.h"
#include "Logger.h"

#include <iostream>
#include <fstream>
#include <filesystem>

const char* g_json_extension = ".json";

namespace fs = std::filesystem;

namespace {

  std::vector<std::string> _SplitLine(const std::string& i_line) {
    std::vector<std::string> res;
    std::string cur_word;

    for (char c : i_line)
      if (c == ' ') {
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

  std::string _GetFileContent(const std::string& i_path) {
    std::ifstream fin(i_path);
    std::string content((std::istreambuf_iterator<char>(fin)),
                         std::istreambuf_iterator<char>());
    fin.close();
    return content;
  }

  void _PrintToFile(const Tokens& i_tokens, const std::string& i_path) {
    std::ofstream fout(i_path);
    for (auto& token : i_tokens)
      fout << token.m_str;

    fout.close();
  }

  void _FormatFile(const fs::path& i_file_path, const ConfigInfo& i_config_info, Logger& i_logger) {

    try {
      fs::directory_entry(i_file_path).exists();
    }
    catch (...) {
      i_logger.PrintError("File \"" + i_file_path.string() + "\" does not exist.");
      return;
    }

    i_logger.SetCurFileName(i_file_path.string());
    std::string text = _GetFileContent(i_file_path.string());

    auto tokens = JSONLexer::Lex(text, i_logger);
    auto formatted_tokens = JSONFormatter::Format(tokens, i_config_info);

    if (tokens != formatted_tokens)
      _PrintToFile(formatted_tokens, i_file_path.string());
  }

  void _FormatDirectory(const fs::path& i_directory, const ConfigInfo& i_config_info, Logger& i_logger, bool i_recursive) {

    try {
      fs::directory_entry(i_directory).exists();
    }
    catch (...) {
      i_logger.PrintError("Directory \"" + i_directory.string() + "\" does not exist.");
      return;
    }

    for (const auto& dir_entry : fs::directory_iterator(i_directory)) {
      if (dir_entry.is_directory() && i_recursive)
        _FormatDirectory(dir_entry.path(), i_config_info, i_logger, i_recursive);

      if (dir_entry.path().extension() == g_json_extension)
        _FormatFile(dir_entry.path(), i_config_info, i_logger);
    }
      
  }

  void _VerifyFile(const fs::path& i_file_path, const ConfigInfo& i_config_info, Logger& i_logger) {

    try {
      fs::directory_entry(i_file_path).exists();
    }
    catch (...) {
      i_logger.PrintError("File \"" + i_file_path.string() + "\" does not exist.");
      return;
    }

    i_logger.SetCurFileName(i_file_path.string());
    std::string text = _GetFileContent(i_file_path.string());

    auto tokens = JSONLexer::Lex(text, i_logger);
    auto formatted_tokens = JSONFormatter::Format(tokens, i_config_info);

    JSONFormatter::Verify(tokens, i_config_info, i_logger);
  }

  void _VerifyDirectory(const fs::path& i_directory, const ConfigInfo& i_config_info, Logger& i_logger, bool i_recursive) {

    try {
      fs::directory_entry(i_directory).exists();
    }
    catch (...) {
      i_logger.PrintError("Directory \"" + i_directory.string() + "\" does not exist.");
      return;
    }

    for (const auto& dir_entry : fs::directory_iterator(i_directory)) {
      if (dir_entry.is_directory() && i_recursive)
        _VerifyDirectory(dir_entry.path(), i_config_info, i_logger, i_recursive);

      if (dir_entry.path().extension() == g_json_extension)
        _VerifyFile(dir_entry.path(), i_config_info, i_logger);
    }

  }
}

void Controller::Start(){
  while (m_proceed) {
    std::string input;
    std::getline(std::cin, input);

    auto args = _SplitLine(input);

    ParseCommand(args);
  }
}

void Controller::PrintHelp(){

}

void Controller::PrintUnknownCommandMessage(){
  std::cout << "Unknown command. See help for the list of all available commands." << std::endl;
}

void Controller::ParseCommand(const std::vector<std::string>& i_args){

  if (i_args.empty()) {
    PrintUnknownCommandMessage();
    return;
  }

  auto arg0 = i_args[0];

  if (arg0 == "-f" || arg0 == "--format")
    ParseFormatCommand(i_args);
  else if (arg0 == "-v" || arg0 == "--verify")
    ParseVerifyCommand(i_args);
  else if (arg0 == "-e" || arg0 == "--exit")
    m_proceed = false;
  else PrintUnknownCommandMessage();
}

void Controller::ParseFormatCommand(const std::vector<std::string>& i_args){
  if (i_args.size() != 4)
    std::cout << "Wrongs arguments for the format command. See help for the list of all available arguments." << std::endl;

  std::string config = _GetFileContent(i_args[1]);
  ConfigInfo config_info = ConfigParser::Parse(config);
  
  Logger logger("./errors.log");

  if (i_args[2] == "-f")
    _FormatFile(i_args[3], config_info, logger);
  else if (i_args[2] == "-d")
    _FormatDirectory(i_args[3], config_info, logger, false);
  else if (i_args[2] == "-p")
    _FormatDirectory(i_args[3], config_info, logger, true);
  else
    std::cout << "Wrong arguments" << std::endl;
}

void Controller::ParseVerifyCommand(const std::vector<std::string>& i_args){
  if (i_args.size() != 4)
    std::cout << "Wrongs arguments for the verify command. See help for the list of all available arguments." << std::endl;

  std::string config = _GetFileContent(i_args[1]);
  ConfigInfo config_info = ConfigParser::Parse(config);

  Logger logger("./errors.log");

  if (i_args[2] == "-f")
    _VerifyFile(i_args[3], config_info, logger);
  else if (i_args[2] == "-d")
    _VerifyDirectory(i_args[3], config_info, logger, false);
  else if (i_args[2] == "-p")
    _VerifyDirectory(i_args[3], config_info, logger, true);
  else
    std::cout << "Wrong arguments" << std::endl;
}
