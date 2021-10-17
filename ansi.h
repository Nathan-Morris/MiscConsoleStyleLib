#ifndef _ANSI_DEF_
#define _ANSI_DEF_

#ifndef TO_DIGIT
#define TO_DIGIT(_C_) ((_C_) + 48)
#endif

#define ANSI_RESET		"\u001b[0m"
#define ANSI_BOLD		"\u001b[1m"
#define ANSI_UNDERLINE	"\u001b[4m"
#define ANSI_INVERT		"\u001b[7m"

#define ANSI_FORE_BLACK		"\u001b[30m"
#define ANSI_FORE_RED		"\u001b[31m"
#define ANSI_FORE_GREEN		"\u001b[32m"
#define ANSI_FORE_YELLOW	"\u001b[33m"
#define ANSI_FORE_BLUE		"\u001b[34m"
#define ANSI_FORE_MAGENTA	"\u001b[35m"
#define ANSI_FORE_CYAN		"\u001b[36m"
#define ANSI_FORE_WHITE		"\u001b[37m"

#define ANSI_BACK_BLACK		"\u001b[40m"
#define ANSI_BACK_RED		"\u001b[41m"
#define ANSI_BACK_GREEN		"\u001b[42m"
#define ANSI_BACK_YELLOW	"\u001b[43m"
#define ANSI_BACK_BLUE		"\u001b[44m"
#define ANSI_BACK_MAGENTA	"\u001b[45m"
#define ANSI_BACK_CYAN		"\u001b[46m"
#define ANSI_BACK_WHITE		"\u001b[47m"

#define ANSI_FORE_BLACK_BRIGHT		"\u001b[30;1m"
#define ANSI_FORE_RED_BRIGHT		"\u001b[31;1m"
#define ANSI_FORE_GREEN_BRIGHT		"\u001b[32;1m"
#define ANSI_FORE_YELLOW_BRIGHT		"\u001b[33;1m"
#define ANSI_FORE_BLUE_BRIGHT		"\u001b[34;1m"
#define ANSI_FORE_MAGENTA_BRIGHT	"\u001b[35;1m"
#define ANSI_FORE_CYAN_BRIGHT		"\u001b[36;1m"
#define ANSI_FORE_WHITE_BRIGHT		"\u001b[37;1m"

#define ANSI_BACK_BLACK_BRIGHT		"\u001b[40;1m"
#define ANSI_BACK_RED_BRIGHT		"\u001b[41;1m"
#define ANSI_BACK_GREEN_BRIGHT		"\u001b[42;1m"
#define ANSI_BACK_YELLOW_BRIGHT		"\u001b[43;1m"
#define ANSI_BACK_BLUE_BRIGHT		"\u001b[44;1m"
#define ANSI_BACK_MAGENTA_BRIGHT	"\u001b[45;1m"
#define ANSI_BACK_CYAN_BRIGHT		"\u001b[46;1m"
#define ANSI_BACK_WHITE_BRIGHT		"\u001b[47;1m"

#pragma once

#include <string>

#include "rgb.h"

static std::string ansiRgbString(const RGBval& rgbval, bool back = 0) {
	std::string ansirgb("\u001b[38;2;000;000;000m");

	if (back) {
		ansirgb[2] = '4';
	}

	ansirgb[7] = TO_DIGIT(rgbval.r / 100);
	ansirgb[8] = TO_DIGIT((rgbval.r % 100) / 10);
	ansirgb[9] = TO_DIGIT(rgbval.r % 10);

	ansirgb[11] = TO_DIGIT(rgbval.g / 100);
	ansirgb[12] = TO_DIGIT((rgbval.g % 100) / 10);
	ansirgb[13] = TO_DIGIT(rgbval.g % 10);

	ansirgb[15] = TO_DIGIT(rgbval.b / 100);
	ansirgb[16] = TO_DIGIT((rgbval.b % 100) / 10);
	ansirgb[17] = TO_DIGIT(rgbval.b % 10);

	return ansirgb;
}

// 'buffer' must be at least 20 bytes long
static char* ansiRgbCString(const RGBval& rgbval, char* buffer, bool back = 0) {
	buffer[0] = '\u001b';
	buffer[1] = '[';
	buffer[2] =	back ? '4' : '3';
	buffer[3] = '8';
	buffer[4] = ';';
	buffer[5] = '2';
	buffer[6] = ';';
	buffer[7] = TO_DIGIT(rgbval.r / 100);
	buffer[8] = TO_DIGIT((rgbval.r % 100) / 10);
	buffer[9] = TO_DIGIT(rgbval.r % 10);
	buffer[10] = ';';
	buffer[11] = TO_DIGIT(rgbval.g / 100);
	buffer[12] = TO_DIGIT((rgbval.g % 100) / 10);
	buffer[13] = TO_DIGIT(rgbval.g % 10);
	buffer[14] = ';';
	buffer[15] = TO_DIGIT(rgbval.b / 100);
	buffer[16] = TO_DIGIT((rgbval.b % 100) / 10);
	buffer[17] = TO_DIGIT(rgbval.b % 10);
	buffer[18] = 'm';
	buffer[19] = '\0';
	return buffer;
}

class fore {
public:
	static std::string rgb(const RGBval& rgbval);
	static std::string rgb(unsigned int rgbval);
	static std::string rgb(unsigned char r, unsigned char g, unsigned char b);

public:
	const static std::string reset;

	const static std::string black;
	const static std::string red;
	const static std::string green;
	const static std::string yellow;
	const static std::string blue;
	const static std::string magenta;
	const static std::string cyan;
	const static std::string white;

	const static std::string blackBright;
	const static std::string redBright;
	const static std::string greenBright;
	const static std::string yellowBright;
	const static std::string blueBright;
	const static std::string magentaBright;
	const static std::string cyanBright;
	const static std::string whiteBright;
};

class back {
public:
	static std::string rgb(const RGBval& rgbval);
	static std::string rgb(unsigned int rgbval);
	static std::string rgb(unsigned char r, unsigned char g, unsigned char b);

public:
	const static std::string& reset;

	const static std::string black;
	const static std::string red;
	const static std::string green;
	const static std::string yellow;
	const static std::string blue;
	const static std::string magenta;
	const static std::string cyan;
	const static std::string white;

	const static std::string blackBright;
	const static std::string redBright;
	const static std::string greenBright;
	const static std::string yellowBright;
	const static std::string blueBright;
	const static std::string magentaBright;
	const static std::string cyanBright;
	const static std::string whiteBright;
};

class style {
public:
	const static std::string& reset;

	const static std::string bold;
	const static std::string underline;
	const static std::string invert;
};

#endif