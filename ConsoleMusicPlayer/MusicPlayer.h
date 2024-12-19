#pragma once
#include "bass.h"
#include <string>

class MusicPlayer {
	private:
		HSTREAM stream;
	
	public:
        MusicPlayer();
        ~MusicPlayer();

        void load(const char* filePath);
        void play();
        void stop();
        void seekForward();
        void seekBackward();
        double getDuration();
        void freeUpResources();
};