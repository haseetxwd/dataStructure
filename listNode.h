#pragma once

typedef int Rank; //��


template <typename T> class ListNode { //�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
public:
	// ��Ա
	T data; 
	ListNode<T>* pred; 
	ListNode<T>* succ; //��ֵ��ǰ�������
	// ���캯��
	ListNode() {}//���header��trailer�Ĺ���
	explicit ListNode(T e, ListNode<T>* p = nullptr, ListNode<T>* s = nullptr)
		: data(e), pred(p), succ(s) {} //Ĭ�Ϲ�����
	// �����ӿ�
	ListNode<T>* insertAsPred(T const& e); //������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNode<T>* insertAsSucc(T const& e); //���浱ǰ�ڵ�֮������½ڵ�
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