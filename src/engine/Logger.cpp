#include "engine/Logger.h"
#include <fstream>
#include <memory>
#include "engine/gameController.h"
struct LogData {
    std::ofstream logFile;
    engine::Logger::SeverityLevel level;
    explicit LogData(engine::Logger::SeverityLevel _level) : logFile("log.txt"), level(_level) { }
    void print(std::string&& data) {
        logFile << "[" << engine::gameController::Instance()->currentTick << "] " << data;
    }
};
std::unique_ptr<LogData> logData;
void engine::Logger::Init(engine::Logger::SeverityLevel minLevel) {
    logData = std::make_unique<LogData>(minLevel);
}
void engine::Logger::Fatal(std::string toLog) {
    if (logData->level < engine::Logger::SeverityLevel::FatalLevel) return;
    logData->logFile << "[Fatal]";
    logData->print(std::move(toLog));
}
void engine::Logger::Error(std::string toLog) {
    if (logData->level < engine::Logger::SeverityLevel::ErrorLevel) return;
    logData->logFile << "[Error]";
    logData->print(std::move(toLog));
}
void engine::Logger::Warning(std::string toLog) {
    if (logData->level < engine::Logger::SeverityLevel::WarningLevel) return;
    logData->logFile << "[Warning]";
    logData->print(std::move(toLog));
}
void engine::Logger::Info(std::string toLog) {
    if (logData->level < engine::Logger::SeverityLevel::InfoLevel) return;
    logData->logFile << "[Info]";
    logData->print(std::move(toLog));
}
void engine::Logger::Debug(std::string toLog) {
    if (logData->level < engine::Logger::SeverityLevel::DebugLevel) return;
    logData->logFile << "[Debug]";
    logData->print(std::move(toLog));
}
void engine::Logger::Trace(std::string toLog) {
    if (logData->level < engine::Logger::SeverityLevel::TraceLevel) return;
    logData->logFile << "[Trace]";
    logData->print(std::move(toLog));
}