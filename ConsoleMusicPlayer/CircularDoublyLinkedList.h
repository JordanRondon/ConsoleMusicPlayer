#pragma once
#include "Node.h"
#include "MusicData.h"

class CircularDoublyLinkedList {
	private:
		Node* list;
		Node* currentNode;

	public:
		CircularDoublyLinkedList();

		Node* getList();
		Node* getCurrentNode();
		void insertEnd(Music musicInf);
		void deletePosition(int position);
		bool searchElement(std::string musicName);
		int count();
		void nextNode();
		void previousNode();
};