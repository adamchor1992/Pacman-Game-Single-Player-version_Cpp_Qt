#pragma once

#include <QString>
#include <fstream>

class LogManager
{
public:
    static void ActivateLogging(QString fileName = "");
    static void LogToFile(std::string &&logMessage);

private:
    inline static std::string DEFAULT_LOG_FILE_NAME = "log.txt";

    static std::ofstream m_LogFile;
    static bool m_LoggingActive;
};
