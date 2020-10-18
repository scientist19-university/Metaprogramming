#include "pch.h"

#include "Controller.h"

int main(int argc, char* argv[]){

  std::vector<std::string> arg;
  for (int i = 1; i < argc; i++)
    arg.push_back(argv[i]);

  Controller::HandleCommand(arg);
}

