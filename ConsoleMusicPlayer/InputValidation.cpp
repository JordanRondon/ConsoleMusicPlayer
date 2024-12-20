#include "InputValidation.h"
#include <conio.h>
#include <iostream>


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