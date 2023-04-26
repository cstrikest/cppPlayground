#pragma once
#include"utils.h"

class Stack
{
private:
	int __ptr;
	int __maxPtr;
	int* __mem;

public:
	Stack(int);
	~Stack();
	int getsize() const;
	void push(int);
	int pop();
	bool isFull() const;
	bool isEmpty() const;
	void showStack(std::ostream&) const;

	Stack& operator+(int);
	Stack& operator+=(int);
	int operator--();

	friend std::ostream& operator<<(std::ostream&, Stack&);

	operator int* ();
};

void runStack();
