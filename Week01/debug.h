#pragma once
#ifndef _DEBUG_H
#define _DEBUG_H

#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

void DebugOut(const wchar_t* fmt, ...);

#endif // !_DEBUG_H