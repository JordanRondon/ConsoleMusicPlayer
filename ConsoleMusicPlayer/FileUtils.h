#pragma once

#include <string>
#include "CircularDoublyLinkedList.h"
#include "MusicPlayer.h"

std::string getUserMusicPath();
void loadFileMp3(const char* ruta, CircularDoublyLinkedList& List, MusicPlayer& MusicP);