#pragma once
#include<stdlib.h>
template<typename T>
class SNode
{
private:
	T data;
	SNode *next;
public:
	SNode():data(),next(nullptr){}
	SNode(const T& data):data(data),next(nullptr){}
	SNode(const SNode& rhs):data(rhs.data),next(rhs.next){}
	SNode *getNext() { return next; }
	void setNext( SNode* next) { this->next = next; }
	T getData() { return data; }
	void setData(const T&data) { this->data = data; }
};
template<typename T>
class MyStack
{
private:
	SNode<T> *head;
	int size;
public:
    enum Status
	{
		TRUE=1, FALSE=0, OK=1, ERROR=0, INFEASIBLE=-1, OVERFLOW_=-2
	};
	MyStack():head(new SNode<T>()),size(0){}
	~MyStack(){
		size = 0;
		SNode<T> *p = head;
		while (p!=nullptr)
		{
			SNode<T> *p1 = p;
			p = p->getNext();
			delete p1;
		}
		head = nullptr;
	}
	Status push(const T& data){
		SNode<T> *newNode = new SNode<T>(data);
		if (newNode==nullptr) exit(OVERFLOW_);
		newNode->setNext(head->getNext());
		head->setNext(newNode);
		size++;
		return OK;
	}
	Status top(T&data) {
		if (head->getNext() == nullptr)
			return ERROR;
		SNode<T> *p = head->getNext();
		data = p->getData();
		return OK;
	}
	Status pop() {
		if (head->getNext() == nullptr)
			return ERROR;
		SNode<T> *p = head->getNext();
		head->setNext(p->getNext());
		delete p;
		size--;
		return OK;
	}
	Status empty() {
		if (head->getNext() == nullptr)
			return TRUE;
		else
			return FALSE;
	}
	Status clear() {
		if (head->getNext() == nullptr)
			return ERROR;
		SNode<T> *p = head->getNext();
		while (p!=nullptr)
		{
			SNode<T> *p1 = p;
			p = p->getNext();
			delete p1;
		}
		head->setNext(nullptr);
		size = 0;
		return OK;
	}
	int length() {
		return size;
	}
};
