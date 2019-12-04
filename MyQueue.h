#pragma once
#include<stdlib.h>
template<typename T>
class QNode
{
private:
	T data;
	QNode *next;
public:
	QNode() :data(), next(nullptr) {}
	QNode(const T& data) :data(data), next(nullptr) {}
	QNode(const QNode& rhs) :data(rhs.data), next(rhs.next) {}
	QNode *getNext() { return next; }
	void setNext( QNode *next) { this->next = next; }
	T getData() { return data; }
	void setData(const T&data) { this->data = data; }
};
template<typename T>
class MyQueue
{
private:
	QNode<T> *head, *rear;
	int size;
public:
	enum Status
	{
		OVERFLOW_=-2,
		INFEASIBLE=-1,
		ERROR=0,
		FALSE=0,
		TRUE=1,
		OK=1
	};
	MyQueue():head(new QNode<T>()),rear(head),size(0){}
	~MyQueue(){
		size = 0;
		QNode<T> *p = head;
		while (p!=nullptr)
		{
			QNode<T> *p1 = p;
			p = p->getNext();
			delete p1;
		}
		rear = nullptr;
		head = nullptr;
	}
	Status push(const T&data)	{
		QNode<T> *newNode = new QNode<T>(data);
		if (newNode == nullptr)
			exit(OVERFLOW_);
		rear->setNext(newNode);
		rear = rear->getNext();
		size++;
		return OK;
	}
	Status front(T&data) {
		if (head->getNext() == nullptr)
			return ERROR;
		QNode<T>* q = head->getNext();
		data = q->getData();
		return OK;
	}
	Status pop() {
		if (head->getNext() == nullptr)
			return ERROR;
		if (head->getNext() == rear)
		{
			head->setNext(rear->getNext());
			delete rear;
			rear = head;
		}
		else
		{
			QNode<T> *p = head->getNext();
			head->setNext(p->getNext());
			delete p;
		}
		size--;
		return OK;
	}
	Status empty(){
		if (head == rear)
			return TRUE;
		else
			return FALSE;
	}
	Status clear(){
		QNode<T> *p = head->getNext();
		if (p == nullptr)
			return ERROR;
		while (p!=nullptr)
		{
			QNode<T> *p1 = p;
			p = p->getNext();
			delete p1;
		}
		head->setNext(nullptr);
		size = 0;
		rear = head;
		return OK;
	}
	int length()
	{
		return size;
	}
};