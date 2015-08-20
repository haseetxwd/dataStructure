#pragma once

#include "listNode.h" //引入列表节点类
#include <random>

template <typename T> class List { //列表模板类

protected:
	int _size; ListNode<T>* header; 
	ListNode<T>* trailer; //规模、头哨兵、尾哨兵


	void init(); //列表创建时的初始化
	int clear(); //清除所有节点
	void selectionSort(ListNode<T>*, int); //对从p开始连续的n个节点选择排序
	void insertionSort(ListNode<T>*, int); //对从p开始连续的n个节点插入排序

public:
	// 构造函数
	List() { init(); } //默认
	List(List<T> const& L); //整体复制列表L
	List(List<T> const& L, Rank r, int n); //复制列表L中自第r项起的n项
	List(ListNode<T>* p, int n); //复制列表中自位置p起的n项
	// 析构函数
	~List(); //释放（包含头、尾哨兵在内的）所有节点
	// 只读访问接口
	Rank size() const { return _size; } //规模
	bool empty() const { return _size <= 0; } //判空
	T& operator[] (Rank r) const; //重载，支持循秩访问（效率低）
	ListNode<T>* first() const { return header->succ; } //首节点位置
	ListNode<T>* last() const { return trailer->pred; } //末节点位置
	bool valid(ListNode<T>* p) //判断位置p是否对外合法
	{
		return p && (trailer != p) && (header != p);
	} //将头、尾节点等同于NULL
	int disordered() const; //判断列表是否已排序
	ListNode<T>* find(T const& e) const //无序列表查找
	{
		return find(e, _size, trailer);
	}
	ListNode<T>* find(T const& e, int n, ListNode<T>* p) const; //无序区间查找
	ListNode<T>* search(T const& e) const //有序列表查找
	{
		return search(e, _size, trailer);
	}
	ListNode<T>* search(T const& e, int n, ListNode<T>* p) const; //有序区间查找
	ListNode<T>* selectMax(ListNode<T>* p, int n); //在p及其n-1个后继中选出最大者
	ListNode<T>* selectMax() { return selectMax(header->succ, _size); } //整体最大者
	// 可写访问接口
	ListNode<T>* insertAsFirst(T const& e); //将e当作首节点插入
	ListNode<T>* insertAsLast(T const& e); //将e当作末节点插入
	ListNode<T>* insertA(ListNode<T>* p, T const& e); //将e当作p的后继插入
	ListNode<T>* insertB(ListNode<T>* p, T const& e); //将e当作p的前驱插入
	T remove(ListNode<T>* p); //删除合法位置p处的节点,返回被删除节点
	void merge(List<T>& L) { merge(first(), size, L, L.first(), L._size); } //全列表归并
	void sort(ListNode<T>* p, int n); //列表区间排序
	void sort() { sort(first(), _size); } //列表整体排序
	int deduplicate(); //无序去重
	int uniquify(); //有序去重
	void reverse(); //前后倒置（习题）
	// 遍历
	void traverse(void(*) (T&)); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
	template <typename VST> //操作器
	void traverse(VST&); //遍历，依次实施visit操作（函数对象，可全局性修改）
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