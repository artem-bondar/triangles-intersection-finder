#include "text.h"

bool checkElementInArray(int element, const int* array, int arraySize) {
	for (int i = 0; i < arraySize; i++)
		if (element == array[i])
			return true;
	return false;
}

double to_double(char number, bool inverse) {
	if (inverse) return ZERO - number;
	else		 return number - ZERO;
}

double roundToFive(double number) {
	return round(number * pow(10, 5))*pow(10, -5);
}

double roundToTwo(double number) {
	return round(number * pow(10, 2))*pow(10, -2);
}

string operator*(string words, int number) {
	string output;
	if (number) {
		for (int i = 0; i < number; i++)
			output += words;
		return output;
	}
	else return "";
}