#pragma once

void gotoxy(int posX, int posY);
void box(int height, int width, int posX, int posY);
void listBox(int height, int width, int posX, int posY);
void barraDeProgreso(int width, int posX, int posY);
int filePathOption(int height, int width, int posX, int posY);
std::string filePathString(int height, int width, int posX, int posY);
void showMusicList(int posX, int posY, Node* list);
void showSelectedMusic(int posX, int posY, Node* list, float volume);