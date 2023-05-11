#pragma once
#include"utils.h"

class Stack
{
protected:
	int __ptr;
	int __maxptr;
	int* __mem;

public:
	// 内联函数必须定义在头文件。因为编译器需要在随时展开。
	// 所以在单个编译单元内必须能找到定义。
	// 每个文件内都定义一次不现实，而且定义不同的话会出现无意义展开。
	// 因此推荐在头文件内定义内联函数。
	// 之前因为这个找了半天问题。还以为是vs的锅。

	// 类构造函数初始化列表
	// 直接用复制构造函数初始化，不用先调用默认构造函数再调用赋值运算符的重载。
	// 如果子类不指定要使用的基类构造函数，则调用默认构造函数。
	// 这里的话跟以下函数Stack()的重载匹配。
	inline Stack(const int size):
		__ptr(0), __maxptr(size), __mem(new int[__maxptr]) {}
	Stack(const Stack&);
	inline Stack(Stack&&) noexcept;

	// 析构函数。如果别的函数在使用完引用后用值传递返回拷贝的对象的话，原来的对象会调用一次析构函数。
	// 导致新对象在结束后delete两次，引发异常。
	virtual inline ~Stack() { delete[] __mem; }
	inline void push(const int& value)
	{
		if (__ptr < __maxptr) *((__mem)+__ptr++) = value;
	}
	inline int pop() { if (__ptr > 0) return *(__mem + --__ptr); }
	inline int getsize() const { return __ptr; }
	inline bool isFull() const { return __ptr == __maxptr; }
	inline bool isEmpty() const { return __ptr == 0; };

	void showStack(std::ostream&) const;

	Stack& operator+(const int&);
	Stack& operator+=(const int&);
	Stack& operator=(const Stack&);
	Stack& operator=(Stack&&) noexcept;
	int operator--();

	friend std::ostream& operator<<(std::ostream&, Stack&);

	operator int* ();
};

void runStack();

