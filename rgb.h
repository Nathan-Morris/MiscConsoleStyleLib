#ifndef _RGB_
#define _RGB_

#pragma once

#include <vector>
#include <iostream>

typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} RGBval, *pRGBval;

static RGBval rgbFromInt(const unsigned int& i) {
	unsigned char* uc_ptr = (unsigned char*)&i;
	RGBval rgbval;

	rgbval.r = uc_ptr[2];
	rgbval.g = uc_ptr[1];
	rgbval.b = uc_ptr[0];

	return rgbval;
}

static unsigned int rgbToInt(const RGBval& rgbval) {
	unsigned int i = 0;
	unsigned char* uc_ptr = (unsigned char*)&i;

	uc_ptr[0] = rgbval.b;
	uc_ptr[1] = rgbval.g;
	uc_ptr[2] = rgbval.r;

	return i;
}

static std::vector<RGBval> rgbGradient(const std::vector<RGBval>& steps, size_t len) {
	std::vector<RGBval> grad;

	if (!steps.size()) {
		return grad;
	}
	else if (steps.size() == 1) {
		return std::vector<RGBval>(len, steps.at(0));
	}

	grad.reserve(len);

	if (len == 0) {
		return grad;
	}
	else if (len == 1) {
		grad.push_back(steps.at(0));
		return grad;
	}
	else if (len < steps.size()) {
		std::vector<RGBval> newSteps(len);
		newSteps.front() = steps.front();
		newSteps.back() = steps.back();
		size_t lowerStepSz = (steps.size() - 2) / (len - 2);
		for (size_t i = 1; i != len - 1; i++) {
			newSteps.at(i) = steps.at(i * lowerStepSz);
		}
		return rgbGradient(newSteps, len);
	}

	RGBval rgb1, rgb2;
	short dr, dg, db, stepsz = (short)((len - steps.size()) / (steps.size() - 1));

	for (size_t i = 0; i != (steps.size() - 1); i++) {
		rgb1 = steps.at(i);
		rgb2 = steps.at(i + 1);

		if (stepsz) {
			dr = ((short)rgb2.r - (short)rgb1.r) / stepsz;
			dg = ((short)rgb2.g - (short)rgb1.g) / stepsz;
			db = ((short)rgb2.b - (short)rgb1.b) / stepsz;
		}

		grad.push_back(rgb1);

		for (size_t stepi = 0; stepi != stepsz; stepi++) {
			rgb1.r += dr;
			rgb1.g += dg;
			rgb1.b += db;

			grad.push_back(rgb1);
		}
	}

	grad.push_back(rgb2);

	size_t i = grad.size() >> 1;
	while (grad.size() < len) {
		grad.insert(
			grad.begin() + i,
			grad.at(i)
		);
	}

	return grad;
}

#endif