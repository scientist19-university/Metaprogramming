#pragma once

#include "Token.h"
#include "ConfigParser.h"
#include "Logger.h"

using namespace JSON;

class JSONFormatter
{
public:
  JSONFormatter() = default;
  ~JSONFormatter() = default;

  static void Verify(const Tokens& i_tokens, const ConfigInfo& i_config_info, const Logger& i_logger);
  static Tokens Format(const Tokens& i_tokens, const ConfigInfo& i_config_info);
};

