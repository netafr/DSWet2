#ifndef _UTILS_H_
#define _UTILS_H_
#define FACTOR 2
template <Class T>
T* resize(T* arr, int size, int* newSize) {
	if (!arr) {
		return NULL;
	}
	T* outArr = new T[size*FACTOR];
	for (int i = 0; i < size; ++i)
	{
		outArr[i] = arr[i];
	}
	delete arr;
	*newSize = FACTOR * size;
	return outArr;
}

template <Class T>
T* shrink(T* arr, int size, int* newSize) {
	if (!arr) {
		return NULL;
	}
	T* outArr = new T[size/FACTOR];
	for (int i = 0; i < size; ++i)
	{
		outArr[i] = arr[i];
	}
	delete arr;
	*newSize = size / FACTOR;
	return outArr;
}


#endif 

