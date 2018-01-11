#include <iostream>

class Node								//Class used to modify stack and queues.
{
public:
	Node(int valueNode, Node* nextptr = NULL, Node* prevptr = NULL, int currentpriority = 0)	//Function used to construct Nodes
	{
		value = valueNode;				//Make value equal to the inputted value called valueNode
		next = nextptr;					//Make next equal to the inputted value called nextptr
		prev = prevptr;					//make prev equal to the inputted value called prevptr
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
	Stack(void) {		// This function is used to construct a stack
		top = 0;		// This function modifies the value stored under top to be equal to 0.		
	};

	~Stack(void) {};	//This function is used to destruct a stack

	void Push(int value) {					//This function is used to push a value onto the top of a stack.
		Node* temp = new Node(value, top);	//This creates a new Node call temp, and makes it the result of the Node function
		top = temp;							//top is then made equal to the value stored under temp
	};

	Node* NodePop(void) {			//This function reassigns the node on the top of the stack to the next value, and returns the value that was previously on top
		Node* temp = top;			//Declare a new node called temp, and make it equal to the node that is on top of the stack
		top = temp->getNext();		//This makes the top node the next node in the stack
		return temp;				//Return the node that is stored under temp
	};

	int Pop(void) {							//This function deletes the node on the top of the stack, and returns the value.
		int returnValue = 0;				//Declaring the value we will be returning
		if (top != nullptr) {				//If the stack has at least 1 node,
			returnValue = top->getVal();	//Make return value equal to the node that is on top
			Node* temp = top;				//Make a new node called temp, and make it equal to the value that is currently on top
			top = top->getNext();			//Make the top value equal to the node that is the next node on the stack
			delete temp;					//then deallocate the memory that is assigned to the node temp
		}
		else								//Otherwise...
		{
			std::cout << "Stack is Empty, Outputting 0" << std::endl;		//If the stack is empty, returnValue stays at 0, and a message is output to the screen explaining the stack is empty
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
		front = back = nullptr;		//This function is used to construct a queue
	};

	~Queue(void) {
		while (front != nullptr)	//This function is is used to destruct a queue
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
		queueSize += 1;							//Increment the value queueSize by 1
	};

	int Dequeue(void) {							//Function that removes the front value from the queue
		Node* tempValue = NodeDequeue();		//Create a temporary Node value, and make it equal to the result of the function called NodeDequeue
		int returnValue = tempValue->getVal();	//Create an interger value called returnValue, and make it equal to the result of tempValue's getVal function
		if (front == nullptr) back = front;		//If the front of the queue produces a null pointer (is empty), make the back of the queue equal to the front of the queue
		queueSize -= 1;							//Decrement the value queueSize by 1
		return returnValue;						//Then finally return the interger that is under returnValue
	}

protected:

	Node* back;						//Node declaration called back, which is used to determine the back of the queue
	Node* front;					//Node declaration called front, which is used to determine the front of the queue
	int queueSize = 0;				//Interger declaration called queueSize, which is used to keep track of how many elements there are in a queue
	int queueLocation = 1;			//Interger declaration called queueLocation, which is used to keep track of which element is currently being examined in a queue

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

class Scheduler : public Queue 	//Class declaration used to handle the Scheduler, which also uses the Queue class
{
private:
	
	Node* currentVal;										//Declaration for a Node value called CurrentVal, which is used to check the current ID and Priority for the Priority Scheduler
	int currentID = 0;										//Declaration of an interger value called currentID, which is used to store the Process ID
	int currentPrio = 0;									//Declaration of an interger value called currentPrio, which is used to store the Priority Value
	int prioCheck = 10;										//Declaration of an interger value called PrioCheck, which is used to compare with the value stored under currentPrio

	Node* NodeDequeue(void) {								//Function used to remove the node from the front of the queue.
		Node* temp = front;									//Create a temporary Node value, and make it equal to the value of the front value
		if (front != nullptr)								//If the front of the queue is NOT null, (has at least 1 value), 
		{
			front = front->getPrev();						//Make the front value equal to the result of front's getPrev function
			if (front != nullptr) front->setNext(nullptr);	//If the front of the queue is still NOT null (has at least 1 value), set the front value to be equal to nullptr(Null Pointer)
		}
		return temp;										//Then return the Node value that is stored under temp
	};

	Scheduler PriorityScheduler(Scheduler toProcess ) {		//Function that takes a Queue as an input, and re-sorts it depending on the priority values
		Scheduler priotisedQueue;							//Declaration of a Scheduler called priotisedQueue, which is returned once the Queue has been sorted out
		while (queueSize > 0)								//If the size of the queue has at least 1 element inside it,
		{
			currentVal = toProcess.NodeDequeue();			//Use the NodeDequeue function to remove the node value from the front of the queue
			currentID = currentVal->getVal();				//Make the value currentID equal to the result of currentVal's getVal function
			currentPrio = currentVal->getPriority();		//Make the value currentPrio equal to the result of currentVal's getPriority function
			queueSize -= 1;									//Then reduce the value of queueSize by 1
			if (currentPrio == prioCheck)					//Check to see if the currentPrio value is equal to the prioCheck value. If it is...
			{
				priotisedQueue.Enqueue(currentID, currentPrio);	//Enqueue the value into the priotisedQueue queue, with the ID being the value under currentID, and priority being the value under currentPrio
				currentID = 0;								//Reset currentID to be equal to 0
				currentPrio = 0;							//Reset currentPrio to be equal to 0
			}
			else {											//If currentPrio is NOT equal to the value stored under prioCheck...
				toProcess.Enqueue(currentID, currentPrio);	//Enqueue the value back into the original queue, with the ID being the value under currentID, and priority being the value under currentPrio
				currentID = 0;								//Reset currentID to be equal to 0
				currentPrio = 0;							//Reset currentPrio to be equal to 0
				queueSize += 1;								//Then increment the value stored under queueSize by 1
			}
			queueLocation += 1;								//Increment the value under queueLocation by 1, ready for the next element in the queue to be checked
			if (queueLocation > queueSize)					//If queueLocation is greater than queueSize, and it would check an empty queue element
			{
				prioCheck -= 1;								//Reduce the priority check value by 1 from whatever it was on the last loop,
				queueLocation = 1;							//Then reset queueLocation to be equal to be 1, ready to check the first value in the queue
				if (prioCheck <= 0)							//If prioCheck is less or equal to the value of 0, which means all the elements from the inputted queue has been sorted...
				{
					return priotisedQueue;					//Then return the Scheduler called priotisedQueue, which is the queue with the priority values sorted in descending order
				}
			}
		}
	}
};
