#include "number_to_string.h"

string numberToString(int num) {
	stringstream ssToStr;
	ssToStr << num;
	return ssToStr.str();
}