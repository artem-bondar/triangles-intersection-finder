#include "interface.h"
#include "input.h"
#include "line.h"
Text text;
Input input;
Interface UI;

void main() {
	UI.showMenu();
	input.getDots();
	UI.operateWithInputtedDots();
	UI.showQuitMessage();
	system("pause");
}