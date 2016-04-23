#include "input.h"
#include "implements.h"
#include "interface.h"

using namespace std;

int globalTextColor = LIGHT_GREY;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

void Interface::clearConsoleRow(const short rowNumber = 0, const short moveCursor = 0) const {
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	DWORD binBuffer;
	FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', csbi.dwSize.X, { 0, csbi.dwCursorPosition.Y - rowNumber }, &binBuffer);
	SetConsoleCursorPosition(hStdOut, { 0, csbi.dwCursorPosition.Y - moveCursor });
}

void Interface::clearHelpMenuZone(const short x = 0, const short y = 7, const int rows = 8) const {
	COORD cleanAfterCoords = { x, y };
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	DWORD binBuffer;
	FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', rows * csbi.dwSize.X, cleanAfterCoords, &binBuffer);
	FillConsoleOutputAttribute(hStdOut, BLACK, rows * csbi.dwSize.X, cleanAfterCoords, &binBuffer);
	SetConsoleCursorPosition(hStdOut, cleanAfterCoords);
}

void Interface::changeTextColor(const int textColor) const {
	globalTextColor = textColor;
	SetConsoleTextAttribute(hStdOut, (WORD)((BLACK << 4) | textColor));
}

void Interface::showCommands() const {
	for (int i = 0; i < KEYS_SIZE; i++)
	{
		if (input.checkValidity(text.keys[i])) print(text.commandsKeys[i], YELLOW);
		else print(text.commandsKeys[i], DARK_GREY);
		print(text.commandsDescriptions[i], LIGHT_GREY);
		cout << text.n;
	}
}

void Interface::showHints() const {
	for (int i = 0; i < HINTS_SIZE; i++)
		print(text.hints[i], text.hintsColors[i]);
}

void Interface::showMenu() const {
	SetConsoleTitle((LPCSTR)text.title.c_str());
	print(text.welcome, WHITE, BLUE);
	print(text.task, WHITE, MAGENTA);
	cout << text.advice[0];
	print(text.advice[1], YELLOW);
	showCommands();
	cout << text.n;
	print(text.input[0], BLUE, YELLOW);
	cout << text.n;
	print(text.input[1], WHITE, GREEN);
	print(text.input[2], WHITE, GREEN);
	print(text.punctuationSigns[6], WHITE, GREEN);
	changeTextColor(LIGHT_GREEN);
	cout << text.n << text.n << text.dotNames[0] << text.punctuationSigns[0];
}

void Interface::showQuitMessage() const {
	print(text.exit, WHITE, MAGENTA);
	cout << text.punctuationSigns[6];
}

void Interface::refreshCommandZone(const bool mode) {
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	clearHelpMenuZone();
	if (mode)
		isHintsShowed = !isHintsShowed;
	if (isHintsShowed)
		showHints();
	else
		showCommands();
	SetConsoleCursorPosition(hStdOut, csbi.dwCursorPosition);
}

void Interface::showFractionalPart(const char keyValue, int* zeroCounter, int* digitsCounter, int &currentZeroCounter, int &currentDigitsCounter, const int &fractionalPart) const {
	if (keyValue == ZERO) {
		zeroCounter[currentZeroCounter]++;
		if (digitsCounter[currentDigitsCounter])
			currentDigitsCounter++;
	}
	else
		if (keyValue == BACKSPACE)
		{
			if ((currentZeroCounter == currentDigitsCounter &&
				zeroCounter[currentZeroCounter] > digitsCounter[currentDigitsCounter]) ||
				currentZeroCounter < currentDigitsCounter)
			{
				if (zeroCounter[currentZeroCounter])
				{
					zeroCounter[currentZeroCounter]--;
					if (!zeroCounter[currentZeroCounter] && currentDigitsCounter)
						currentDigitsCounter--;
				}
			}
			else
			{
				if (digitsCounter[currentDigitsCounter])
				{
					digitsCounter[currentDigitsCounter]--;
					if (!digitsCounter[currentDigitsCounter] && currentZeroCounter)
						currentZeroCounter--;
				}
			}
		}
		else
			if (isdigit(keyValue))
			{
				digitsCounter[currentDigitsCounter]++;
				if (zeroCounter[currentZeroCounter])
					currentZeroCounter++;
			}
	if (zeroCounter[currentZeroCounter] == fractionalPart)
		cout << text.punctuationSigns[3] << text.punctuationSigns[4] * zeroCounter[currentZeroCounter];
	else
		cout << text.punctuationSigns[4] * zeroCounter[currentZeroCounter];
}

