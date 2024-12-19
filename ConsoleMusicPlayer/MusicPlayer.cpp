#include <iostream>
#include "MusicPlayer.h"

MusicPlayer::MusicPlayer(): stream(0), volume(1.0f) {
    if (!BASS_Init(-1, 44100, 0, 0, NULL)) {
        std::cerr << "Error initializing BASS: " << BASS_ErrorGetCode() << std::endl;
    }
}

MusicPlayer::~MusicPlayer() {
    this->freeUpResources();
    BASS_Free();
}

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

void MusicPlayer::play() {
    if (!BASS_ChannelPlay(this->stream, FALSE)) {
        std::cerr << "Error playing file: " << BASS_ErrorGetCode() << std::endl;
        BASS_StreamFree(this->stream);
    }
}

void MusicPlayer::stop() {
    BASS_ChannelStop(this->stream);
}

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

double MusicPlayer::getDuration() {
    QWORD length = BASS_ChannelGetLength(this->stream, BASS_POS_BYTE);
    double duration = BASS_ChannelBytes2Seconds(this->stream, length);
    return duration;
}

float MusicPlayer::getVolume() {
    return this->volume;
}

void MusicPlayer::freeUpResources() {
    if (this->stream) {
        BASS_StreamFree(this->stream);
    }
}

void MusicPlayer::volumeUp() {
    if (this->volume >= 1.0f)
        return;

    this->volume = this->volume + 0.1f;
    if (!BASS_ChannelSetAttribute(this->stream, BASS_ATTRIB_VOL, volume)) {
        std::cerr << "Error al configurar el volumen" << std::endl;
    }
}

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