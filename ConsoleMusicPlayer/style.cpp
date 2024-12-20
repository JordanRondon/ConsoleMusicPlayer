#include <Windows.h>
#include <iostream>
#include <sstream>
#include <iomanip> 
#include "Node.h"
#include "CircularDoublyLinkedList.h"
#include "MusicPlayer.h"
#include "InputValidation.h"

/**
 * @brief Moves the console cursor to the specified position.
 *
 * @param posX The X-coordinate (horizontal position).
 * @param posY The Y-coordinate (vertical position).
 */
void gotoxy(int posX, int posY) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = posX;
	dwPos.Y = posY;
	SetConsoleCursorPosition(hcon, dwPos);
}

/**
 * @brief Draws a box in the console with the specified dimensions and position.
 *
 * @param height The height of the box.
 * @param width The width of the box.
 * @param posX The X-coordinate of the top-left corner.
 * @param posY The Y-coordinate of the top-left corner.
 */
void box(int height, int width, int posX, int posY) {
	//-----------------horizontal lines--------------------
	for (int i = 0; i < width; i++) {
		gotoxy(posX + i, posY); std::cout << (char)205; //top
		gotoxy(posX + i, posY + height + 1); std::cout << (char)205; //down
	}

	//-------------------vertical lines--------------------
	for (int i = 0; i < height + 2; i++) {
		gotoxy(posX, posY + i); std::cout << (char)186; //left
		gotoxy(posX + width, posY + i); std::cout << (char)186; //rigth
	}

	//---------------------top corners---------------------
	gotoxy(posX, posY); std::cout << (char)201; //left
	gotoxy(posX + width, posY); std::cout << (char)187; //rigth

	//--------------------down corners---------------------
	gotoxy(posX, posY + height + 1); std::cout << (char)200; //left
	gotoxy(posX + width, posY + height + 1); std::cout << (char)188; //rigth
}

/**
 * @brief Draws a list box in the console with a specific layout for a music list.
 *
 * @param height The height of the list box.
 * @param width The width of the list box.
 * @param posX The X-coordinate of the top-left corner.
 * @param posY The Y-coordinate of the top-left corner.
 */
void listBox(int height, int width, int posX, int posY) {
	//-----------------horizontal lines--------------------
	for (int i = 0; i < width; i++) {
		gotoxy(posX + i, posY); std::cout << (char)205; //top
		gotoxy(posX + i, posY + 2); std::cout << (char)205; //mid
		gotoxy(posX + i, posY + 2 + (height + 1)); std::cout << (char)205; //down
	}

	//-------------------vertical lines--------------------
	for (int i = 0; i < height + 4; i++) {
		gotoxy(posX, posY + i); std::cout << (char)186; //left
		gotoxy(posX + (width - 9), posY + i); std::cout << (char)186; //mid
		gotoxy(posX + width, posY + i); std::cout << (char)186; //rigth
		//gotoxy(posX + ((width - 6) / 2), posY + i); std::cout << (char)186;
	}

	//-----------------------subtitles----------------------
	gotoxy(posX + 1, posY + 1); std::cout << "NAME";
	//gotoxy(posX + ((width - 6) / 2) + 1, posY + 1); std::cout << "AUTOR";
	gotoxy((posX + (width - 7)) + 1, posY + 1); std::cout << "TIME";

	//---------------------top corners----------------------
	gotoxy(posX, posY); std::cout << (char)201; //left
	gotoxy(posX + width, posY); std::cout << (char)187; //rigth

	//---------------------down corners---------------------
	gotoxy(posX, posY + height + 3); std::cout << (char)200; //left
	gotoxy(posX + width, posY + height + 3); std::cout << (char)188; //rigth

	//--------------------intersections---------------------
	//---------up
	gotoxy(posX + (width - 9), posY); std::cout << (char)203;
	//gotoxy(posX + (width - 6) / 2, posY); std::cout << (char)203;
	
	//---------mid
	gotoxy(posX, posY + 2); std::cout << (char)204; //left back
	gotoxy(posX + (width - 9), posY + 2); std::cout << (char)206; //mid
	//gotoxy(posX + (width - 6) / 2, posY + 2); std::cout << (char)206;
	gotoxy(posX + width, posY + 2); std::cout << (char)185; //rigth back

	//---------down
	gotoxy(posX + (width - 9), posY + height + 3); std::cout << (char)202;
	//gotoxy(posX + (width - 6) / 2, posY + height + 3); std::cout << (char)202;
}

