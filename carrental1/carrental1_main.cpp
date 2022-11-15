#include <fstream>
#include <common_log.h>
#include <common_argument_parser.h>
#include <carrental1_dynamic_program.h>
#include <carrental1_utils.h>

using namespace carrental1;
using namespace common;

void parseArguments(std::string& paramFile,
                    std::string& valueFile,
                    std::string& policyFile,
                    std::string& logFile,
                    std::string& logLevelStr,
                    int argc,
                    char* argv[])
{
    ArgumentParser parser;

    parser.init({
        Argument::create(paramFile, "paramFile", "p", "paramFile",
                         "Path to param file", true, k_nonEmptyStrV),
        Argument::create(valueFile, "valueFile", "", "valueFile",
                         "Path to value file", true, k_nonEmptyStrV),
        Argument::create(policyFile, "policyFile", "", "policyFile",
                         "Path to policy file", true, k_nonEmptyStrV),
        Argument::create(logFile, "logFile", "l", "logFile",
                         "Path to log file", true, k_nonEmptyStrV),
        Argument::create(logLevelStr, "logLevel", "v", "logLevel",
                         "Log level", true, k_nonEmptyStrV)
    });

    parser.parse(argc, argv);
}

void initLog(const std::string& logLevelStr,
             const std::string& logFile)
{
    static std::ofstream os;

    os.open(logFile);

    if (!os.good())
    {
        THROW_EXCEPT(FileException, "Failed to open file " + logFile);
    }

    Logger::LogLevel level = Logger::LEVEL_DEBUG;

    if (!logLevelStr.empty())
    {
        level = Logger::strToLevel(logLevelStr);
    }

    Logger::initInstance(os, level);
}

int main(int argc, char* argv[])
{
    std::string paramFile, valueFile, policyFile, logFile, logLevelStr;

    parseArguments(paramFile, valueFile, policyFile,
                   logFile, logLevelStr, argc, argv);
    initLog(logLevelStr, logFile);

    Params params(paramFile);
    DynamicProgram program(params);

    program.run();

    writeTable(valueFile, program.values());
    writeTable(policyFile, program.policy());
}
