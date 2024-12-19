#include <iostream>
#include <filesystem>
#include <atomic>
#include <thread>
#include <conio.h>
#include "CircularDoublyLinkedList.h"
#include "MusicData.h"
#include "MusicPlayer.h"
#include "style.h"

#define QUIT 113        // 'q'
#define PLAY 112        // 'P'
#define STOP 115        // 's'
#define FASTFORWARD 102 // 'f'
#define REWIND 114      // 'r'
#define NEXT 110        // 'n'
#define PREVIOUS 98     // 'b'
#define VOLUMEUP 43     // '+'
#define VOLUMEDOWN 45   // '-'

using namespace std;

string getUserMusicPath();
void loadFileMp3(const char* ruta, CircularDoublyLinkedList& list, MusicPlayer& musicP);
void threadNexSong(MusicPlayer& MusicP, CircularDoublyLinkedList& list, string& currentMusicPath, std::atomic<bool>& running);

int main() {

    int boxHeight = 11;
    int boxWidth = 70;
    int boxPosX = 25;
    int boxPosY = 7;

    CircularDoublyLinkedList list;
    MusicPlayer MusicP;

    int opcionLoadFile = filePathOption(boxHeight, boxWidth, boxPosX, boxPosY);

    switch (opcionLoadFile) {
    case 1:
        loadFileMp3(getUserMusicPath().c_str(), list, MusicP);
        break;
    case 2:
        string carpeta = filePathString(boxHeight, boxWidth, boxPosX, boxPosY);
        loadFileMp3(carpeta.c_str(), list, MusicP);
        break;
    }
        
    boxHeight = list.count();
    boxPosY = 8;
    char keyPress = NULL;
    string currentMusicPath = "";

    std::atomic<bool> running(true);
    std::thread threadMusic (threadNexSong, std::ref(MusicP), std::ref(list), std::ref(currentMusicPath), std::ref(running));

    do {
        musicListInterface(boxHeight, boxWidth, boxPosX, boxPosY, list, MusicP);

        string musicPath = getUserMusicPath() + '/' + list.getCurrentNode()->MusicObj.getName();
        std::replace(musicPath.begin(), musicPath.end(), '\\', '/');
        gotoxy(0, (boxPosY + boxHeight + 6));

        if (musicPath != currentMusicPath) {
            MusicP.load(musicPath.c_str());
            MusicP.play();
            currentMusicPath = musicPath;
        }

        gotoxy(boxPosX + 6, (boxPosY + boxHeight + 4)); 
        cout << "q: QUIT p:PLAY s:STOP n:NEXT b:PREVIOUS f:FORWARD r:REWIND";
        gotoxy(boxPosX + 22, (boxPosY + boxHeight + 5));
        cout << "+: VOLUMEUP -:VOLUMEDOWN";

        keyPress = _getch();

        switch (keyPress) {
        case PLAY: 
            MusicP.play();
            break;
        case STOP:
            MusicP.stop();
            break;
        case FASTFORWARD: 
            MusicP.seekForward();
            break;
        case REWIND:
            MusicP.seekBackward();
            break;
        case VOLUMEUP:
            MusicP.volumeUp();
            break;
        case VOLUMEDOWN:
            MusicP.volumeDown();
            break;
        case NEXT:
            list.nextNode();
            break;
        case PREVIOUS:
            list.previousNode();
            break;
        }
        system("CLS");
    } while (keyPress != QUIT);

    running = false;
    threadMusic.join();

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

void loadFileMp3(const char* path, CircularDoublyLinkedList& list, MusicPlayer& musicP) {
    Music musicData;

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

void threadNexSong(MusicPlayer& MusicP, CircularDoublyLinkedList& list, string& currentMusicPath, std::atomic<bool>& running) {
    while (running) {
        if (MusicP.isFinished()) {
            list.nextNode();
            string musicPath = getUserMusicPath() + '/' + list.getCurrentNode()->MusicObj.getName();
            std::replace(musicPath.begin(), musicPath.end(), '\\', '/');
            MusicP.load(musicPath.c_str());
            currentMusicPath = musicPath;
            MusicP.play();
        }
        Sleep(100);
    }
    if (!running) MusicP.stop();
}