#ifndef _WRAPPER_
#define _WRAPPER_

template <class T>
class Wrapper {
	T data;
	int key;

public:
	Wrapper() : data(), key() {}

	Wrapper(const T& data, int key) : data(data), key(key) {}

	Wrapper(const Wrapper& wrap) : data(wrap.data), key(wrap.key) {}

	T& GetData() {
		return this->data;
	}

	int GetKey() {
		return this->key;
	}

	void SetData(int data) {
		this->data = data;
	}

	void SetKey(int key) {
		this->key = key;
	}

	bool operator==(const Wrapper& wrap) const {
		return (key == wrap.key);
	}

	bool operator<(const Wrapper& wrap) const {
		return (key < wrap.key);
	}

	bool operator>(const Wrapper& wrap) const {
		return (key > wrap.key);
	}

	~Wrapper() {}
};
#endif