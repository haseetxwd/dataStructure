#pragma once

typedef int Rank; //秩


template <typename T> class ListNode { //列表节点模板类（以双向链表形式实现）
public:
	// 成员
	T data; 
	ListNode<T>* pred; 
	ListNode<T>* succ; //数值、前驱、后继
	// 构造函数
	ListNode() {}//针对header和trailer的构造
	explicit ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr)
		: data(e), pred(p), succ(s) {} //默认构造器
	// 操作接口
	ListNode<T>* insertAsPred(T const& e); //紧靠当前节点之前插入新节点
	ListNode<T>* insertAsSucc(T const& e); //紧随当前节点之后插入新节点
};

template <typename T>
ListNode<T>* ListNode<T>::insertAsPred(T const& e) {
	auto newNode = new ListNode(e, pred, this);
	pred->succ = newNode;
	pred = newNode;
	return  newNode;
}

template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc(T const& e) {
	auto newNode = new ListNode(e, this, succ);
	succ->pred = newNode;
	succ = newNode;
	return newNode;
}