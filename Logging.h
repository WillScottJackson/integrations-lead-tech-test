#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

class Logging
{
public: 

	enum class LoggingLevel
	{
		info, 
		debug,
		warning,
		error,
		critical,
	};

	Logging(const std::string& filename);

	void Log(LoggingLevel level, const std::string &functionName, const std::string& message);

private: 
	std::ofstream logFile;
};

