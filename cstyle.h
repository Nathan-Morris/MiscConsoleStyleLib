#ifndef _CONSOLE_STYLE_
#define _CONSOLE_STYLE_

#pragma once

#include "global.h"

typedef struct {
	char topLeft;
	char topRight;
	char bottomLeft;
	char bottomRight;

	char horizontal;
	char vertical;

	char intersectAll;
	char intersectLeft;
	char intersectRight;
	char intersectTop;
	char intersectBottom;
} AsciiBoxInfo, *pAsciiBoxInfo;

typedef struct {
	COORD offsets;
	char character;
} CharOffsetInfo, *pCharOffsetInfo;

typedef std::map<short, const std::string&> AsciiRenderRules;

typedef enum : short {
	RENDER_RULE_DEFAULT = 300,
	RENDER_RULE_NUMERIC = 301,
	RENDER_RULE_ALPHABETIC = 302,
	RENDER_RULE_SYMBOLIC = 303,
	RENDER_RULE_RESET = 304
} AsciiRenderRuleCode;

static std::string makeBox(
	std::string title, 
	const std::string& content, 
	pAsciiBoxInfo boxInfo,
	bool centered = 0
) {
	// initialization
	std::stringstream ss;
	std::vector<std::string> lines;
	size_t maxLineLen = strMaxLineLength(content, &lines);

	// line size setup
	if (title.size() > maxLineLen) {
		maxLineLen = title.size();
	}
	for (std::string& lineref : lines) {
		strResize(lineref, maxLineLen, centered);
	}


	// writes top (title) line
	if (title.size()) {
		title.insert(0, 1, boxInfo->intersectLeft);
		title.insert(title.size(), 1, boxInfo->intersectRight);

		strResize(title, maxLineLen + 2, 1, boxInfo->horizontal);

		ss.put(boxInfo->topLeft);

		ss.write(title.c_str(), title.size());
	}
	else {
		ss.put(boxInfo->topLeft);

		for (size_t i = 0; i != maxLineLen + 2; i++) {
			ss.put(boxInfo->horizontal);
		}
	}
	ss.put(boxInfo->topRight);


	// writes middle (content) lines
	for (std::string& lineref : lines) {
		ss.put('\n');
		ss.put(boxInfo->vertical);
		ss.put(' ');
		ss.write(lineref.c_str(), lineref.size());
		ss.put(' ');
		ss.put(boxInfo->vertical);
	}


	// writes bottom (end) line
	ss.put('\n');
	ss.put(boxInfo->bottomLeft);
	for (size_t i = 0; i != maxLineLen + 2; i++) {
		ss.put(boxInfo->horizontal);
	}
	ss.put(boxInfo->bottomRight);

	return ss.str();
}

static std::string makeBox(
	const std::string& content,
	pAsciiBoxInfo boxInfo,
	bool centered = 0
) {
	return makeBox(std::string(""), content, boxInfo, centered);
}

