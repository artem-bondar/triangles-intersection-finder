#include <conio.h>
#include <math.h>

#include "input.h"
#include "enum.h"
#include "implements.h"

Input::Input() {
	dots = 0;
	setAllNull();
}

void Input::setCountersNull(int* zeroCounter, int* digitsCounter, int &currentZeroCounter, int &currentDigitsCounter) {
	for (int i = 0; i < 3; i++) {
		zeroCounter[i] = 0;
		digitsCounter[i] = 0;
	}
	currentZeroCounter = 0;
	currentDigitsCounter = 0;
}

void Input::setAllNull() {
	xIntegerPart = xFractionalPart = yIntegerPart = yFractionalPart = 0;
	xMinusFlag = yMinusFlag = xDotFlag = yDotFlag = commaFlag = false;
	setCountersNull(xZeroCounter, xDigitsCounter, xCurrentZeroCounter, xCurrentDigitsCounter);
	setCountersNull(yZeroCounter, yDigitsCounter, yCurrentZeroCounter, yCurrentDigitsCounter);
}

const bool Input::checkChar(char character) const {
	return isdigit(character) || checkElementInArray(character, text.keys, sizeof(text.keys));
}

const bool Input::checkValidity(char keyValue) const {
	switch (keyValue) {
	case ENTER:
	{
		if (!yIntegerPart)
			return false;
		break;
	}
	case SPACE:
	case COMMA:
	{
		if (commaFlag || !xIntegerPart)
			return false;
		break;
	}
	case DOT:
	{
			if ((xDotFlag && !commaFlag) ||
				(yDotFlag && commaFlag))
					return false;
		break;
	}
	case BACKSPACE: 
	{
		if (!xIntegerPart && !xMinusFlag) return false;
		break;
	}
	case HELP:
	{
		break;
	}
	case ZERO:
	{
		if ((xIntegerPart == 1 && !array[dots].getCoordinates(x) && !commaFlag && !xDotFlag) ||
			(yIntegerPart == 1 && !array[dots].getCoordinates(y) && commaFlag && !yDotFlag))
			return false;
	}
	default:
	{
		if (keyValue != MINUS && ((((xIntegerPart == MAX_INTEGER_DIGITS_LIMIT && !xDotFlag) ||
									(xFractionalPart == MAX_FRACTIONAL_DIGITS_LIMIT && xDotFlag))  && !commaFlag) ||
								  (((yIntegerPart == MAX_INTEGER_DIGITS_LIMIT && !yDotFlag) ||
									(yFractionalPart == MAX_FRACTIONAL_DIGITS_LIMIT && yDotFlag)) && commaFlag)))
			return false;
		break;
	}
	}
	return true;
}

void Input::executeBackspace(const int &i, const int coord, char &keyValue, bool &dotFlag, int &fractionalPart, int &integerPart,
							 int* zeroCounter, int* digitsCounter, int &currentZeroCounter, int &currentDigitsCounter, bool &minusFlag) {
	if (dotFlag)
	{
		double extraFractionalValue = (long long int(array[i].getCoordinates(coord) * pow(10, fractionalPart)) % 10) * pow(10, -fractionalPart);
		if (fractionalPart)
		{
			array[i].setCoordinates(coord, roundToFive(array[i].getCoordinates(coord) - extraFractionalValue));
			fractionalPart--;
		}
		else
		{
			dotFlag = false;
			setCountersNull(zeroCounter, digitsCounter, currentZeroCounter, currentDigitsCounter);
		}
		if (!array[i].getCoordinates(coord) && minusFlag && extraFractionalValue)
			array[i].setCoordinates(coord, -array[i].getCoordinates(coord));
	}
	else
		if (integerPart)
		{
			array[i].setCoordinates(coord, int(array[i].getCoordinates(coord) / 10));
			integerPart--;
		}
		else
		{
			if (minusFlag)
			{
				minusFlag = false;
				array[i].setCoordinates(coord, 0);
			}
			else
			{
				if (coord == y) {
					commaFlag = false;
					keyValue = COMMA;
				}
			}
		}
}

void Input::executeNumber(const int &i, const int coord, const char keyValue, const bool &dotFlag, int &integerPart, int &fractionalPart, const bool &minusFlag) {
	if (!dotFlag)
	{
		integerPart += !(integerPart == 1 && !array[i].getCoordinates(coord));
		array[i].setCoordinates(coord, roundToFive(array[i].getCoordinates(coord) * 10 + to_double(keyValue, minusFlag)));
	}
	else
	{
		fractionalPart++;
		array[i].setCoordinates(coord, roundToFive(array[i].getCoordinates(coord) + to_double(keyValue, minusFlag) * pow(10, -fractionalPart)));
	}
	if (!array[i].getCoordinates(coord) && minusFlag)
		array[i].setCoordinates(coord, -array[i].getCoordinates(coord));
}

void Input::modifyNumber(char &keyValue) {
	switch (keyValue) {
	case ENTER:
	{
		if (!array[dots].getCoordinates(x))
			array[dots].setCoordinates(x, 0);
		if (!array[dots].getCoordinates(y))
			array[dots].setCoordinates(y, 0);
		break;
	}
	case MINUS:
	{
		if (!commaFlag)
		{
			array[dots].setCoordinates(x, -array[dots].getCoordinates(x));
			if (xMinusFlag) xMinusFlag = false;
			else
				xMinusFlag = true;
		}
		else
		{
			array[dots].setCoordinates(y, -array[dots].getCoordinates(y));
			if (yMinusFlag) yMinusFlag = false;
			else
				yMinusFlag = true;
		}
		break;
	}
	case SPACE:
	case COMMA:
	{
		commaFlag = true;
		break;
	}
	case DOT:
	{
		if (!commaFlag)
		{
			xDotFlag = true;
			if (!xIntegerPart)
			{
				array[dots].setCoordinates(x, 0);
				xIntegerPart++;
			}
		}
		else
		{
			yDotFlag = true;
			if (!yIntegerPart)
			{
				yDotFlag = true;
				array[dots].setCoordinates(y, 0);
				yIntegerPart++;
			}
		}
		break;
	}
	case BACKSPACE:
	{
		if (!commaFlag)
		{
			executeBackspace(dots, x, keyValue, xDotFlag, xFractionalPart, xIntegerPart,
							 xZeroCounter, xDigitsCounter, xCurrentZeroCounter, xCurrentDigitsCounter, xMinusFlag);
		}
		else
		{
			executeBackspace(dots, y, keyValue, yDotFlag, yFractionalPart, yIntegerPart,
							 yZeroCounter, yDigitsCounter, yCurrentZeroCounter, yCurrentDigitsCounter, yMinusFlag);
		}
		break;
	}
	case HELP:
	{
		UI.refreshCommandZone(true);
		break;
	}
	default:
	{
		if (!commaFlag)
		{
			executeNumber(dots, x, keyValue, xDotFlag, xIntegerPart, xFractionalPart, xMinusFlag);
		}
		else
		{
			executeNumber(dots, y, keyValue, yDotFlag, yIntegerPart, yFractionalPart, yMinusFlag);
		}
	}
	}
}

void Input::getDots() {
	char keyValue;
	while (dots != 6) {
		keyValue = _getch();
		if (checkChar(keyValue) && checkValidity(keyValue)) {
			modifyNumber(keyValue);
			UI.showInput(keyValue);
			if (keyValue == ENTER)
			{
				setAllNull();
				dots++;
			}
			UI.refreshCommandZone(false);
		}
	}
}