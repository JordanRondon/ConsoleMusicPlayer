#include <iostream>
#include <filesystem>
#include "CircularDoublyLinkedList.h"
#include "MusicData.h"
#include "MusicPlayer.h"
#include "style.h"

using namespace std;

void loadFileMp3(const char* ruta, CircularDoublyLinkedList& list);

int main() {

    CircularDoublyLinkedList list;

    const char* carpeta = "C:/Users/JORDAN/Music/";
    loadFileMp3(carpeta, list);

    return 0;
}

void loadFileMp3(const char* ruta, CircularDoublyLinkedList& list) {
    Music musicData;
    MusicPlayer musicP;

    for (auto const& dir_entry : filesystem::directory_iterator(ruta)) {
        if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".mp3") {
            musicData.setName(dir_entry.path().filename().string());
            musicP.load(dir_entry.path().string().c_str());
            musicData.setDurationSeconds(musicP.getDuration());
            list.insertEnd(musicData);
        }
    }
}
