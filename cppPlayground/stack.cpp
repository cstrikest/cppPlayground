#include "Stack.h"

// 复制构造函数 需要提供新new的指针。因为旧的已经被delete，直接赋值会指向释放过的内存。
Stack::Stack(const Stack& stack) :
	__maxptr(stack.__maxptr),
	__ptr(stack.__ptr)
{
	__mem = new int[__maxptr];
	*__mem = *stack.__mem;
}

Stack::Stack(Stack&& stack) noexcept :
	__maxptr(stack.__maxptr),
	__ptr(stack.__ptr)
{
	__mem = stack.__mem;
	stack.__mem = nullptr;
	stack.__maxptr = 0;
	stack.__ptr = 0;
}
void Stack::showStack(std::ostream& cout) const
{
	for (int i = __ptr - 1; i >= 0; i--)
	{
		cout << std::hex << i * 4 << "\t\t" << std::dec << *(__mem + i) << std::endl;
	}
}

// 运算符重载
Stack& Stack::operator+(const int& value)
{
	if (__ptr < __maxptr) *((__mem)+(__ptr)++) = value;
	return *this;
}

Stack& Stack::operator+=(const int& value)
{
	if (__ptr < __maxptr) *((__mem)+(__ptr)++) = value;
	return *this;
}

int Stack::operator--() { if (__ptr > 0) return *(__mem + --__ptr); }

// 友元运算符重载 
std::ostream& operator<<(std::ostream& os, Stack& stack) { return os << "A stack with " << stack.__maxptr << " integer."; }

// 赋值运算符重载 判断是不是自赋值，然后delete掉等号左边对象现有的指针，new新的指针再赋值。
Stack& Stack::operator=(const Stack& stack)
{
	if (this == &stack) return *this;
	delete[] __mem;
	__mem = new int[__maxptr];
	__maxptr = stack.__maxptr;
	*__mem = *stack.__mem;
	__ptr = stack.__ptr;
	return *this;
}

Stack& Stack::operator=(Stack&& stack) noexcept
{
	if (this == &stack) return *this;
	delete[] __mem;
	__mem = stack.__mem;
	__maxptr = stack.__maxptr;
	__ptr = stack.__ptr;
	stack.__mem = nullptr;
	stack.__maxptr = 0;
	stack.__ptr = 0;
	return *this;
}

Stack::operator int* () { return __mem; }

void runStack()
{
	std::string tmp;
	int tint;
	std::string size;
	std::cout << "Size of stack:" << std::endl << ">>";
	do
	{
		std::cin >> size;
	} while (!isNumeric(size));

	Stack stack(std::stoi(size));
	std::cin.get();
	std::cout << "Maxium " << 4 * std::stoi(size) << " bytes." << std::endl;
	while (true)
	{
		if (stack.isFull()) std::cout << ">|";
		else if (stack.isEmpty()) std::cout << "|>";
		else std::cout << ">>";
		std::getline(std::cin, tmp);
		std::cin.clear();
		if (isNumeric(tmp))
		{
			tint = std::atoi(tmp.c_str());
			if (stack.isFull()) std::cout << "\033[1AFULL." << std::endl;
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
			if (stack.isEmpty()) std::cout << "\033[1AEMPTY." << std::endl;
			//else std::cout << stack.pop() << std::endl;lse std::cout << stack.pop() << std::endl;
			else std::cout << --stack << std::endl;

		}
		else if (tmp[0] == 's')
		{
			//if (stack.isEmpty()) std::cout << "-\t\t-" << std::endl;
			//else stack.showStack(std::cout);
			stack.showStack(std::cout);
		}
		else if (tmp[0] == 'q' or tmp[0] == 'Q') break;
		else
		{
			std::cout << "\033[1A\033[KIllegal input." << std::endl;
			continue;
		}
	}
}

