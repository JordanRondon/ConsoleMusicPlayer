#include "FileUtils.h"
#include <filesystem>
#include <iostream>


namespace fs = std::filesystem;

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

    for (auto const& dir_entry : fs::directory_iterator(path)) {
        if (dir_entry.is_regular_file() && dir_entry.path().extension() == ".mp3") {
            musicData.setName(dir_entry.path().filename().string());
            musicP.load(dir_entry.path().string().c_str());
            musicData.setDurationSeconds(musicP.getDuration());
            list.insertEnd(musicData);
        }
    }
}