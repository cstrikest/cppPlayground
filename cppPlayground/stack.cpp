#include "Stack.h"

Stack::Stack(int size)
{
	__maxPtr = size;
	__mem = new int[__maxPtr];
	__ptr = 0;
}

// 析构函数。如果别的函数在使用完引用后用值传递返回拷贝的对象的话，原来的对象会调用一次析构函数。
// 导致新对象在结束后没有初始化就delete，引发异常。
inline Stack::~Stack() { delete __mem; }

inline void Stack::push(int value) { if (__ptr < __maxPtr) *((__mem)+__ptr++) = value; }

inline int Stack::pop() { if (__ptr > 0) return *(__mem + --__ptr); }

inline int Stack::getsize() const { return __ptr; }

inline bool Stack::isFull() const { return __ptr == __maxPtr; }

inline bool Stack::isEmpty() const { return __ptr == 0; };

void Stack::showStack(std::ostream& cout) const
{
	for (int i = __ptr - 1; i > 0 - 1; i--)
	{
		cout << std::hex << i * 4 << "\t\t" << std::dec << *(__mem + i) << std::endl;
	}
}

// 运算符重载
Stack& Stack::operator+(int value)
{
	if (this->__ptr < this->__maxPtr) *((this->__mem) + (this->__ptr)++) = value;
	return *this;
}

inline Stack& Stack::operator+=(int value)
{
	if (this->__ptr < this->__maxPtr) *((this->__mem) + (this->__ptr)++) = value;
	return *this;
}

int Stack::operator--() { if (__ptr > 0) return *(__mem + --__ptr); }

// 友元运算符重载 
std::ostream& operator<<(std::ostream& os, Stack& stack) { return os << "A stack with " << stack.__maxPtr << " integer."; }

Stack::operator int* () { return this->__mem; }

void runStack()
{
	std::string tmp;
	int tint;
	int size;
	std::cout << "Size of stack:" << std::endl << ">>";
	std::cin >> size;
	Stack stack(size);
	std::cin.get();
	std::cout << "Maxium " << 4 * size << " bytes." << std::endl;
	while (true)
	{
		std::cout << ">>";
		std::getline(std::cin, tmp);
		std::cin.clear();
		if (isNumeric(tmp))
		{
			tint = std::atoi(tmp.c_str());
			if (stack.isFull()) std::cout << "FULL." << std::endl;
			else
			{
				// stack.push(tint);
				// stack = stack + tint;
				stack += tint;
				continue;
			}
		}
		else if (tmp[0] == 'p')
		{
			if (stack.isEmpty()) std::cout << "EMPTY." << std::endl;
			//else std::cout << stack.pop() << std::endl;lse std::cout << stack.pop() << std::endl;
			else std::cout << --stack << std::endl;

		}
		else if (tmp[0] == 's')
		{
			if (stack.isEmpty()) std::cout << "-\t\t-" << std::endl;
			else stack.showStack(std::cout);
			std::cout << stack << std::endl;
		}
		else if (tmp[0] == 'q' or tmp[0] == 'Q') break;
		else
		{
			std::cout << "Illegal input." << std::endl;
			continue;
		}
	}
}
