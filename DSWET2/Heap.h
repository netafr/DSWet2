//
// Created by Oren Jacobian Pana on 12/28/2017.
//

#ifndef DSHW1_HEAP_H
#define DSHW1_HEAP_H
#define FACTOR 2
#define SHRINK_FACTOR 0.25
#include "Wrapper.h"

/* This class represents a min-heap data structure.
   Heap uses the Wrapper class: will save index of element in the data field.
   Allocates array of pointers to wrappers, and allows to:
   -Insert a new wrapper (by his pointer) to the heap
   -GetMin receive the minimum element in the heap (its a min-heap)
   -DelKey deletes a wanted key by a given index.

   Using size and max_size fields the heap can use dynamic array.
   When the array is full (size = max_size) will resize: allocate a new array with
   new size = max_size multiplied by FACTOR (see define). If the current size is smaller
   than actual max_size, will shrink the array by half.
 */
class Heap{

    Wrapper<int>** arr;
    int size;
    int max_size;

    /* Description:  Swaps between two pointers to Wrapper, updates
                     data of each wrapper to be the new index in the array.
	* Input:         i,j indices in array to swap between
	* Output:        Updates the array according to the swap, updates the data
                     of each wrapper to be the new index.
	* Return Values: None.
	*/
	void swap(int i, int j) {
		if (i < 0 || i >= size || j < 0 || j >= size) return;
		Wrapper<int>* temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		(arr[i])->SetData(i);//The data in each wrapper saves the index in the array
		(arr[j])->SetData(j);
	}
    /* Description:  Allocates a new array with new size, copies elements from old array to the new one,
                     and then saves the new array.
                     This method is being called when array is full or current size
                     equals to max_size * SHRINK_FACTOR
	* Input:         new_size - the size of new allocated array
	* Output:        Allocates a bigger array, elements will be copied to new
                     one in the same order (indices won't change), deallocates old array.
	* Return Values: None.
	*/
    void resize(int new_size) {
        if (!arr) return;
        max_size = new_size;
        Wrapper<int>** new_arr = new Wrapper<int>*[max_size];
        for (int i = 0; i < size; i++)
            new_arr[i] = arr[i]; //Note: Assignment of pointers
        delete[] arr;
        arr = new_arr;
    }
    /* Description:  Sifts down a given element (by his index) to the relevant place
                    in the array. Compares given element with his sons (checks if it has valid sons)
                    If given element is the minimum beyond the three, will do nothing.
                    Else will swap with the minimum between the sons and continue recursively (min-heap)
   * Input:         i - index of wanted element to sift.
   * Output:        Puts element with index i in the current place, updates
                    the indices of changed wrappers (using swap)
   * Return Values: None.
   */
    void siftDown(int i) {
        int left_son = i*2 + 1, right_son = i*2 + 2;
        if (left_son >= size) return;
        int min_index = i;

        if(*arr[i] > *arr[left_son])
            min_index = left_son;
        if((right_son < size) && (*arr[min_index] > *arr[right_son]))
            min_index = right_son;

        if(min_index != i)
        {
            swap(i, min_index);
            //After swap, given element is set at min_index, will continue recursively down the heap.
            siftDown(min_index);
        }
    }
    /* Description:  Sifts up a given element (by his index) to the relevant place
                   in the array. Compares the element to its parent, if parent is
                   bigger, will replace and continue recursively (min-heap)
  * Input:         i - index of wanted element to sift.
  * Output:        Puts element with index i in the current place, updates
                   the indices of changed wrappers (using swap)
  * Return Values: None.
  */
    void siftUp(int i) {
        if (i == 0) return;
        int parent = (i-1)/2;
        //While element i is smaller than his parent, replace and continue
        if (*arr[parent] > *arr[i]) {
            swap(parent, i);
            siftUp(parent);
        }
    }
    /* Description:  Decreases key of given element with index i.
   * Input:         i - index of wanted element to update.
                    val - the new key to set.
   * Output:        Puts element with index i in the current place, updates
                    the indices of changed wrappers (using swap)
   * Return Values: None.
   */
    void decKey(int i, int val) {
        if (!arr) return;
        //Updates the key of element i and then sifts up to relevant place.
		arr[i]->SetKey(val);
        siftUp(i);
    }
    /* Description:  Deletes the minimum element from heap.
   * Input:         None.
   * Output:        Deletes the minimum, updates the array size and allocates a
                    new array (using resize) if needed.
   * Return Values: None.
   */
    void DelMin() {
        if (size == 0) return;
        swap(0, size - 1);//Swaps root with last leaf, as learnt in class
        delete arr[size - 1];
        size--;
        siftDown(0);
        if (size <= max_size * SHRINK_FACTOR) //Checks if resize is needed
            resize(max_size/FACTOR);
    }
public:
    /* Description:  Cto'r
   * Input:         input_arr - array of pointers to class Wrapper<int>.
                    Each wrapper saves a key and additional data (index of element in array)
                    size - number of elements in input_arr
   * Output:        Allocates a new array and copies the pointers. Then, sifts down
                    the elements in the array in DESC order as learnt at class.
   * Return Values: None.
   */
    Heap(Wrapper<int>** input_arr, int size) {
        arr = new Wrapper<int>*[size * FACTOR];
        this->size = size;
        max_size = size * FACTOR;
        for (int i = 0; i < size; i++) {
            arr[i] = input_arr[i];
            arr[i]->SetData(i);//Sets each element data to be current index.
        }
        for (int i = size - 1; i >= 0; i--)
            siftDown(i);
    }
    /* Description:  Returns the minimum element in heap.
   * Input:         None.
   * Output:        None.
   * Return Values: The minimum element (will be set at cell #0), not the pointer.
   */
    Wrapper<int>& GetMin() {
        return *arr[0];
    }
    /* Description:  Inserts a new element (using his pointer) to heap.
   * Input:         value - pointer to Wrapper<int>
   * Output:        Inserts the element to heap, updates the indices and allocates
                    a new array if resize is needed
   * Return Values: None.
   */
    void Insert(Wrapper<int>* value) {
        value->SetData(size);
        arr[size++] = value;
        siftUp(size-1);
        if (size >= max_size)
            resize(max_size * FACTOR);
    }
    /* Description:  Deletes element with index i
   * Input:         i - index of wanted element to be deleted from heap
   * Output:        Deletes the element and rearranges the heap if needed/
   * Return Values: None.
   */
    void DelKey(int i) {
        Wrapper<int> min = GetMin();
        //Decreases the key to be the new min, so it will become the heap's root
        decKey(i, min.GetKey()-1);
        DelMin();
    }
    /* Description:   Dto'r.
	*/
    ~Heap() {
		for (int i = 0; i < size; i++)
		{
			if(arr[i])
				delete arr[i];
		}
        delete[] arr;
    }
};


#endif //DSHW1_HEAP_H
