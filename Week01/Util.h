#pragma once
#ifndef _UTIL_H
#define _UTIL_H

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <string>

void DebugOut(const wchar_t* fmt, ...);
std::vector<std::string> SplitLine(std::string line, std::string delimeter = "\t");
std::wstring ToWSTR(std::string st);
LPCWSTR ToLPCWSTR(std::string st);

#endif // !_UTIL_H
