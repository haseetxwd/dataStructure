#pragma once

#include "listNode.h" //�����б�ڵ���
#include <random>

template <typename T> class List { //�б�ģ����

protected:
	int _size; ListNode<T>* header; 
	ListNode<T>* trailer; //��ģ��ͷ�ڱ���β�ڱ�


	void init(); //�б���ʱ�ĳ�ʼ��
	int clear(); //������нڵ�
	void selectionSort(ListNode<T>*, int); //�Դ�p��ʼ������n���ڵ�ѡ������
	void insertionSort(ListNode<T>*, int); //�Դ�p��ʼ������n���ڵ��������

public:
	// ���캯��
	List() { init(); } //Ĭ��
	List(List<T> const& L); //���帴���б�L
	List(List<T> const& L, Rank r, int n); //�����б�L���Ե�r�����n��
	List(ListNode<T>* p, int n); //�����б�����λ��p���n��
	// ��������
	~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
	// ֻ�����ʽӿ�
	Rank size() const { return _size; } //��ģ
	bool empty() const { return _size <= 0; } //�п�
	T& operator[] (Rank r) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
	ListNode<T>* first() const { return header->succ; } //�׽ڵ�λ��
	ListNode<T>* last() const { return trailer->pred; } //ĩ�ڵ�λ��
	bool valid(ListNode<T>* p) //�ж�λ��p�Ƿ����Ϸ�
	{
		return p && (trailer != p) && (header != p);
	} //��ͷ��β�ڵ��ͬ��NULL
	int disordered() const; //�ж��б��Ƿ�������
	ListNode<T>* find(T const& e) const //�����б����
	{
		return find(e, _size, trailer);
	}
	ListNode<T>* find(T const& e, int n, ListNode<T>* p) const; //�����������
	ListNode<T>* search(T const& e) const //�����б����
	{
		return search(e, _size, trailer);
	}
	ListNode<T>* search(T const& e, int n, ListNode<T>* p) const; //�����������
	ListNode<T>* selectMax(ListNode<T>* p, int n); //��p����n-1�������ѡ�������
	ListNode<T>* selectMax() { return selectMax(header->succ, _size); } //���������
	// ��д���ʽӿ�
	ListNode<T>* insertAsFirst(T const& e); //��e�����׽ڵ����
	ListNode<T>* insertAsLast(T const& e); //��e����ĩ�ڵ����
	ListNode<T>* insertA(ListNode<T>* p, T const& e); //��e����p�ĺ�̲���
	ListNode<T>* insertB(ListNode<T>* p, T const& e); //��e����p��ǰ������
	T remove(ListNode<T>* p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); } //ȫ�б�鲢
	void sort(ListNode<T>* p, int n); //�б���������
	void sort() { sort(first(), _size); } //�б���������
	int deduplicate(); //����ȥ��
	int uniquify(); //����ȥ��
	void reverse(); //ǰ���ã�ϰ�⣩
	// ����
	void traverse(void(*) (T&)); //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
	template <typename VST> //������
	void traverse(VST&); //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�
}; //List
template <typename T>
void List<T>::init() {
	_size = 0;
	header = new ListNode<T>;
	trailer = new ListNode<T>;

}

template <typename T>
int List<T>::clear() {
	Rank temp = _size;
	_size = 0;

	ListNode<T>* first = header->succ;
	ListNode<T>* second = header;

	while (1) {
		if (first) break;
		delete second;
		second = first;
		first = first->succ;

	}
	header->succ = trailer;
	trailer->pred = header;

	return temp;
}

template <typename T>
void List<T>::selectionSort(ListNode<T>* p, int n) {
	int i = 0;
	auto last = trailer;
	while (i < n) {
		auto temp = selectMax(p, n - i);
		last->insertB(temp->data);
		last = last->pred;
		i++;
		remove(temp);
	}
}



template <typename T>
void List<T>::insertionSort(ListNode<T>* p, int n) {
	if (n < 2) return;
	auto first = p->succ;
	for (auto second = p; n--; first = first->succ) {
		while (second->data < first->data) {
			second = second->succ;
		}
		insertB(second, first->data);
		first = first->pred;
		remove(first->succ);
	}
}

template <typename T>
List<T>::List(List<T> const& L) {
	List(L, 0, _size);
}

