#pragma once
#include"utils.h"

class Stack
{
private:
	int __ptr;
	int __maxPtr;
	int* __mem;

public:
	inline Stack(int size)
	{
		__maxPtr = size;
		__mem = new int[__maxPtr];
		__ptr = 0;
	}
	Stack(const Stack&);
	inline ~Stack() { delete[] __mem; }
	
	inline void push(int value) { if (__ptr < __maxPtr) *((__mem)+__ptr++) = value; }

	inline int pop() { if (__ptr > 0) return *(__mem + --__ptr); }

	inline int getsize() const { return __ptr; }

	inline bool isFull() const { return __ptr == __maxPtr; }

	inline bool isEmpty() const { return __ptr == 0; };
	
	void showStack(std::ostream&) const;

	Stack& operator+(int);
	Stack& operator+=(int);
	Stack& operator=(const Stack&);
	int operator--();

	friend std::ostream& operator<<(std::ostream&, Stack&);

	operator int* ();
};

void runStack();
