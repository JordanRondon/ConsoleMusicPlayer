#pragma once
#include "MusicData.h"

struct Node {
	Music MusicObj;
	Node* next;
	Node* before;
};