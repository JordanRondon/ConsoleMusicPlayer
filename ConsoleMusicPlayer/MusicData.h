#pragma once
#include <string>

class Music {
	private:
		std::string name;
		int durationSeconds;

	public:
		Music();
		Music(std::string name, int durationSeconds);

		void setName(std::string name);
		void setDurationSeconds(int durationSeconds);
		std::string getName();
		int getDurationSeconds();
		std::string convertSecondsToTime();
};