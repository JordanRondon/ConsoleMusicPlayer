#include "CircularDoublyLinkedList.h"
#include <string> 

/**
 * @brief Constructor for the CircularDoublyLinkedList Class.
 *
 * Initializes an empty circular doubly linked list.
 */
CircularDoublyLinkedList::CircularDoublyLinkedList() :
	list(nullptr), currentNode(nullptr) {
}

/**
 * @brief Gets the starting node of the list.
 *
 * @return A pointer to the first node in the list.
 */
Node* CircularDoublyLinkedList::getList() {
	return this->list;
}

/**
 * @brief Gets the current node in the list.
 *
 * If no current node is defined, initializes to the first node in the list.
 *
 * @return A pointer to the position of the current node in the list.
 */
Node* CircularDoublyLinkedList::getCurrentNode() {
	if (this->currentNode != nullptr) {
		return currentNode;
	}
	this->currentNode = this->list;
	return this->currentNode;
}

/**
 * @brief Inserts a new node at the end of the list.
 *
 * @param musicInf Music type information that will be stored in the new node.
 */
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

/**
 * @brief Counts the total number of nodes in the list.
 *
 * @return The total number of nodes in the list.
 */
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


/**
 * @brief Move to the next node in the list.
 *
 * Move the current node to the next node in the list.
 */
void CircularDoublyLinkedList::nextNode() {
	if (this->currentNode != nullptr) {
		this->currentNode = this->currentNode->next;
	}
}

/**
 * @brief Go back to the previous node in the list.
 *
 * Change the current node to the previous node in the list.
 */
void CircularDoublyLinkedList::previousNode() {
	if (this->currentNode != nullptr) {
		this->currentNode = this->currentNode->previous;
	}
}