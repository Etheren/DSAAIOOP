class Node
{
public:
	Node(int value, Node* nextptr = NULL, Node* prevptr = NULL, int currentpriority = 0);

	int getVal(void);

	Node* getNext(void);

	Node* getPrev(void);

	void setVal(int value);

	void setPrev(Node* prevptr);

	void setNext(Node* nextptr);

	int getPriority(void);

	void setPriority(int priority);

private:
	Node* next;
	Node* prev;
	int priority;
	int value;
};

class Stack
{
public:
	Stack(void);

	~Stack(void);

	void Push(int value);

	Node* NodePop(void);

	int Pop(void);

private:

	Node* top;
};

class Queue
{
public:
	Queue(void);

	~Queue(void);

	void Enqueue(int i, int priority = 0);

	int Dequeue(void);

protected:

	Node* back;
	Node* front;

private:

	virtual Node* NodeDequeue(void);
};


class Scheduler : public Queue
{
private:

	Node* NodeDequeue(void);

};
