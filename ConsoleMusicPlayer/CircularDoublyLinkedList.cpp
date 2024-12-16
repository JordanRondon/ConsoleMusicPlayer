#include "CircularDoublyLinkedList.h"
#include <string> 

CircularDoublyLinkedList::CircularDoublyLinkedList() :
	list(nullptr) {
}

Node* CircularDoublyLinkedList::getList() {
	return this->list;
}

void CircularDoublyLinkedList::insertEnd(Music musicInf) {
	
	Node* newNode = new Node;
	Node* lastNode;

	newNode->MusicObj = musicInf;
	newNode->next = list;

	if (list == NULL) {
		lastNode = newNode;
	}
	else {
		lastNode = list->previous;
		list->previous = newNode;
	}

	list = newNode;
	lastNode->next = list;
	list->previous = lastNode;

	list = list->next;

}

void CircularDoublyLinkedList::deletePosition(int index) {
	
	Node* currentNode = list;
	int currentPosition = 0;

	if (list != NULL) {
		if (list->previous == list && list->next == list) {
			list = NULL;
			return;
		}

		do {
			currentPosition++;
			if (currentPosition < index)
				currentNode = currentNode->next;
		} while (currentPosition < index && currentNode != list);

		if (currentNode->previous == list->previous) {//elimina el primer nodo
			//verifica si el dato a eliminar esta en el inicio de lista
			list = currentNode->next;//actualiza una posicion adelante el inicio de lista
			list->previous = currentNode->previous;
			list->previous->next = list;
		}
		else if (currentNode->next == list) {//elimina el ultimo nodo
			//verifica si el dato a eliminar esta en el final de lista
			currentNode->previous->next = list;
			list->previous = currentNode->previous;
		}
		else {//elimina en cualquier posición
			currentNode->previous->next = currentNode->next;
			currentNode->next->previous = currentNode->previous;
		}

		delete currentNode;
	}

}

bool CircularDoublyLinkedList::searchElement(std::string musicName) {
	Node* currentNode = list;

	if (list != NULL) {
		do {
			if (currentNode->MusicObj.getName() == musicName)
				return true;
			currentNode = currentNode->next;
		} while (currentNode != list);
	}

	return false;
}

int CircularDoublyLinkedList::count() {
	
	Node* currentNode = list;
	int totalItems = 0;

	if (list != NULL) {
		do {
			totalItems++;
			currentNode = currentNode->next;
		} while (currentNode != list);
	}

	return totalItems;
}

Node* CircularDoublyLinkedList::next() {
	return list->next;
}

Node* CircularDoublyLinkedList::before() {
	return list->previous;
}