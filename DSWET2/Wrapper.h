#ifndef _WRAPPER_
#define _WRAPPER_
template <class T>
class Wrapper {
	T data;
	int key;
public:
	Wrapper() : data(), key() {}
	Wrapper(const T& data, int key) : data(data), key(key) {}
	Wrapper(const Wrapper& wrap) : data(wrap.GetData()), key(wrap.GetKey()) {}
	const T& GetData() const {
		return this->data;
	}
	int GetKey() const {
		return this->key;
	}
	bool operator==(const Wrapper& wrap) const {
		return (data == wrap.GetKey());
	}
	bool operator<(const Wrapper& wrap) const {
		return (data < wrap.GetKey());
	}
	bool operator>(const Wrapper& wrap) const {
		return (data > wrap.GetKey());
	}
	~Wrapper() {}
};
#endif