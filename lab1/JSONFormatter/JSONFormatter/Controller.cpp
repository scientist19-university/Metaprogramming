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
      std::cout << "File \"" + i_file_path.string() + "\" does not exist." << std::endl;
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
      std::cout << "Directory \"" + i_directory.string() + "\" does not exist." << std::endl;
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
      std::cout << "File \"" + i_file_path.string() + "\" does not exist." << std::endl;
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
      std::cout << "Directory \"" + i_directory.string() + "\" does not exist." << std::endl;
      return;
    }

    for (const auto& dir_entry : fs::directory_iterator(i_directory)) {
      if (dir_entry.is_directory() && i_recursive)
        _VerifyDirectory(dir_entry.path(), i_config_info, i_logger, i_recursive);

      if (dir_entry.path().extension() == g_json_extension)
        _VerifyFile(dir_entry.path(), i_config_info, i_logger);
    }

  }

  ConfigInfo _GetConfigFromFile(const fs::path& i_config_path) {
    try {
      fs::directory_entry(i_config_path).exists();
    }
    catch (...) {
      std::cout << "Config file \"" + i_config_path.string() + "\" does not exist." << std::endl;
      return ConfigInfo();
    }

    std::string config = _GetFileContent(i_config_path.string());
    ConfigInfo config_info = ConfigParser::Parse(config);

    return config_info;
  }
}


void Controller::PrintHelp(){
  std::cout << "Available commands:\n\n"
            << "--format <path to config> -(f | d | p) <path to file to format>\n"
            << "-f <path to config> -(f | d | p) <path to file to format>\n\n"
            << "--verify <path to config> -(f | d | p) <path to file to verify>\n"
            << "-v <path to config> -(f | d | p) <path to file to verify>\n\n"
            << "--help\n"
            << "-h\n\n";
}

void Controller::PrintUnknownCommandMessage(const std::string& i_command){
  std::cout << "Unknown command " << i_command << ". See help for the list of all available commands." << std::endl;
}

void Controller::HandleCommand(const std::vector<std::string>& i_args){

  if (i_args.empty()) {
    PrintUnknownCommandMessage("");
    return;
  }

  auto arg0 = i_args[0];

  if (arg0 == "-f" || arg0 == "--format")
    HandleFormatCommand(i_args);
  else if (arg0 == "-v" || arg0 == "--verify")
    HandleVerifyCommand(i_args);
  else if (arg0 == "-h" || arg0 == "--help")
    PrintHelp();
  else PrintUnknownCommandMessage(arg0);
}

void Controller::HandleFormatCommand(const std::vector<std::string>& i_args){
  if (i_args.size() != 4)
    std::cout << "Wrongs arguments for the format command. See help for the list of all available arguments." << std::endl;

  const ConfigInfo config_info = _GetConfigFromFile(i_args[1]);
  
  Logger logger("./errors.log");

  if (i_args[2] == "-f")
    _FormatFile(i_args[3], config_info, logger);
  else if (i_args[2] == "-d")
    _FormatDirectory(i_args[3], config_info, logger, false);
  else if (i_args[2] == "-p")
    _FormatDirectory(i_args[3], config_info, logger, true);
  else
    std::cout << "Wrong argument " << i_args[2] << std::endl;
}

void Controller::HandleVerifyCommand(const std::vector<std::string>& i_args){
  if (i_args.size() != 4)
    std::cout << "Wrongs arguments for the verify command. See help for the list of all available arguments." << std::endl;

  const ConfigInfo config_info = _GetConfigFromFile(i_args[1]);

  Logger logger("./errors.log");

  if (i_args[2] == "-f")
    _VerifyFile(i_args[3], config_info, logger);
  else if (i_args[2] == "-d")
    _VerifyDirectory(i_args[3], config_info, logger, false);
  else if (i_args[2] == "-p")
    _VerifyDirectory(i_args[3], config_info, logger, true);
  else
    std::cout << "Wrong argument " << i_args[2] << std::endl;
}
