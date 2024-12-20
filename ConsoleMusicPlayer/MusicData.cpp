#include "MusicData.h"

using namespace std;

/**
 * @brief Default constructor for the Music class.
 *
 * Initializes the music object with an empty name and a duration of 0 seconds.
 */
Music::Music():
	name(""),
	durationSeconds(0) {}

/**
 * @brief Parameterized constructor for the Music class.
 *
 * @param name The name of the music track.
 * @param durationSeconds The duration of the music track in seconds.
 */
Music::Music(string name, int durationSeconds) :
	name(name),
	durationSeconds(durationSeconds) {}

/**
 * @brief Sets the name of the music track.
 *
 * @param name The name to assign to the music track.
 */
void Music::setName(string name) {
	this->name = name;
}

/**
 * @brief Sets the duration of the music track in seconds.
 *
 * @param durationSeconds The duration to assign to the music track.
 */
void Music::setDurationSeconds(int durationSeconds) {
	this->durationSeconds = durationSeconds;
}

/**
 * @brief Retrieves the name of the music track.
 *
 * @return A string containing the name of the music track.
 */
string Music::getName() {
	return this->name;
}

/**
 * @brief Retrieves the duration of the music track in seconds.
 *
 * @return An integer representing the duration of the music track in seconds.
 */
int Music::getDurationSeconds() {
	return this->durationSeconds;
}

/**
 * @brief Converts the duration of the music track from seconds to a time format.
 *
 * The time format is represented as "hours:minutes:seconds".
 *
 * @return A string containing the formatted duration of the music track.
 */
string Music::convertSecondsToTime() {
	int seconds = this->getDurationSeconds() % 60;
	int minutes = (this->getDurationSeconds() / 60) % 60;
	int hours = this->getDurationSeconds() / 3600;
	return std::to_string(hours) + ':' + std::to_string(minutes) + ':' + std::to_string(seconds);
}