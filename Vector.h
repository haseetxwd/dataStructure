#pragma once
#include <random>

typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template <typename T> class Vector { //����ģ����
protected:
	Rank _size; int _capacity;  T* _elem; //��ģ��������������
	void copyFrom(T const* A, Rank lo, Rank hi); //������������A[lo, hi)
	void expand(); //�ռ䲻��ʱ����
	void shrink(); //װ�����ӹ�Сʱѹ��
	bool bubble(Rank lo, Rank hi); //ɨ�轻��
	void bubbleSort(Rank lo, Rank hi); //���������㷨
	Rank max(Rank lo, Rank hi); //ѡȡ���Ԫ��
	void selectionSort(Rank lo, Rank hi); //ѡ�������㷨
	void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨
	void mergeSort(Rank lo, Rank hi); //�鲢�����㷨
//	Rank partition(Rank lo, Rank hi); //��㹹���㷨
//	void quickSort(Rank lo, Rank hi); //���������㷨
//	void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩
public:
	// ���캯��
	Vector(int c, int s, T v);//����Ϊc����ģΪs������Ԫ�س�ʼΪv
	//s<=c
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����
	// ��������
	~Vector() { delete[] _elem; } //�ͷ��ڲ��ռ�
	// ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	bool empty() const { return !_size; } //�п�
	int disordered() const; //�ж������Ƿ�������
	Rank find(T const& e) const { return find(e, 0, _size); } //���������������
	Rank find(T const& e, Rank lo, Rank hi) const; //���������������
	Rank search(T const& e) const //���������������
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi) const; //���������������
	// ��д���ʽӿ�
	T& operator[] (Rank r) const; //�����±������������������������ʽ���ø�Ԫ��
	Vector<T> & operator= (Vector<T> const&); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	T remove(Rank r); //ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��
	Rank insert(Rank r, T const& e); //����Ԫ��
	Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
	void sort(Rank lo, Rank hi); //��[lo, hi)����
	void sort() { sort(0, _size); } //��������
	void unsort(Rank lo, Rank hi); //��[lo, hi)����
	void unsort() { unsort(0, _size); } //��������
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��
	// ����
	void traverse(void(*) (T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
	template <typename VST> void traverse(VST&); //������ʹ�ú������󣬿�ȫ�����޸ģ�
}; //Vector
template <typename T>
int Vector<T>::deduplicate() {
	if (_size < 2) return 0;
	Rank oldSize = _size;
	for (int i = 1; i <= _size;) {
		if (find(_elem[i], 0, i))
			remove(i);
		else i++;
	}
	return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify() {
	if (_size < 2) return 0;
	Rank oldSize = _size;
	Rank a = 0;
	Rank b = 1;
	while (b < _size) {
		if (_elem[b] = _elem[b - 1]) b++;
		else {
			remove(a + 1, b);
			a++;
			b = a + 1;
		}
	}
	remove(a + 1, b);
	return oldSize - _size;
	
}

template <typename T>
void Vector<T>::traverse(void(*p)(T&)) {
	for (int i = 0; i < _size; i++) {
		p(_elem[i]);
	}
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &p) {
	for (int i = 0; i < _size; i++) {
		p(_elem[i]);
	}
}

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_size = hi - lo;
	_capacity =2 * _size;
	_elem = new T[_capacity];
	for (int i = 0; i < _size; i++)
		_elem[i] = A[lo + i];
}

template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;
	T *A = _elem;
	_elem = new T[2 * _capacity];
	for (int i = 0; i < _size; i++)
		_elem[i] = A[i];

	delete[] A;
}

template <typename T>
void Vector<T>::shrink() {
	if (_capacity < 2 * DEFAULT_CAPACITY) return;
	if (_size * 4 < _capacity) {
		T *A = _elem;
		_capacity = 2 * _size;
		_elem = new T[_capacity];
		for (int i = 0; i < _size; i++)
			_elem[i] = A[i];

		delete[] A;
	}
}

template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
	bool sorted = true;
	for (int i = lo + 1; i < hi; i++) {
		if (_elem[i] < _elem[i - 1]) {
			sorted = false;
			T a = _elem[i];
			_elem[i] = _elem[i - 1];
			_elem[i - 1] = a;
		}
	}
	return sorted;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
	for (int i = hi; i > lo; i--)
		if (bubble(lo, i))
			return;
}

template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
	T tempMax = _elem[lo];
	Rank tempMaxIndex = lo;
	for (int i = lo + 1; i < hi; i++) {
		if (_elem[i] > tempMax) {
			tempMax = _elem[i];
			tempMaxIndex = i;
		}
	}

	return tempMaxIndex;
}

template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
	for (int i = hi; i > lo; i--) {
		Rank tempMaxIndex = max(lo, i);
		T tempMax = _elem[tempMaxIndex];
		_elem[tempMaxIndex] = _elem[i - 1];
		_elem[i - 1] = tempMax;
	}

}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	T *A = new T[mi - lo];
	for (int i = 0; i < hi - lo; i++)
		A[i] = _elem[lo + i];
	int lb = mi - lo;//ǰ������
	int lc = hi - mi;//��������

	for (int i = 0, j = 0, k = 0; i < hi - lo; i++) {
		if (j < lb && (k >= lc || A[j] > _elem[mi + k])) {
			_elem[i] = A[j];
			j++;
		}
		if (k < lc && (j >= lb || _elem[mi + k] > A[j])) {
			_elem[i] = _elem[mi + k];
			k++;
		}
	}
	delete[] A;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return;
	Rank mi = (lo + hi) / 2;
	mergeSort(lo, mi);
	mergeSort(mi, hi);
	merge(lo, mi, hi);

}

template <typename T>
Vector<T>::Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
	_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
}

template <typename T>
int Vector<T>::disordered() const {
	int inverseNumber = 0;
	for (int i = 1; i < _size; i++) {
		if (_elem[i] > _elem[i - 1])
			inverseNumber++;
	}
	return inverseNumber;
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
	for (int i = lo; i < hi; i++) {
		if (e == _elem[i])
			return i;
	}
	return -1;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
	while (lo < hi) {
		Rank mi = lo + static_cast<int>(0.618 * (hi - lo));
		if (e < _elem[mi]) hi = mi;
		else if (e > _elem[mi]) lo = mi + 1;
		else return mi;
	}
	return -1;
}

template <typename T>
T& Vector<T>::operator[](Rank r) const {
	return _elem[r];
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& A) {
	delete[] _elem;
	copyFrom(A._elem, 0, A._size);
	return *this;
}

template <typename T>
T Vector<T>::remove(Rank r) {
	T a = _elem[r];
	remove(r, r+1);
	return a;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (hi - lo < 1) return 0;
	for (int i = 0; i < _size - hi; i++)
		_elem[lo + i] = _elem[hi + i];
	shrink();
	return hi - lo;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;

	return r;
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
	mergeSort(lo, hi);
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	for (int i = hi - 1 ; i > lo; i--) {
		int length = hi - lo;
		int x = rand() % length;
		T a = _elem[lo + x];
		_elem[lo + x] = _elem[i];
		_elem[i] = a;
	}
}