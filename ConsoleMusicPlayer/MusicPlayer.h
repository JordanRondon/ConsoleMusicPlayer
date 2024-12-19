#pragma once
#include "bass.h"
#include <string>

class MusicPlayer {
	private:
		HSTREAM stream;
        float volume;
        bool stoppedManually;
	
	public:
        MusicPlayer();
        ~MusicPlayer();

        void load(const char* filePath);
        void play();
        void stop();
        void seekForward();
        void seekBackward();
        double getDuration();
        float getVolume();
        void freeUpResources();
        void volumeUp();
        void volumeDown();
        bool isFinished();
};