template <typename T>
List<T>::List(List<T> const& L, Rank r, int n) {
	init();
	_size = n;
	auto pNode = header;
	auto pNodeAnthour = L.header;
	while (r--) pNodeAnthour = pNodeAnthour->succ;
	while (n--) {
		pNode = pNode->insertAsSucc(pNodeAnthour->data);
		pNodeAnthour = pNodeAnthour->succ;

	}
}

template <typename T>
List<T>::List(ListNode<T>* p, int n) {
	init();
	_size = n;
	auto pNode = header;
	auto pNodeAnthour = p;
	while (n--) {
		pNode = pNode->insertAsSucc(pNodeAnthour->data);
		pNodeAnthour = pNodeAnthour->succ;

	}

}

template <typename T>
List<T>::~List() {
	clear();
	delete header;
	delete trailer;
}

template <typename T>
T& List<T>::operator[](Rank r) const {
	auto p = header;
	while (r--) {
		p = p->succ;
	}
	return *p;
}

template <typename T>
int List<T>::disordered() const {
	if (_size < 2) return true;
	auto flag = true;
	auto p = header->succ;
	auto n = _size - 1;
	while (n--) {
		if (p->data > p->succ->data) {
			flag = false; break;
		}
		p = p->succ;
	}
	if (flag) return true;

	flag = true;
	p = header->succ;
	n = _size - 1;
	while (n--) {
		if (p->data < p->succ->data) {
			flag = false; break;
		}
		p = p->succ;
	}
	return flag;

}

template <typename T>
ListNode<T>* List<T>::find(T const& e, int n, ListNode<T>* p) const {
	ListNode<T>* target = nullptr;
	while (n--) {
		if (p->data == e) {
			target = p;
			break;
		}
		p = p->succ;
	}
	return target;
}

template <typename T>
ListNode<T>* List<T>::search(T const& e, int n, ListNode<T>* p) const {
	return find(e, n, p);
}

template <typename T>
ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n) {
	if (n < 1) return nullptr;
	auto key = p;
	T temp = p->data;
	while (--n) {
		if (p->data >= temp) {
			temp = p->data;
			key = p;
		}
		p = p->succ;
	}
	return key;
}

template <typename T>
ListNode<T>* List<T>::insertAsFirst(T const& e) {
	return header->insertAsSucc(e);
}

template <typename T>
ListNode<T>* List<T>::insertAsLast(T const& e) {
	return header->insertAsPred(e);
}

template <typename T>
ListNode<T>* List<T>::insertA(ListNode<T>* p, T const& e) {
	return p->insertAsSucc(e);
}

template <typename T>
ListNode<T>* List<T>::insertB(ListNode<T>* p, T const& e) {
	return p->insertAsPred(e);
}

template <typename T>
T List<T>::remove(ListNode<T>* p) {
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	T temp = p->data;
	delete p;
	return temp;
}

template <typename T>
void List<T>::sort(ListNode<T>* p, int n) {
	selectionSort(p, n);
}


template <typename T>
int List<T>::deduplicate() {
	int n = 0;
	if (_size < 2) return 0;
	auto first = header->succ->succ;
	while (first != trailer) {
		auto second = header->succ;
		while (second != first) {
			second = second->succ;
			if (second->pred->data == first->data) {
				n++;
				remove(second->pred);
			}
		}
		first = first->succ;
	}
	return n;
}

template <typename T>
int List<T>::uniquify() {
	if (_size < 2) return 0;
	int n = 0;
	auto first = header->succ->succ;
	auto second = header->succ;
	while (!first) {
		if (first->data == second->data) {
			first = first->succ;
			remove(first->pred);
			n++;
		}
		else {
			second = first;
			first = first->succ;			
		}
	}
	return n;
}

template <typename T>
void List<T>::reverse() {
	if (_size < 2)return;
	auto head = header->succ;
	auto trail = trailer->pred;
	while (head < trail) {
		T temp = head->data;
		head->data = trail->data;
		trail->data = temp;
	}

}

template <typename T>
void List<T>::traverse(void(*p)(T&)) {
	int n = _size;
	auto pNode = header->succ;
	while (n--) {
		p(pNode->data);
		pNode->succ;
	}
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST& visit) {
	int n = _size;
	auto pNode = header->succ;
	while (n--) {
		visit(pNode->data);
		pNode->succ;
	}
}