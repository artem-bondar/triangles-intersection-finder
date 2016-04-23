#ifndef  INPUT_H
#define  INPUT_H

#include "dot.h"
#include "triangle.h"
#include "interface.h"

class Input {
public:

	Input();

	void
		getDots();
	const bool
		checkValidity(char keyValue) const;

	friend void
		Interface::showFractionalPart(const char keyValue, int* zeroCounter, int* digitsCounter, int &currentZeroCounter, int &currentDigitsCounter, const int &fractionalPart) const,
		Interface::showInput(const char keyValue) const,
		Interface::operateWithInputtedDots() const;

private:

	void
		setAllNull(),
		setCountersNull(int* zeroCounter, int* digitsCounter, int &currentZeroCounter, int &currentDigitsCounter),
		executeBackspace(const int &dots, const int coord, char &keyValue, bool &dotFlag, int &fractionalPart, int &integerPart,
						 int* zeroCounter, int* digitsCounter, int &currentZeroCounter, int &currentDigitsCounter, bool &minusFlag),
		executeNumber(const int &dots, const int coord, const char keyValue, const bool &dotFlag, int &integerPart, int &fractionalPart, const bool &minusFlag),
		modifyNumber(char &keyValue);
	const bool
		checkChar(char character) const;

	bool
		commaFlag, xDotFlag, xMinusFlag,
				   yDotFlag, yMinusFlag;
	int 
		dots, xZeroCounter[3], xCurrentZeroCounter, xDigitsCounter[3], xCurrentDigitsCounter, xIntegerPart, xFractionalPart,
			  yZeroCounter[3], yCurrentZeroCounter, yDigitsCounter[3], yCurrentDigitsCounter, yIntegerPart, yFractionalPart;
	Dot array[6];

};

extern Input input;

#endif