#include "FileUtils.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

/**
 * @brief Retrieves the path to the user's Music folder on Windows systems.
 *
 * This function constructs the path to the Music directory based on the user's profile environment variable.
 *
 * @return A string containing the path to the user's Music folder. Returns an empty string if the path cannot be determined.
 */
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

/**
 * @brief Loads MP3 files from a specified directory into a circular doubly linked list.
 *
 * This function scans the given directory for MP3 files. For each valid MP3 file, it extracts its name and duration,
 * then adds it to the provided CircularDoublyLinkedList and loads the file into the MusicPlayer.
 *
 * @param path The path to the directory containing MP3 files.
 * @param list A reference to the CircularDoublyLinkedList where music data will be stored.
 * @param musicP A reference to the music player to process the length of MP3 files.
 */
void loadFileMp3(const char* path, CircularDoublyLinkedList& List, MusicPlayer& MusicP) {
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
            MusicP.load(dir_entry.path().string().c_str());
            musicData.setDurationSeconds(MusicP.getDuration());
            List.insertEnd(musicData);
        }
    }
}