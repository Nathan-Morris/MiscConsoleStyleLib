#include "ansi.h"

//
// Fore
//

std::string fore::rgb(const RGBval& rgbval) {
	return ansiRgbString(rgbval, 0);
}

std::string fore::rgb(unsigned int rgbval) {
	return fore::rgb(rgbFromInt(rgbval));
}

std::string fore::rgb(unsigned char r, unsigned char g, unsigned char b) {
	return fore::rgb({ r, g, b });
}

const std::string fore::reset = std::string(ANSI_RESET);

const std::string fore::black = std::string(ANSI_FORE_BLACK);
const std::string fore::red = std::string(ANSI_FORE_RED);
const std::string fore::green = std::string(ANSI_FORE_GREEN);
const std::string fore::yellow = std::string(ANSI_FORE_YELLOW);
const std::string fore::blue = std::string(ANSI_FORE_BLUE);
const std::string fore::magenta = std::string(ANSI_FORE_MAGENTA);
const std::string fore::cyan = std::string(ANSI_FORE_CYAN);
const std::string fore::white = std::string(ANSI_FORE_WHITE);

const std::string fore::blackBright = std::string(ANSI_FORE_BLACK_BRIGHT);
const std::string fore::redBright = std::string(ANSI_FORE_RED_BRIGHT);
const std::string fore::greenBright = std::string(ANSI_FORE_GREEN_BRIGHT);
const std::string fore::yellowBright = std::string(ANSI_FORE_YELLOW_BRIGHT);
const std::string fore::blueBright = std::string(ANSI_FORE_BLUE_BRIGHT);
const std::string fore::magentaBright = std::string(ANSI_FORE_MAGENTA_BRIGHT);
const std::string fore::cyanBright = std::string(ANSI_FORE_CYAN_BRIGHT);
const std::string fore::whiteBright = std::string(ANSI_FORE_WHITE_BRIGHT);



//
// Back
//

std::string back::rgb(const RGBval& rgbval) {
	return ansiRgbString(rgbval, 1);
}

std::string back::rgb(unsigned int rgbval) {
	return fore::rgb(rgbFromInt(rgbval));
}

std::string back::rgb(unsigned char r, unsigned char g, unsigned char b) {
	return fore::rgb({ r, g, b });
}

const std::string& back::reset = fore::reset;

const std::string back::black = std::string(ANSI_BACK_BLACK);
const std::string back::red = std::string(ANSI_BACK_RED);
const std::string back::green = std::string(ANSI_BACK_GREEN);
const std::string back::yellow = std::string(ANSI_BACK_YELLOW);
const std::string back::blue = std::string(ANSI_BACK_BLUE);
const std::string back::magenta = std::string(ANSI_BACK_MAGENTA);
const std::string back::cyan = std::string(ANSI_BACK_CYAN);
const std::string back::white = std::string(ANSI_BACK_WHITE);

const std::string back::blackBright = std::string(ANSI_BACK_BLACK_BRIGHT);
const std::string back::redBright = std::string(ANSI_BACK_RED_BRIGHT);
const std::string back::greenBright = std::string(ANSI_BACK_GREEN_BRIGHT);
const std::string back::yellowBright = std::string(ANSI_BACK_YELLOW_BRIGHT);
const std::string back::blueBright = std::string(ANSI_BACK_BLUE_BRIGHT);
const std::string back::magentaBright = std::string(ANSI_BACK_MAGENTA_BRIGHT);
const std::string back::cyanBright = std::string(ANSI_BACK_CYAN_BRIGHT);
const std::string back::whiteBright = std::string(ANSI_BACK_WHITE_BRIGHT);



//
// Style
//

const std::string& style::reset = fore::reset;

const std::string style::bold = std::string(ANSI_BOLD);
const std::string style::underline = std::string(ANSI_UNDERLINE);
const std::string style::invert = std::string(ANSI_INVERT);