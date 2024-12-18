#include <Windows.h>
#include <iostream>

void gotoxy(int posX, int posY) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = posX;
	dwPos.Y = posY;
	SetConsoleCursorPosition(hcon, dwPos);
}

//int menu() {
//	//menú principal
//	int opcion;
//	do {
//		system("cls");
//		cout << "\t.:REPRODUCTOR DE MUSICA:." << endl;
//		cout << "\t------------------------" << endl;
//		cout << "\n1. Agregar Musica" << endl;
//		cout << "2. Eliminar Musica" << endl;
//		cout << "3. Escuchar Musica" << endl;
//		cout << "4. Salir" << endl;
//		cout << "Ingresa uno de le las opciones: "; opcion = validarEntero();
//	} while (opcion <= 0 || opcion >= 5);
//
//	return opcion;
//}

//int menu2(int x, int y) {
//	//menú del reproductor de música
//	int opcion;
//
//	do {
//		gotoxy(x, y + 8); cout << "1. siguiente";
//		gotoxy(x, y + 9); cout << "2. anterior";
//		gotoxy(x, y + 10); cout << "3. salir";
//		gotoxy(x, y + 11); cout << "Ingresa uno de le las opciones: "; opcion = validarEntero();
//	} while (opcion <= 0 || opcion >= 4);
//
//	return opcion;
//}

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

void barraDeProgreso(int width, int posX, int posY) {
	for (int i = 0; i < width; i++) {//linea principal
		gotoxy(posX + i, posY); std::cout << "-";
	}
	for (int i = 0; i < width; i++) {//animacion de progreso
		gotoxy(posX + i, posY); std::cout << (char)220;
		Sleep(100);//retarda por cierto tiempo el proceso
	}
}

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
		std::cin >> option;
		system("cls");
	} while (!(option != 0 && (option == 1 || option == 2)));
	
	return option;
}

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