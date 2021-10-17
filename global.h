#ifndef _GLOBAL_INC_
#define _GLOBAL_INC_

#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <random>
#include <vector>
#include <map>

#include "ansi.h"
#include "stringutil.h"

static inline bool __INIT__() {
	// initializes windows console ansi support
	HANDLE handleStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	if (!GetConsoleMode(handleStdout, &mode) || !SetConsoleMode(handleStdout, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
		std::cout << "Unable To Initialize Windows Console Ansi Support\n\r";
		exit(-1);
	}

	return 1;
}

extern const bool __IS_INITD__;

#endif
