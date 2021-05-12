#pragma once
#include <string>
namespace engine {
    class Logger {
      public:
        enum SeverityLevel {
            FatalLevel,
            ErrorLevel,
            WarningLevel,
            InfoLevel,
            DebugLevel,
            TraceLevel
        };
        static void Init(SeverityLevel);
        static void flush();
        static void Fatal(std::string);
        static void Error(std::string);
        static void Warning(std::string);
        static void Info(std::string);
        static void Debug(std::string);
        static void Trace(std::string);

    };
}