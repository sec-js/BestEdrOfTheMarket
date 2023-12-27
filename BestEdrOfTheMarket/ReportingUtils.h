#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <iostream>
#include <sstream>

std::string GetProcessPathByPID(DWORD pid, HANDLE& hProc) {
    char processPath[MAX_PATH];
    if (GetModuleFileNameExA(hProc, NULL, processPath, MAX_PATH) == 0) {
        return "";
    }
    return processPath;
}

std::string createReportingJson(
    DWORD pid,
    const std::string& processName,
    const std::string& defenseMechanism,
    const std::string& address,
    const std::string& detectedPattern,
    const std::string& patternList,
    const std::string& foundIn) {
    std::stringstream json;

    json << "{\n"
        << "  \"Version\" : \"" << "Best EDR Of The Market 1.1.0" << "\",\n"
        << "  \"MaliciousPID\" : \"" << std::to_string(pid) << "\",\n"
        << "  \"ProcessPath\" : \"" << processName << "\",\n"
        << "  \"DefenseMechanism\" : \"" << defenseMechanism << "\",\n"
        << "  \"DateTime\" : \"" << std::string(__DATE__) + " " + std::string(__TIME__) << "\",\n"
        << "  \"Address\" : \"" << address << "\",\n"
        << "  \"DetectedPattern\" : \"" << detectedPattern << "\",\n"
        << "  \"PatternList\" : \"" << patternList << "\",\n"
        << "  \"FoundIn\" : \"" << foundIn << "\"\n"
        << "}";

    return json.str();
}
