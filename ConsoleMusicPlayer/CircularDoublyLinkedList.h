#pragma once
#include "Node.h"
#include "MusicData.h"

class CircularDoublyLinkedList {
	private:
		Node* CircularList;

	public:
		CircularDoublyLinkedList();

		Node* getList();
		void insertEnd(Music musicInf);
		void deletePosition(int position);
		void searchElement(std::string musicName);
		void count();
		Node* next();
		Node* before();
};