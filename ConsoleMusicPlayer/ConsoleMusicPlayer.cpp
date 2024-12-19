#include <iostream>
#include <filesystem>
#include <atomic>
#include <thread>
#include <conio.h>
#include "CircularDoublyLinkedList.h"
#include "MusicData.h"
#include "MusicPlayer.h"
#include "FileUtils.h"
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

void threadNextSong(MusicPlayer& MusicP, CircularDoublyLinkedList& List, string& currentMusicPath, std::atomic<bool>& running);

int main() {

    int boxHeight = 11;
    int boxWidth = 70;
    int boxPosX = 25;
    int boxPosY = 7;

    CircularDoublyLinkedList List;
    MusicPlayer MusicP;

    int opcionLoadFile = filePathOption(boxHeight, boxWidth, boxPosX, boxPosY);

    switch (opcionLoadFile) {
    case 1:
        loadFileMp3(getUserMusicPath().c_str(), List, MusicP);
        break;
    case 2:
        string carpeta = filePathString(boxHeight, boxWidth, boxPosX, boxPosY);
        loadFileMp3(carpeta.c_str(), List, MusicP);
        break;
    }
        
    boxHeight = List.count();
    boxPosY = 8;
    char keyPress = NULL;
    string currentMusicPath = "";

    std::atomic<bool> running(true);
    std::thread threadMusic (threadNextSong, std::ref(MusicP), std::ref(List), std::ref(currentMusicPath), std::ref(running));

    do {
        musicListInterface(boxHeight, boxWidth, boxPosX, boxPosY, List, MusicP);

        string musicPath = getUserMusicPath() + '/' + List.getCurrentNode()->MusicObj.getName();
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
            List.nextNode();
            break;
        case PREVIOUS:
            List.previousNode();
            break;
        }
        system("CLS");
    } while (keyPress != QUIT);

    running = false;
    threadMusic.join();

    return 0;
}

void threadNextSong(MusicPlayer& MusicP, CircularDoublyLinkedList& List, string& currentMusicPath, std::atomic<bool>& running) {
    while (running) {
        if (MusicP.isFinished()) {
            List.nextNode();
            string musicPath = getUserMusicPath() + '/' + List.getCurrentNode()->MusicObj.getName();
            std::replace(musicPath.begin(), musicPath.end(), '\\', '/');
            MusicP.load(musicPath.c_str());
            currentMusicPath = musicPath;
            MusicP.play();
        }
        Sleep(100);
    }
    if (!running) MusicP.stop();
}