/**
 * @brief Displays a menu to select the file path option for the music folder.
 *
 * @param height The height of the box for the menu.
 * @param width The width of the box for the menu.
 * @param posX The X-coordinate of the menu.
 * @param posY The Y-coordinate of the menu.
 * @return An integer indicating the user's choice (1 or 2).
 */
int filePathOption(int height, int width, int posX, int posY) {
	int option = 0;

	do {
		box(height, width, posX, posY);
		gotoxy(posX + (width / 3.5), posY + 2); std::cout << ".:Welcome to the music console:.";
		gotoxy(posX + (width / 4), posY + 4); std::cout << "Where is your music located?";
		gotoxy(posX + (width / 4), posY + 5); std::cout << "Select an option:";
		gotoxy(posX + (width / 4), posY + 7); std::cout << "1. Default folder \"Music\"";
		gotoxy(posX + (width / 4), posY + 8); std::cout << "2. Enter the path to my music folder";
		gotoxy(posX + (width / 4), posY + 10); std::cout << "Please choose an option (1 or 2): ";
		option = validateInteger();
		system("cls");
	} while (!(option != 0 && (option == 1 || option == 2)));
	
	return option;
}

/**
 * @brief Prompts the user to enter the path of the music folder.
 *
 * @param height The height of the box for the input prompt.
 * @param width The width of the box for the input prompt.
 * @param posX The X-coordinate of the input prompt.
 * @param posY The Y-coordinate of the input prompt.
 * @return A string containing the entered path.
 */
std::string filePathString(int height, int width, int posX, int posY) {
	std::string path = "";

	do {
		box(height, width, posX, posY);
		gotoxy(posX + (width / 3.5), posY + 2); std::cout << ".:Welcome to the music console:.";
		gotoxy(posX + (width / 4), posY + 5); std::cout << "Enter the path of the music folder";
		gotoxy(posX + (width / 4), posY + 6); std::cout << "example: \"C:/Users/profile/Music/\"";
		gotoxy(posX + (width / 4), posY + 8); std::cout << "path: ";
		std::cin >> path;
		system("cls");
	} while (path == "");

	return path;
}

/**
 * @brief Displays a list of music tracks in a circular doubly linked list.
 *
 * @param posX The X-coordinate of the list display.
 * @param posY The Y-coordinate of the list display.
 * @param list A pointer to the head node of the circular doubly linked list.
 */
void showMusicList(int posX, int posY, Node* list) {
	if (list != nullptr) {
		Node* currentNode = list;
		int iterator = 0;

		do {
			gotoxy(posX + 1, (posY + iterator) +3);
			std::cout << iterator + 1 << '.' << currentNode->MusicObj.getName();
			gotoxy((posX + 62), (posY + iterator) +3);
			std::cout << currentNode->MusicObj.convertSecondsToTime();
			currentNode = currentNode->next;
			iterator++;
		} while (currentNode != list);
	}
}

/**
 * @brief Displays the currently selected music track along with its details.
 *
 * @param posX The X-coordinate of the display.
 * @param posY The Y-coordinate of the display.
 * @param list A pointer to the node of the selected music track.
 * @param volume The current volume level as a float.
 */
void showSelectedMusic(int posX, int posY, Node* list, float volume) {
	gotoxy(posX+3, posY+1);
	std::cout << "Selected music:";
	gotoxy(posX + 10, posY + 3);
	std::cout << list->MusicObj.getName();
	
	gotoxy(posX + 29, posY + 1);
	std::cout << "Duration:";
	gotoxy(posX + 39, posY + 1);
	std::cout << list->MusicObj.convertSecondsToTime();

	gotoxy(posX + 56, posY + 1);
	std::cout << "Volume:";
	gotoxy(posX + 64, posY + 1);
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(0) << volume * 100;
	std::cout << oss.str() + "%";
}

/**
 * @brief Creates a user interface for the music list, displaying the selected music and the full list.
 *
 * @param height The height of the interface.
 * @param width The width of the interface.
 * @param posX The X-coordinate of the interface.
 * @param posY The Y-coordinate of the interface.
 * @param list The circular doubly linked list of music tracks.
 * @param MusicP The MusicPlayer object used for playback.
 */
void musicListInterface(int height, int width, int posX, int posY, CircularDoublyLinkedList& list, MusicPlayer& MusicP) {
	box(4, width, posX, 2);
	showSelectedMusic(posX, 2, list.getCurrentNode(), MusicP.getVolume());

	listBox(height, width, posX, posY);
	showMusicList(posX, posY, list.getList());
}