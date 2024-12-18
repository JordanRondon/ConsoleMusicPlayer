#pragma once
#include "Node.h"
#include "MusicData.h"

class CircularDoublyLinkedList {
	private:
		Node* list;

	public:
		CircularDoublyLinkedList();

		Node* getList();
		void insertEnd(Music musicInf);
		void deletePosition(int position);
		bool searchElement(std::string musicName);
		int count();
};