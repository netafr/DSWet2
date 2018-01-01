//
// Created by Oren Jacobian Pana on 12/28/2017.
//

#ifndef DSHW1_HEAP_H
#define DSHW1_HEAP_H
#define FACTOR 2
#define SHRINK_FACTOR 0.25
#include "Wrapper.h"
class Heap{

    Wrapper<int>** arr;
    int size;
    int max_size;

	void swap(int i, int j) {
		if (i < 0 || i >= size || j < 0 || j >= size) return;
		Wrapper<int>* temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
		(arr[i])->SetData(i);
		(arr[j])->SetData(j);
	}
    void resize() {
        if (!arr) return;
        max_size *= FACTOR;
        Wrapper<int>** new_arr = new Wrapper<int>*[max_size];
		for (int j = 0; j < max_size; ++j) {
			new_arr[j] = NULL;
		}
        for (int i = 0; i < size; i++)
            new_arr[i] = arr[i];
        delete[] arr;
        arr = new_arr;
    }
    void shrink() {
        if (!arr) return;
        max_size /= FACTOR;
        Wrapper<int>** new_arr = new Wrapper<int>*[max_size];
		for (int j = 0; j < max_size; ++j) {
			new_arr[j] = NULL;
		}
        for (int i = 0; i < size; i++)
            new_arr[i] = arr[i];
        delete[] arr;
        arr = new_arr;
    }
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
            siftDown(min_index);
        }
    }
    void siftUp(int i) {
        if (i == 0) return;
        int parent = (i-1)/2;
        if (*arr[parent] > *arr[i]) {
            swap(parent, i);
            siftUp(parent);
        }
    }
    void decKey(int i, int val) {
        if (!arr) return;
		arr[i]->SetKey(val);
        siftUp(i);
    }
public:
    Heap(Wrapper<int>** input_arr, int size) {
        arr = new Wrapper<int>*[size * FACTOR];
        this->size = size;
        max_size = size * FACTOR;
        for (int i = 0; i < size; i++) {
            arr[i] = input_arr[i];
            arr[i]->SetData(i);
        }
        for (int i = size - 1; i >= 0; i--)
            siftDown(i);
    }
    Wrapper<int>& GetMin() {
        return *arr[0];
    }
    void DelMin() {
        if (size == 0) return;
		swap(0, size - 1);
		delete arr[size - 1];
        size--;
        siftDown(0);
        if (size <= max_size * SHRINK_FACTOR)
            shrink();
    }
    void Insert(Wrapper<int>* value) {
        arr[size++] = value;
        siftUp(size-1);
        if (size >= max_size)
            resize();
    }
    void DelKey(int i) {
        Wrapper<int> min = GetMin();
        decKey(i, min.GetKey()-1);
        DelMin();
    }
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
