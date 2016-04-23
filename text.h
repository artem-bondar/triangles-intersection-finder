#ifndef GTEXT_H
#define GTEXT_H

#include <string>
#include "enum.h"

using namespace std;

struct Text {
	const string
		welcome = "\n Welcome to triangles intersection finder \n",
		title = "Triangles Intersection Finder",
		task = "\n This program checks if intersection of two triangles is non-empty \n\n",
		dotNames[6] = { " A", " B", " C", " D", " E", " F" },
		punctuationSigns[7] = { " = (", ")\n", ", ", ".","0","\b"," " },
		commandsKeys[KEYS_SIZE] = { "       [0-9]", "\t [-]", "\t [.]", "  [,][Space]", " [BackSpace]", "     [Enter]","\n\t [H]" },
		n = "\n",
		commandsDescriptions[KEYS_SIZE] = { " Input digit", " Inverse sign"," Change to fractional input", " Change to y-coordinate",
											" Cancel previous action", " Finish inputting current dot"," Help" },
		advice[2] = { " Executable keys are ", "highlighted.\n\n" },
		hints[HINTS_SIZE] = { " Q = (", "-", "123456789", ".", "12345", ", ", "987654321", ".", "54321",
							  ")", "\n\n Limits for input:\n ","Integer"," part - 9 digits,\n ","Fractional",
							  " part - 5 digits.\n\n Press ","[H]"," to hide help and return to menu" },
		input[4] = { " Personalize your expirience. Input numbers that you most like \n"," Triangle", " ABC", " DEF" },
		error[9] = { " Dots ", "A, B, C","D, E, F"," don't form", " a triangle"," triangles", ", they are collinear \n\n", " and ", " Both dots " },
		equal = " = ",
		win = " Selected triangles have intersection. Congratulations! \n\n",
		loss = " Selected triangles don't have intersection :( \n\n",
		exit = " Thank you for using. Have a nice day! \n\n",
		geometry[18] = { "Non-existent ", "dot." , "line.", "segment.", "triangle.", "(", ")", ", ", "{", "}", ", [", "]", "-"," - "," + ","x","y"," = 0" };
	const int
		keys[KEYS_SIZE] = { ONE, MINUS, DOT, COMMA, BACKSPACE, ENTER, HELP, SPACE },
		hintsColors[HINTS_SIZE] = { WHITE, LIGHT_RED, LIGHT_GREEN, WHITE, LIGHT_CYAN, WHITE, LIGHT_GREEN, WHITE, LIGHT_CYAN,
									WHITE, LIGHT_GREY, LIGHT_GREEN, LIGHT_GREY, LIGHT_CYAN, LIGHT_GREY, YELLOW, LIGHT_GREY };
};

extern Text text;

#endif