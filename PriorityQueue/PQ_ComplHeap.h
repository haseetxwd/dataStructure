#pragma once
#include  <iostream>

typedef int Rank;

template <typename T> class PQ_ComplHeap {

	int _size;
	int _capacity;
	T* _elem;

	inline Rank parent(Rank n) { return (n - 1) / 2; }
	inline Rank lChild(Rank n) { return n * 2 + 1; }
	inline Rank rChild(Rank n) { return n * 2 + 2; }

	inline bool parentValid(Rank n) { return n > 0; }
	inline bool lChlidVaild(Rank n) { return n * 2 + 1 < _size; }
	inline bool rChlidVaild(Rank n) { return n * 2 + 2 < _size; }
	inline void swap(Rank a, Rank b) { T temp = _elem[b]; _elem[b] = _elem[a]; _elem[a] = temp; }



	Rank lastInternal();
	void expand();
	void copyFrom(T* p, Rank lo, Rank hi);
	Rank percolateUP(Rank n);
	Rank percolateDown(Rank n);
	void heapity();//structure heap

public:
	PQ_ComplHeap();
	PQ_ComplHeap(T* p, int size);
	PQ_ComplHeap(T* p, Rank lo, Rank hi);
	int size();
	void insert(T e);
	T getMax();
	void delMax();
	void test();
};

template <typename T>
Rank PQ_ComplHeap<T>::lastInternal() {
	auto temp = 2;
	auto i = 0;
	while (1){
		if (_size < temp) break;
		temp *= 2;
		i++;
	}
	return temp / 2 - 2;
}

template <typename T>
void PQ_ComplHeap<T>::expand() {
	if (_size == _capacity) {
		T* temp = new T[_size * 2];
		for (auto i = 0; i < _size; i++)
			temp[i] = _elem[i];
		_capacity = _size * 2;
		delete[] _elem;
		_elem = temp;
		temp = nullptr;
	}
}

template <typename T>
void PQ_ComplHeap<T>::copyFrom(T* p, Rank lo, Rank hi) {
	_size = hi - lo;
	_capacity = _size * 2;
	_elem = new T[_capacity];
	for (auto i = 0; i < hi - lo; i++)
		_elem[i] = p[lo + i];
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateUP(Rank n) {
	while (parentValid(n)) {
		if (_elem[parent(n)] > _elem[n]) break;
		swap(n, parent(n));
		n = parent(n);
	}
	return n;
}

template <typename T>
Rank PQ_ComplHeap<T>::percolateDown(Rank n) {
	while (1){
		if (rChlidVaild(n)) {
			Rank temp = _elem[rChild(n)] > _elem[lChild(n)] ? rChild(n) : lChild(n);
			if (_elem[n] < _elem[temp])
				swap(n, temp), n = temp;
			else break;
		}
		else if (lChlidVaild(n)) {
			if (_elem[lChild(n)] < _elem[n]) break;
			swap(n, lChild(n));
			n = lChild(n);
		}
		else
			break;
	}
	return n;
	
}

template <typename T>
void PQ_ComplHeap<T>::heapity() {
	if (_size < 2) return;

	for (auto i = lastInternal(); i >= 0; i--)
		percolateDown(i);
}



template <typename T>
PQ_ComplHeap<T>::PQ_ComplHeap() {
	_size = 0;
	_elem = new T[3];
	_capacity = 3;
}

template <typename T>
PQ_ComplHeap<T>::PQ_ComplHeap(T* p, int size) {
	copyFrom(p, 0, size);
	heapity();
}

template <typename T>
PQ_ComplHeap<T>::PQ_ComplHeap(T* p, Rank lo, Rank hi) {
	copyFrom(p, lo, hi);
	heapity();
}

template <typename T>
int PQ_ComplHeap<T>::size() {
	return _size;
}

template <typename T>
void PQ_ComplHeap<T>::insert(T e) {
	expand();
	_elem[_size] = e;
	_size++;
	percolateUP(_size-1);

	
}

template <typename T>
T PQ_ComplHeap<T>::getMax() {
	return _elem[0];
}

template <typename T>
void PQ_ComplHeap<T>::delMax() {
	if (_size){
		_size--;
		_elem[0] = _elem[_size];
		percolateDown(0);
	}	
}

template <typename T>
void PQ_ComplHeap<T>::test() {
	auto a = _size;
	while (a--) {
		std::cout << getMax() << std::endl;
		delMax();
	}
}