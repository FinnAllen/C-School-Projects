// author Dr Y and CPSC 122 Fall 2018
// date: November 6, 2017
// file queue.h

//   Specification for ADT Queue
//   data object: a queue which is a First In First Out List
//   operations: create, destroy, check if empty, copy
//               (finish)
#ifndef QUEUE_H
#define QUEUE_H
                           // member function should have const??
#include <iostream>
using namespace std;

struct Node;
typedef int ItemType;

class Queue
{
   //outputs a queue to a file or the screen
   //pre  : rhsq exists. output is open.
   //post : contents of rhsq have been output
   //usage: cout << rhsq << endl;   
   friend ostream& operator<< (ostream& output, const Queue& rhsq);

public:

   //creates an empty queue
   //post : an empty queue
   //usage: Queue q;
   Queue();
   
   //copies an existing queue
   //pre  : rhsq exists
   //post : queue object is a copy of rhsq
   //usage: Queue q(anotherq); or passing a Que object by value
   Queue(const Queue& rhsq);
   
   //destroys a queue
   //pre  : queue object exists
   //post : queue object does not exist
   //usage: automatically done at the end of scope
   ~Queue();
   
   //finds the size of a queue object
   //pre  : queue object exists
   //post : returns the size of the queue object
   //usage: cout << q.getSize();
   int getSize() const;
   
   //checks to see if a queue object is empty
   //pre  : queue object exists
   //post : if queue is empty returns true else returns false
   //usage: if (q.isEmpty())
   bool isEmpty() const;
   
   //inserts a new item at the rear of the queue
   //pre  : newItem has an assigned value; queue exists
   //post : if queue object is not full, newItem is added
   //       at the rear of the queue and isNotFull is true else isNotFull is false
   // usage: myq.lineUp(hunter, isNotFull);
   void lineUp(ItemType newItem, bool& isNotFull);
   
   //deletes item from the front of the queue after copying it
   //pre  : queue exists
   //post : if queue is nonempty, front of queue has been removed
   //         and isNotEmpty is true else isNotEmpty is false
   // usage:
   void getServed(bool& isNotEmpty);
   
   //copies the front item
   //pre  : queue exists and is not empty
   //post : the front item in the queue is copied into frontItem
   
   ItemType getWhoIsServed() const;
   
   //copies the queue
   //pre  : rhsq exists. queue object exists but may be empty
   //post : queue object is a copy of rhsq
   //usage: copyq.operator=(rhsq);
   //      or        copyq = rhsq;
   Queue& operator=(const Queue& rhsq);
   
private: 
   
   Node* backptr;
};
#endif