void Interface::outputNumber(const double number, const int fractionalPart) const {
	if (fractionalPart == 5 && (number < 0.0001 && number > -0.00009 && number))
	{
		cout.precision(5);
		cout << fixed << number;
		cout.unsetf(ios::fixed);
	}
	else
	{
		cout.precision(15);
		cout << number;
	}
}

void Interface::showInput(const char keyValue) const {
	clearConsoleRow();
	cout << text.dotNames[input.dots] << text.punctuationSigns[0];
	if (input.xMinusFlag && !input.xIntegerPart)
		cout << text.geometry[12];
	if (input.xIntegerPart)
		outputNumber(input.array[input.dots].getCoordinates(x), input.xFractionalPart);
	if (input.xDotFlag && !input.commaFlag)
	{
		showFractionalPart(keyValue, input.xZeroCounter, input.xDigitsCounter, input.xCurrentZeroCounter, input.xCurrentDigitsCounter, input.xFractionalPart);
	}
	if (input.commaFlag) {
		cout << text.punctuationSigns[2];
		if (input.yMinusFlag && !input.yIntegerPart)
			cout << text.geometry[12];
		if (input.yIntegerPart)
			outputNumber(input.array[input.dots].getCoordinates(y), input.yFractionalPart);
		if (input.yDotFlag) {
			showFractionalPart(keyValue, input.yZeroCounter, input.yDigitsCounter, input.yCurrentZeroCounter, input.yCurrentDigitsCounter, input.yFractionalPart);
		}
	}
	if (keyValue == ENTER)
	{
		if (input.yDotFlag && !input.yFractionalPart)
			cout << text.punctuationSigns[5];
		cout << text.punctuationSigns[1];
		if (input.dots == 2)
		{
			cout << text.n;
			print(text.input[1], WHITE, CYAN);
			print(text.input[3], WHITE, CYAN);
			print(text.punctuationSigns[6], WHITE, CYAN);
			cout << text.n << text.n;
			changeTextColor(LIGHT_CYAN);
		}
		if ((input.dots + 1) != 6) cout << text.dotNames[input.dots + 1] << text.punctuationSigns[0];
		else
			changeTextColor(LIGHT_GREY);
	}
}

void Interface::operateWithInputtedDots() const {
	clearHelpMenuZone(0, 1, 29);
	Triangle ABC(input.array[0], input.array[1], input.array[2]),
			 DEF(input.array[3], input.array[4], input.array[5]);
	if (ABC.checkExistence() && DEF.checkExistence())
	{
		if (ABC.checkIntersectionWith(DEF))
			print(text.win, WHITE, GREEN);
		else
			print(text.loss, WHITE, RED);
		changeTextColor(LIGHT_GREEN);
		cout << text.input[2] << text.equal << ABC << text.n;
		changeTextColor(LIGHT_CYAN);
		cout << text.input[3] << text.equal << DEF << text.n << text.n;
		changeTextColor(LIGHT_GREY);
	}
	else
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((RED << 4) | WHITE));
		if (!ABC.checkExistence() && !DEF.checkExistence())
			cout << text.error[8] << text.error[1] << text.error[7] << text.error[2] << text.error[3] << text.error[5];
		else
		{
			cout << text.error[0];
			if (!ABC.checkExistence())
				cout << text.error[1];
			else
				cout << text.error[2];
			cout << text.error[3] << text.error[4];
		}
		cout << text.error[6];
	}
}