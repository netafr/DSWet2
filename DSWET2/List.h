
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

/*
 This class represents a basic generic list data structure.
 Allowing to insert new data (to beginning of list) and to get pointer to data in list.
 The list is implemeneted as chain of nodes.
 */
template <class T>
class List {
    ListNode<T> *head;

public:
    /* Description:   Cto'r - at first head is NULL because no nodes at all
	*/
    List() : head(NULL) {}
  /* Description:  Returns pointer to wanted data, NULL if doesnt exist.
  * Input:         toFind - dummy data used for comparison
  * Output:        None.
  * Return Values: Pointer to wanted data.
  */
    T* GetData(const T& toFind) {
        ListNode<T> *temp = head;
        while (temp != NULL) {
            if (temp->getData() == toFind)
                return &temp->getData();
            temp = temp->getNext();
        } //If didn't find, will return NULL
        return NULL;
    }
  /* Description:  Inserts a new node into the list, will be set as the new head.
  * Input:         data - the new data to insert
  * Output:        Inserts the new data (using node) will be placed at beginning
  * Return Values: None.
  */
    void Insert(const T& data) {
        ListNode<T>* new_node = new ListNode<T>(data);
        new_node->setNext(head); //Updates the head.
        head = new_node;
    }
 /* Description:   Executes a certain function on each node in the list.
  * Input:         a- action class with () operator
  * Output:        performs the action class on each data in list
  * Return Values: None.
  */
	template <class Action>
	void GenericIteration(Action a) {
		ListNode<T>* temp = head;
		while (temp) {
			a(temp->getData());
			temp = temp->getNext();
		}
	}
    /* Description:   Dto'r.
	*/
    ~List() {
        //Deletes inner nodes first.
        while (head != NULL) {
            ListNode<T>* temp = head;
            head = head->getNext();
            delete temp;
        }
    }
};


#endif //LIST_H
