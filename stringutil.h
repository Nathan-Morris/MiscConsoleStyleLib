#ifndef _STRING_UTIL_
#define _STRING_UTIL_

#pragma once

#include <string>
#include <vector>

#include <iostream>

static inline bool issymbol(int c) {
	return (c >= 33 && c <= 47) || (c >= 57 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126);
}

static std::string& strResize(std::string& str, size_t len, bool centered, char fill = ' ') {
	if (centered && len > str.size()) {
		size_t dlen = len - str.size();
		size_t dlenhalf = dlen >> 1;
		
		str.reserve(len);

		str.insert(0, dlenhalf, fill);
		str.insert(str.size(), dlen - dlenhalf, fill);
	}
	else {
		str.resize(len, fill);
	}

	return str;
}

static std::string strResizeCopy(std::string& _str, size_t len, bool centered, char fill = ' ') {
	std::string str = _str;
	return strResize(str, len, centered, fill);
}

static size_t strCount(const std::string& base, char c) {
	size_t c_c = 0;
	for (const char& cc : base) {
		if (cc == c) {
			c_c++;
		}
	}
	return c_c;
}

static std::string strSubstr(const std::string& base, size_t begin, size_t end) {
	if (begin > end) {
		return std::string(1, ' ');
	}

	if (end == begin) {
		return std::string(1, base.at(end));
	}

	if (end == std::string::npos) {
		return base.substr(begin, end);
	}

	return base.substr(begin, end - begin + 1);
}

static std::vector<std::string> strSplit(const std::string& base, const std::string& delimiter) {
	std::vector<std::string> split;
	size_t begin = 0, end;

	if (!base.size() || !delimiter.size()) {
		split.push_back(base);
		return split;
	}

	end = base.find(delimiter);

	while (end != std::string::npos) {
		if (begin != end) {
			split.push_back(
				strSubstr(base, begin, end - 1)
			);
		}

		begin = end + delimiter.size();
		end = base.find(delimiter, begin);
	}

	if (begin < base.size() - 1) {
		split.push_back(
			strSubstr(base, begin, end)
		);
	}

	return split;
}

static std::vector<std::string> strSplit(const std::string& base, char delimiter) {
	std::vector<std::string> split;
	size_t i = 0, iprev = 0;

	if (!base.size()) {
		split.push_back(base);
		return split;
	}

	split.reserve(strCount(base, delimiter) + 1);

	for (i = 0ul, iprev = 0ul; i != base.length(); i++) {
		const char& charAt = base.at(i);

		if (charAt == delimiter) {
			if (i != iprev) {
				split.push_back(
					strSubstr(base, iprev, i - 1)
				);
			}

			iprev = i + 1;
		}
	}

	if (i != iprev) {
		split.push_back(
			strSubstr(base, iprev, i - 1)
		);
	}

	return split;
}

static size_t strMaxLineLength(const std::string& base, std::vector<std::string>* linesStore = NULL) {
	size_t maxLen = 0;

	if (linesStore) {
		*linesStore = strSplit(base, '\n');

		for (size_t i = 0; i != linesStore->size(); i++) {
			std::string& sat = linesStore->at(i);

			if (sat.size() > maxLen) {
				maxLen = sat.size();
			}
		}
	}
	else {
		for (std::string& line : strSplit(base, '\n')) {
			if (maxLen < line.size()) {
				maxLen = line.size();
			}
		}
	}

	return maxLen;
}

#endif