static std::string makeTable(
	size_t colsC,
	size_t rowsC,
	std::vector<std::string> content,
	std::vector<std::string> titles,
	pAsciiBoxInfo boxInfo,
	bool centered = 0
) {
	std::stringstream ss;

	// size check
	if (content.size() != rowsC * colsC) {
		// error
		throw std::exception("Passed Content Size Is Not Able To Be Placed Within Table Dimensions");
	}

	// initialize pointers / info arrays
	std::string** contentXY = new std::string*[rowsC];
	size_t* maxColLens = new size_t[colsC](); // '()' -> initialized to all '0'
	size_t maxColLenSum = 0;
	for (size_t i = 0; i != rowsC; i++) {
		contentXY[i] = &content.data()[i * colsC];
		for (size_t j = 0; j != colsC; j++) {
			if (maxColLens[j] < contentXY[i][j].size()) {
				maxColLens[j] = contentXY[i][j].size();
			}
		}
	}
	for (size_t i = 0; i != titles.size(); i++) {
		if (maxColLens[i] < (size_t)titles.at(i).size()) {
			maxColLens[i] = (size_t)titles.at(i).size();
		}
	}
	for (size_t i = 0; i != colsC; i++) {
		maxColLenSum += maxColLens[i];
	}


	// initialize midline
	std::string midline((colsC + 1) + (colsC * 2) + maxColLenSum, boxInfo->horizontal);
	size_t offset = 3;
	midline.at(0) = boxInfo->intersectRight;
	for (size_t i = 0; i != colsC - 1; i++) {
		midline.at(offset + maxColLens[i]) = boxInfo->intersectAll;
		offset += maxColLens[i] + 3;
	}
	midline.at(midline.size() - 1) = boxInfo->intersectLeft;


	// writes top (title) line
	ss.put(boxInfo->topLeft);
	for (size_t i = 0; i != colsC; i++) {
		if (i) {
			ss.put(boxInfo->intersectBottom);
		}
		if (i < titles.size() && titles.at(i).size()) { // has title for column
			titles.at(i).reserve(titles.at(i).size() + 2);
			titles.at(i).insert(0, 1, boxInfo->intersectLeft);
			titles.at(i).push_back(boxInfo->intersectRight);

			strResize( titles.at(i), maxColLens[i] + 2, 1, boxInfo->horizontal);
			ss.write(titles.at(i).c_str(), titles.at(i).size());
		}
		else { // doesnt have title for column
			for (size_t j = 0; j != maxColLens[i] + 2; j++) {
				ss.put(boxInfo->horizontal);
			}
		}
	}
	ss.put(boxInfo->topRight);


	// writes middle (content) lines
	for (size_t i = 0; i != rowsC; i++) {
		if (i) {
			ss.put('\n');
			ss.write(midline.c_str(), midline.size());
		}
		ss.put('\n');
		ss.put(boxInfo->vertical);
		for (size_t j = 0; j != colsC; j++) {
			ss.put(' ');
			strResize(contentXY[i][j], maxColLens[j], centered, ' ');
			ss.write(contentXY[i][j].c_str(), contentXY[i][j].size());
			ss.put(' ');
			ss.put(boxInfo->vertical);
		}
	}


	// writes bottom (end) line
	midline.at(0) = boxInfo->bottomLeft;
	midline.at(midline.size() - 1) = boxInfo->bottomRight;
	for (size_t i = 1; i < (midline.size() - 1); i++) {
		if (midline.at(i) == boxInfo->intersectAll) {
			midline.at(i) = boxInfo->intersectTop;
		}
	}
	ss.put('\n');
	ss.write(midline.c_str(), midline.size());


	// memory deallocation / cleanup
	delete[] maxColLens;
	delete[] contentXY;


	// return (duh)
	return ss.str();
}

static std::string makeTable(
	const std::string& titleLeft, 
	const std::string& titleRight, 
	const std::vector<std::pair<std::string, std::string>>& content,
	pAsciiBoxInfo boxInfo,
	bool centered = 0
) {
	std::vector<std::string> titles = { titleLeft, titleRight };
	std::vector<std::string> contentV;
	
	contentV.reserve(content.size() << 1);

	for (const auto& pref : content) {
		contentV.push_back(pref.first);
		contentV.push_back(pref.second);
	}

	return makeTable(2, content.size(), contentV, titles, boxInfo, centered);
}

static std::string makeTable(
	const std::vector<std::pair<std::string, std::string>>& content,
	pAsciiBoxInfo boxInfo,
	bool centered = 0
) {
	return makeTable("", "", content, boxInfo, centered);
}

static std::string strRender(const std::string& msg, const AsciiRenderRules& rules) {
	std::stringstream ss;

	bool hasDefault;
	bool hasNumeric;
	bool hasAlphabetic;
	bool hasSymbolic;

	AsciiRenderRules::const_iterator findIter;

	if (!rules.size()) { // if no rules empty
		return msg;
	}

	findIter = rules.find(RENDER_RULE_RESET);

	const std::string& reset = (findIter != rules.end()) ? findIter->second : fore::reset;
	const std::string* strDefault = NULL, * strNumeric = NULL, * strAlphabetic = NULL, * strSymbolic = NULL;


	findIter = rules.find(RENDER_RULE_DEFAULT);
	if ((hasDefault = (findIter != rules.end()))) {
		strDefault = &findIter->second;
	}
	findIter = rules.find(RENDER_RULE_NUMERIC);
	if ((hasNumeric = (findIter != rules.end()))) {
		strNumeric = &findIter->second;
	}
	findIter = rules.find(RENDER_RULE_ALPHABETIC);
	if ((hasAlphabetic = (findIter != rules.end()))) {
		strAlphabetic = &findIter->second;
	}
	findIter = rules.find(RENDER_RULE_SYMBOLIC);
	if ((hasSymbolic = (findIter != rules.end()))) {
		strSymbolic = &findIter->second;
	}


	for (const char& c : msg) {
		if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\b') {
			ss.put(c);
			continue;
		}

		findIter = rules.find((short)c);

		if (findIter != rules.end()) {
			ss.write(findIter->second.c_str(), findIter->second.size());
			ss.put(c);
			ss.write(reset.c_str(), reset.size());
		}
		else if (hasNumeric && isdigit((unsigned char)c)) {
			ss.write(strNumeric->c_str(), strNumeric->size());
			ss.put(c);
			ss.write(reset.c_str(), reset.size());
		}
		else if (hasAlphabetic && isalpha((unsigned char)c)) {
			ss.write(strAlphabetic->c_str(), strAlphabetic->size());
			ss.put(c);
			ss.write(reset.c_str(), reset.size());
		}
		else if (hasSymbolic && issymbol((unsigned char)c)) {
			ss.write(strSymbolic->c_str(), strSymbolic->size());
			ss.put(c);
			ss.write(reset.c_str(), reset.size());
		}
		else if (hasDefault) {
			ss.write(strDefault->c_str(), strDefault->size());
			ss.put(c);
			ss.write(reset.c_str(), reset.size());
		}
		else {
			ss.put(c);
		}
	}

	return ss.str();
}

