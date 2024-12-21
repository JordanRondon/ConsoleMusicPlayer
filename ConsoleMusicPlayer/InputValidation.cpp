#include "InputValidation.h"
#include <conio.h>
#include <iostream>

/**
 * @brief Reads and validates an integer input from the user.
 *
 * This function captures user input character by character, allowing only numeric digits (0-9).
 * It also supports backspace for corrections and stops reading when the Enter key is pressed.
 * The validated integer is then returned.
 *
 * @return The validated integer entered by the user.
 */
int validateInteger() {
	char keyPressed, content[100];
	int index = 0;

	do {
		keyPressed = _getch();
		if (keyPressed >= '0' && keyPressed <= '9') {
			std::cout << keyPressed;
			content[index] = keyPressed;
			index++;
		}
		else if (keyPressed == 8 && index > 0) {
			std::cout << keyPressed;
			std::cout << ' ';
			std::cout << keyPressed;
			index--;
		}
		else if (keyPressed == 13) std::cout << std::endl;
	} while (keyPressed != 13);

	content[index] = 0;

	return atoi(content);
}