#include "pch.h"
#include "Controller.h"

#include "JSONLexer.h"
#include "JSONFormatter.h"
#include "ConfigParser.h"
#include "Logger.h"

#include <iostream>
#include <fstream>

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

  std::string text = _GetFileContent(i_args[3]);
  
  Logger logger("./errors.log");
  logger.SetCurFileName(i_args[1].c_str());

  auto tokens = JSONLexer::Lex(text, logger);
  auto formatted_tokens = JSONFormatter::Format(tokens, config_info);

  if (tokens != formatted_tokens)
    _PrintToFile(formatted_tokens, i_args[3]);
}

void Controller::ParseVerifyCommand(const std::vector<std::string>& i_args){
  if (i_args.size() != 4)
    std::cout << "Wrongs arguments for the verify command. See help for the list of all available arguments." << std::endl;

  std::string config = _GetFileContent(i_args[1]);
  ConfigInfo config_info = ConfigParser::Parse(config);

  Logger logger("./errors.log");
  logger.SetCurFileName(i_args[1].c_str());

  std::string text = _GetFileContent(i_args[3]);
  auto tokens = JSONLexer::Lex(text, logger);

  JSONFormatter::Verify(tokens, config_info, logger);
}
