#include <iostream>
#include <filesystem>
#include <conio.h>
#include "CircularDoublyLinkedList.h"
#include "MusicData.h"
#include "MusicPlayer.h"
#include "style.h"

#define QUIT 113        // 'q': Quit
#define PLAY 112        // 'P': Play
#define STOP 115        // 's': Stop
#define FASTFORWARD 102 // 'f' -> Forward
#define REWIND 114      // 'r' -> Rewind
#define NEXT 110        // 'n' -> Next
#define PREVIOUS 98     // 'b' -> Previous

using namespace std;

string getUserMusicPath();
void loadFileMp3(const char* ruta, CircularDoublyLinkedList& list);

int main() {

    int boxHeight = 11;
    int boxWidth = 70;
    int boxPosX = 25;
    int boxPosY = 7;

    CircularDoublyLinkedList list;

    int opcionLoadFile = filePathOption(boxHeight, boxWidth, boxPosX, boxPosY);

    switch (opcionLoadFile) {
    case 1:
        loadFileMp3(getUserMusicPath().c_str(), list);
        break;
    case 2:
        string carpeta = filePathString(boxHeight, boxWidth, boxPosX, boxPosY);
        loadFileMp3(carpeta.c_str(), list);
        break;
    }

    boxHeight = list.count();
    boxPosY = 8;
    char keyPress;

    do {
        box(4, boxWidth, boxPosX, 2);
        listBox(boxHeight, boxWidth, boxPosX, boxPosY);
        gotoxy(boxPosX + 6, (boxPosY + boxHeight + 4)); 
        cout << "q: QUIT p:PLAY s:STOP n:NEXT b:PREVIOUS f:FORWARD r:REWIND";
        keyPress = _getch();

        switch (keyPress) {
        case QUIT: break;
        case PLAY: break;
        case STOP: break;
        case FASTFORWARD: break;
        case REWIND: break;
        case NEXT: break;
        case PREVIOUS: break;
        }
        system("CLS");
    } while (keyPress != QUIT);

    return 0;
}

string getUserMusicPath() {
    char* userProfile = nullptr;
    size_t len = 0;

    if (_dupenv_s(&userProfile, &len, "USERPROFILE") == 0 && userProfile != nullptr) {
        std::string musicPath = std::string(userProfile) + "\\Music";
        free(userProfile);
        return musicPath;
    }

    return "";
}

void loadFileMp3(const char* path, CircularDoublyLinkedList& list) {
    Music musicData;
    MusicPlayer musicP;

    if (!std::filesystem::exists(path)) {
        std::cerr << "Error: The route '" << path << "' does not exist." << std::endl;
        return;
    }

    if (!std::filesystem::is_directory(path)) {
        std::cerr << "Error: '" << path << "' is not a valid directory." << std::endl;
        return;
    }

    for (auto const& dir_entry : filesystem::directory_iterator(path)) {
        if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".mp3") {
            musicData.setName(dir_entry.path().filename().string());
            musicP.load(dir_entry.path().string().c_str());
            musicData.setDurationSeconds(musicP.getDuration());
            list.insertEnd(musicData);
        }
    }
}
