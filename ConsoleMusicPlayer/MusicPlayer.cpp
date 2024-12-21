#include <iostream>
#include "MusicPlayer.h"

/**
 * @brief Default constructor for the MusicPlayer class.
 *
 * Initializes the MusicPlayer object, setting up the BASS library for audio playback.
 * Logs an error if initialization fails.
 */
MusicPlayer::MusicPlayer(): stream(0), volume(1.0f), stoppedManually(false){
    if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
        std::cerr << "Error initializing BASS: " << BASS_ErrorGetCode() << std::endl;
    }
}

/**
 * @brief Destructor for the MusicPlayer class.
 *
 * Releases resources allocated by the MusicPlayer and frees the BASS library.
 */
MusicPlayer::~MusicPlayer() {
    this->freeUpResources();
    BASS_Free();
}

/**
 * @brief Loads an MP3 file into the MusicPlayer for playback.
 *
 * @param filePath The file path of the MP3 file to load.
 */
void MusicPlayer::load(const char* filePath) {
    this->freeUpResources();
    this->stream = BASS_StreamCreateFile(FALSE, filePath, 0, 0, 0);
    
    if (!this->stream) {
        std::cerr << "Error loading MP3 file: " << BASS_ErrorGetCode() << std::endl;
    }

    if (!BASS_ChannelSetAttribute(this->stream, BASS_ATTRIB_VOL, this->volume)) {
        std::cerr << "Error al configurar el volumen" << std::endl;
    }
}

/**
 * @brief Plays the currently loaded MP3 file.
 *
 * Logs an error if playback fails.
 */
void MusicPlayer::play() {
    if (!BASS_ChannelPlay(this->stream, FALSE)) {
        std::cerr << "Error playing file: " << BASS_ErrorGetCode() << std::endl;
        BASS_StreamFree(this->stream);
    }
    this->stoppedManually = false;
}

/**
 * @brief Stops playback of the currently loaded MP3 file.
 *
 * Marks the playback as manually stopped.
 */
void MusicPlayer::stop() {
    BASS_ChannelStop(this->stream);
    this->stoppedManually = true;
}

/**
 * @brief Seeks forward in the currently playing MP3 file by 5 seconds.
 *
 * Ensures the new position does not exceed the duration of the file.
 */
void MusicPlayer::seekForward() {
    double seconds = 5.0;
    QWORD positionBytes = BASS_ChannelGetPosition(this->stream, BASS_POS_BYTE);
    double positionSeconds = BASS_ChannelBytes2Seconds(this->stream, positionBytes);
    double newPositionSeconds = positionSeconds + seconds;
    double durationSeconds = BASS_ChannelBytes2Seconds(this->stream, BASS_ChannelGetLength(this->stream, BASS_POS_BYTE));
    
    if (newPositionSeconds < durationSeconds) {
        QWORD newPositionBytes = BASS_ChannelSeconds2Bytes(this->stream, newPositionSeconds);

        BASS_ChannelSetPosition(this->stream, newPositionBytes, BASS_POS_BYTE);
    }
}

/**
 * @brief Seeks backward in the currently playing MP3 file by 5 seconds.
 *
 * Ensures the new position does not go below 0 seconds.
 */
void MusicPlayer::seekBackward() {
    double seconds = 5.0;
    QWORD positionBytes = BASS_ChannelGetPosition(this->stream, BASS_POS_BYTE);
    double positionSeconds = BASS_ChannelBytes2Seconds(this->stream, positionBytes);
    double newPositionSeconds = positionSeconds - seconds;

    if (newPositionSeconds >= 0) {
        QWORD newPositionBytes = BASS_ChannelSeconds2Bytes(this->stream, newPositionSeconds);

        BASS_ChannelSetPosition(this->stream, newPositionBytes, BASS_POS_BYTE);
    }
}

/**
 * @brief Retrieves the duration of the currently loaded MP3 file in seconds.
 *
 * @return The duration of the file in seconds.
 */
double MusicPlayer::getDuration() {
    QWORD length = BASS_ChannelGetLength(this->stream, BASS_POS_BYTE);
    double duration = BASS_ChannelBytes2Seconds(this->stream, length);
    return duration;
}

/**
 * @brief Retrieves the current volume level of the MusicPlayer.
 *
 * @return The current volume level as a float (range: 0.0f to 1.0f).
 */
float MusicPlayer::getVolume() {
    return this->volume;
}

/**
 * @brief Frees resources associated with the current MP3 file.
 */
void MusicPlayer::freeUpResources() {
    if (this->stream) {
        BASS_StreamFree(this->stream);
    }
}

/**
 * @brief Increases the volume of the MusicPlayer by 10%.
 *
 * Ensures the volume does not exceed 100% (1.0f).
 */
void MusicPlayer::volumeUp() {
    if (this->volume >= 1.0f)
        return;

    this->volume = this->volume + 0.1f;
    if (!BASS_ChannelSetAttribute(this->stream, BASS_ATTRIB_VOL, volume)) {
        std::cerr << "Error al configurar el volumen" << std::endl;
    }
}

/**
 * @brief Decreases the volume of the MusicPlayer by 10%.
 *
 * Ensures the volume does not go below 0% (0.0f).
 */
void MusicPlayer::volumeDown() {
    if (this->volume <= 0.0f)
        return;
    if ((this->volume - 0.1f) < 0.0f)
        this->volume = 0.0f;
    else
        this->volume = this->volume - 0.1f;
    if (!BASS_ChannelSetAttribute(this->stream, BASS_ATTRIB_VOL, volume)) {
        std::cerr << "Error al configurar el volumen" << std::endl;
    }
}

/**
 * @brief Checks if the playback of the MP3 file has finished.
 *
 * @return True if playback has stopped and was not manually stopped, false otherwise.
 */
bool MusicPlayer::isFinished() {
    return !this->stoppedManually && BASS_ChannelIsActive(this->stream) == BASS_ACTIVE_STOPPED;
}