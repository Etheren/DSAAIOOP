#include <iostream>

class Node								//Class used to modify stack and queues.
{
public:
	Node(int valueNode, Node* nextptr = NULL, Node* prevptr = NULL, int currentpriority = 0)
	{
		value = valueNode;
		next = nextptr;
		prev = prevptr;
	};

	int getVal(void) {
		return value;					//Returns the value currently stored under the name of value
	};

	Node* getNext(void) {				//Returns the value currently stored under the name of next
		return next;
	};

	Node* getPrev(void) {				//Returns the value currently stored under the name of prev
		return prev;					
	};

	void setVal(int valueInput) {		//Sets the value named value equal to an interger value that is passed into the function
		value = valueInput;
	};

	void setPrev(Node* prevptr) {		//Sets the value named prev equal to an value that is passed into the function
		prev = prevptr;
	};

	void setNext(Node* nextptr) {		//Sets the value named next equal to an value that is passed into the function
		next = nextptr;
	};

	int getPriority(void) {				//Returns the value currently stored under the name of priority
		return priority;
	};

	void setPriority(int priorityInput) {				// Function to modify the value under the name of priority
		if (priorityInput <= 0)							// If a value that is equal or less to 0 is passed into the function,
		{
			priority = 1;												// Set the priority value to be equal to 1 instead,
			std::cout << "\nInput Priority too low. Setting to 1\n";	// And output a message to the screen, indicating the input value was too low, and it has been modified to 1
		}
		else if (priorityInput > 10)									//If a value that is greater than 10 is passed into the function,
		{
			priority = 10;												//Set the priority value to be equal to 10 instead,
			std::cout << "\nInput Priority too high. Setting to 10\n";	//And output a message to the screen, indicating the input value was too high, and it has been modified to 10.
		}
		else
		{																//Otherwise, if the input value is between 1 and 10 inclusive,
			priority = priorityInput;									//Set the priority value to be equal to the input
		}
	};

private:
	Node* next;			//Declares the value called next, which is used for queues	
	Node* prev;			//Declares the value called prev, which is also used for queues
	int priority;		//Declares the interger value called priority, which is used to determine priority for our processes
	int value;			//Decalres the interget value called value, which is used to determine the process ID
};

class Stack				//Class declaration which handles stacks
{
public:
	Stack(void) {		// This function is used to initialise a stack
		top = 0;		// This function modifies the value stored under top to be equal to 0.		
	};

	~Stack(void) {};

	void Push(int value) {					//This function is used to push a value onto the top of a stack.
		Node* temp = new Node(value, top);	//This creates a new Node call temp, and makes it the result of the Node function
		top = temp;							//top is then made equal to the value stored under temp
	};

	Node* NodePop(void) {			//This function reassigns the node on the top of the stack to the next value, and returns the value that was previously on top
		Node* temp = top;
		top = temp->getNext();		//This makes the top node the next node in the stack
		return temp;
	};

	int Pop(void) {							//This function deletes the node on the top of the stack, and returns the value.
		int returnValue = 0;				//Declaring the value we will be returning
		if (top != nullptr) {				//If the stack has at least 1 node,
			returnValue = top->getVal();	//Make return value equal to the node that is on top
			Node* temp = top;				//Make a new node called temp, and make it equal to the value that is currently on top
			top = top->getNext();			//Make the top value equal to the node that is the next node on the stack
			delete temp;					//then deallocate the memory that is assigned to the node temp
		}
		else 
		{
			std::cout << "Stack is Empty" << std::endl;		//If the stack is empty, returnValue stays at 0, and a message is output to the screen explaining the stack is empty
		}
		return returnValue;				//Then return the value that is stored under returnValue.		
	}

private:

	Node* top;		//Declaration of a node called top, which is used to keep track of what value is on top of the stack.
};

class Queue			//Class declaration used to handle Queues
{
public:
	Queue(void) {
		front = back = nullptr;		//This function is used to declare
	};

	~Queue(void) {
		while (front != nullptr)	//If the queue is empty and nothing is in front of the queue
		{
			delete NodeDequeue();	//Deallocate the memory that has been assigned to the NodeDequeue function
		}
	}

	void Enqueue(int i, int priority = 0)		//Function that adds a value to the back of the queue, alongside a priority value
	{
		Node* tempValue = new Node(i, back);	//Creates a temporary Node value, and makes it equal to the value of the inputted value.
		back = tempValue;						//makes the back value equal to the value that is stored under tempValue
		if (front == nullptr) front = back;		//If the front of the queue produces a Null pointer, (empty), make the front of the queue equal to the back value
		else
		{										//Otherwise,
			tempValue = back->getNext();		//Make temp value equal to the result of the back's getNext function return
			tempValue->setPrev(back);			//Then move the value that is stored under back, and push that the the back of the queue
		}
		
	};

	int Dequeue(void) {							//Function that removes the front value from the queue
		Node* tempValue = NodeDequeue();		//Create a temporary Node value, and make it equal to the result of the function called NodeDequeue
		int returnValue = tempValue->getVal();	//Create an interger value called returnValue, and make it equal to the result of tempValue's getVal function
		if (front == nullptr) back = front;		//If the front of the queue produces a null pointer (is empty), make the back of the queue equal to the front of the queue
		return returnValue;						//Then finally return the interger that is under returnValue
	}

protected:

	Node* back;						//Node declaration called back, which is used to determine the back of the queue
	Node* front;					//Node declaration called front, which is used to determine the front of the queue

private:

	virtual Node* NodeDequeue(void) {
		Node* temp = front;									//Create a temporary Node value, and make it equal to the value of the front value
		if (front != nullptr)								//If the front of the queue is NOT null, (has at least 1 value), 
		{
			front = front->getPrev();						//Make the front value equal to the result of front's getPrev function
			if (front != nullptr) front->setNext(nullptr);	//If the front of the queue is still NOT null (has at least 1 value), set the front value to be equal to nullptr(Null Pointer)
		}
		return temp;		//Then return the value that is stored under temp
	};
};

class Scheduler : public Queue		//Class declaration used to handle the Scheduler, which also uses the Queue class
{
private:
	
	Node* NodeDequeue(void) {								//Function used to remove the node from the front of the queue.
		Node* temp = front;									//Create a temporary Node value, and make it equal to the value of the front value
		if (front != nullptr)								//If the front of the queue is NOT null, (has at least 1 value), 
		{
			front = front->getPrev();						//Make the front value equal to the result of front's getPrev function
			if (front != nullptr) front->setNext(nullptr);	//If the front of the queue is still NOT null (has at least 1 value), set the front value to be equal to nullptr(Null Pointer)
		}
		return temp;		//Then return the value that is stored under temp
	};

	Node* PriorityScheduler(int noOfProcs) {
		Node* currentVal[1000]; 
		Queue toProcess;
		for (int count = 0; count < noOfProcs; count++)
		{

		}
	}

};

int main()
{
	Stack s;
	Queue q;
	s.Push(10);
	s.Push(20);
	s.Push(30);
	std::cout << s.Pop() << std::endl;
	std::cout << s.Pop() << std::endl;
	std::cout << s.Pop() << std::endl;
	std::cout << s.Pop() << std::endl;
	q.Enqueue(10, 1);
	q.Enqueue(20, 1);
	q.Enqueue(30, 1);
	std::cout << q.Dequeue() << std::endl;
	std::cout << q.Dequeue() << std::endl;
	std::cout << q.Dequeue() << std::endl;
	system("pause");
	return 0;
}