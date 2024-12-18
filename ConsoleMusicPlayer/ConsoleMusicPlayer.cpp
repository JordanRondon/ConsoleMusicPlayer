#include <iostream>
#include <filesystem>
#include "CircularDoublyLinkedList.h"
#include "MusicData.h"
#include "MusicPlayer.h"
#include "style.h"

using namespace std;

std::string getUserMusicPath();
void loadFileMp3(const char* ruta, CircularDoublyLinkedList& list);

int main() {

    CircularDoublyLinkedList list;

    int opcionLoadFile = filePathOption(11, 70, 25, 7);

    switch (opcionLoadFile) {
    case 1:
        loadFileMp3(getUserMusicPath().c_str(), list);
        break;
    case 2:
        string carpeta = filePathString(11, 70, 25, 7);
        loadFileMp3(carpeta.c_str(), list);
        break;
    }

    cout << list.count() << endl; 

    

    return 0;
}

std::string getUserMusicPath() {
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