static std::string strRenderGradient(const std::string& msg, const AsciiRenderRules& rules, const std::vector<RGBval>& gradientSteps) {
	std::stringstream ss;

	bool hasNumeric;
	bool hasAlphabetic;
	bool hasSymbolic;

	AsciiRenderRules::const_iterator findIter;

	std::vector<std::string> lines;
	std::vector<char*> ansiRgbGradient;
	size_t maxLineLen;

	if (!gradientSteps.size() && !rules.size()) { // if no gradient steps and no rules
		return msg;
	}
	
	maxLineLen = strMaxLineLength(msg, &lines);
	ansiRgbGradient.reserve(maxLineLen);

	for (RGBval& rgbval : rgbGradient(gradientSteps, maxLineLen)) {
		ansiRgbGradient.push_back(new char[20]);
		ansiRgbCString(rgbval, ansiRgbGradient.back());
	}

	const std::string* strNumeric = NULL, * strAlphabetic = NULL, * strSymbolic = NULL;

	if (rules.size()) {
		findIter = rules.find(RENDER_RULE_NUMERIC);
		if ((hasNumeric = (findIter != rules.end()))) {
			strNumeric = &findIter->second;
		}
		findIter = rules.find(RENDER_RULE_ALPHABETIC);
		if ((hasAlphabetic = (findIter != rules.end()))) {
			strAlphabetic = &findIter->second;
		}
		findIter = rules.find(RENDER_RULE_SYMBOLIC);
		if ((hasSymbolic = (findIter != rules.end()))) {
			strSymbolic = &findIter->second;
		}
	}


	for (size_t line_i = 0; line_i != lines.size(); line_i++) {
		if (line_i) {
			ss.put('\n');
		}

		std::string& line = lines.at(line_i);

		for (size_t i = 0; i != line.size(); i++) {
			char& c = line.at(i);

			if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\b') {
				ss.put(c);
				continue;
			}

			if (rules.size()) {
				findIter = rules.find((short)c);

				if (findIter != rules.end()) {
					ss.write(findIter->second.c_str(), findIter->second.size());
					ss.put(c);
					ss.write(fore::reset.c_str(), fore::reset.size());
				}
				else if (hasNumeric && isdigit((unsigned char)c)) {
					ss.write(strNumeric->c_str(), strNumeric->size());
					ss.put(c);
					ss.write(fore::reset.c_str(), fore::reset.size());
				}
				else if (hasAlphabetic && isalpha((unsigned char)c)) {
					ss.write(strAlphabetic->c_str(), strAlphabetic->size());
					ss.put(c);
					ss.write(fore::reset.c_str(), fore::reset.size());
				}
				else if (hasSymbolic && issymbol((unsigned char)c)) {
					ss.write(strSymbolic->c_str(), strSymbolic->size());
					ss.put(c);
					ss.write(fore::reset.c_str(), fore::reset.size());
				}
				else {
					ss.write(ansiRgbGradient.at(i), 19);
					ss.put(c);
					ss.write(fore::reset.c_str(), fore::reset.size());
				}
			}
			else {
				ss.write(ansiRgbGradient.at(i), 19);
				ss.put(c);
				ss.write(fore::reset.c_str(), fore::reset.size());
			}
		}
	}

	for (char*& cptr : ansiRgbGradient) {
		delete[] cptr;
	}

	return ss.str();
}

#endif
