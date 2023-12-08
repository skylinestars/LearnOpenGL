#pragma once
#include <string>
#include <windows.h>
#include <algorithm>

class FileTools
{
public:
	static std::string getProgramDir()
	{
		wchar_t exeName[MAX_PATH];
        exeName[0] = 0;
        GetModuleFileNameW(nullptr, exeName, MAX_PATH);
        char buffer[MAX_PATH] = {0};
	    wcstombs(buffer,exeName,MAX_PATH);
        std::string programDir(buffer);
        std::replace(programDir.begin(), programDir.end(), '\\', '/');
        programDir = programDir.substr(0, programDir.find_last_of("/\\"));
        return programDir;
	}
};