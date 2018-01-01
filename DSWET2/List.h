
#ifndef LIST_H
#define LIST_H
#include "stddef.h"



template <class T> class ListNode {
    T data;
    ListNode* next;

public:
    ListNode(const T& data) : data(data), next(NULL) {}
    ListNode* getNext() const {
        return next;
    }
    T& getData() {
        return data;
    }
    void setNext(ListNode* next) {
        this->next = next;
    }
};
template <class T>
class List {
    ListNode<T> *head;

public:
    List() : head(NULL) {}
    T* GetData(const T& toFind) {
        ListNode<T> *temp = head;
        while (temp != NULL) {
            if (temp->getData() == toFind)
                return &temp->getData();
            temp = temp->getNext();
        }
        return NULL;
    }
    void Insert(const T& data) {
        if (GetData(data)) return;
        ListNode<T>* new_node = new ListNode<T>(data);
        new_node->setNext(head);
        head = new_node;
    }
	template <class Action>
	void GenericIteration(Action a) {
		ListNode<T>* temp = head;
		while (temp) {
			a(temp->getData());
			temp = temp->getNext();
		}
	}
    ~List() {
        while (head != NULL) {
            ListNode<T>* temp = head;
            head = head->getNext();
            delete temp;
        }
    }
};


#endif //LIST_H
