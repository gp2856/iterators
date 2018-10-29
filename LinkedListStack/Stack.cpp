#include "Stack.h"

std::ostream & operator<<(std::ostream & out, Stack & s)
{
	out << s.Peek();
	return out;
}
