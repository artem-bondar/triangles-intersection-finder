#ifndef INTERFACE_H
#define INTERFACE_H

#include "text.h"
#include <Windows.h>
#include <iostream>

extern int globalTextColor;
extern HANDLE hStdOut;
extern CONSOLE_SCREEN_BUFFER_INFO csbi;

class Interface {
public:

	void
		refreshCommandZone(const bool mode);
	void
		showQuitMessage() const,
		showMenu() const,
		operateWithInputtedDots() const,
		showInput(const char keyValue) const,
		outputNumber(const double number, const int fractionalPart) const,
		showFractionalPart(const char keyValue, int* zeroCounter, int* digitsCounter, int &currentZeroCounter, int &currentDigitsCounter, const int &fractionalPart) const;

private:

	void
		changeTextColor(const int textColor) const,
		clearConsoleRow(const short rowNumber, const short moveCursor) const,
		clearHelpMenuZone(const short x, const short y, const int rows) const,
		showCommands() const,
		showHints() const;
			
	bool isHintsShowed;

};

extern Interface UI;

template <class TypeClass> void print(const TypeClass text, const int textColor, const int backgroundColor = BLACK) {
	SetConsoleTextAttribute(hStdOut, (WORD)((backgroundColor << 4) | textColor));
	cout << text;
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | globalTextColor));
}

#endif