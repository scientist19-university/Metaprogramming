cmake_minimum_required(VERSION 3.15.2)
project(JSONFormatter)

set(CMAKE_CXX_FLAGS "/std:c++17")

add_executable(JSONFormatter
	src/main.cpp

	src/ConfigParser.cpp
	src/ConfigParser.h

	src/Controller.cpp
	src/Controller.h

	src/JSONFormatter.cpp
	src/JSONFormatter.h

	src/JSONLexer.cpp
	src/JSONLexer.h

	src/Logger.cpp
	src/Logger.h

	src/Token.h)