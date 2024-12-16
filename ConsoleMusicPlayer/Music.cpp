#include "MusicData.h"

using namespace std;

Music::Music():
	name(""),
	durationSeconds(0) {}

Music::Music(string name, int durationSeconds) :
	name(name),
	durationSeconds(durationSeconds) {}

void Music::setName(string name) {
	this->name = name;
}

void Music::setDurationSeconds(int durationSeconds) {
	this->durationSeconds = durationSeconds;
}

string Music::getName() {
	return this->name;
}

int Music::getDurationSeconds() {
	return this->durationSeconds;
}