#include "Logging.h"

Logging::Logging(const std::string& filename) :
	logFile(filename, std::ios::app)
{
	if (!logFile.is_open())
		std::cerr << "Unable to open log file: " << filename << std::endl;
}

void Logging::Log(LoggingLevel level, const std::string& functionName, const std::string& message)
{
	if (!logFile.is_open())
		return;

	std::string levelStr;

	switch (level)
	{
	case LoggingLevel::info:
		levelStr = "[Info]";
		break;
	case LoggingLevel::debug:
		levelStr = "[Debug]";
		break;
	case LoggingLevel::warning:
		levelStr = "[Warning]";
		break;
	case LoggingLevel::error:
		levelStr = "[Error]";
		break;
	case LoggingLevel::critical:
		levelStr = "[Critical]";
		break;
	}

	logFile << levelStr <<" Function: " << functionName << " " << message << std::endl;
	logFile.flush();
}