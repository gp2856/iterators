#pragma once
#include <iterator>
#include <iostream>

class Stack
{
private:
	class Element
	{
	public:
		Element( int val,Element* pNext )
			:
			val( val ),
			pNext( pNext )
		{}
		Element( const Element& src )
			:
			val( src.val )
		{
			if( src.pNext != nullptr )
			{
				pNext = new Element( *src.pNext );
			}
		}
		Element& operator=( const Element& ) = delete;
		int GetVal() const
		{
			return val;
		}
		int& GetValRef()
		{
			return val;
		}
		Element* GetNext() const
		{
			if (pNext != nullptr)
			{
				return pNext;
			}
			else return nullptr;
		}
		Element* Disconnect()
		{
			auto pTemp = pNext;
			pNext = nullptr;
			return pTemp;
		}
		int CountElements() const
		{
			if( pNext != nullptr )
			{
				return pNext->CountElements() + 1;
			}
			else
			{
				return 1;
			}
		}

		~Element()
		{
			delete pNext;
			pNext = nullptr;
		}
	private:
		int val;
		Element* pNext = nullptr;
	};
public:
	class ElementIterator : std::iterator<std::forward_iterator_tag, Element>
	{
	public:
		// Constructors and copy operator
		ElementIterator(pointer p = nullptr) : ptr(p) {}
		ElementIterator(reference p) : ptr(&p) {}
		ElementIterator(ElementIterator* source) : ptr(source->ptr) {}
		ElementIterator& operator=(const ElementIterator& src) { ptr = src.ptr; return *this; }

		// Increment operators
		ElementIterator& operator++() { ptr = ptr->GetNext(); return *this; }
		ElementIterator& operator++(int) { ElementIterator copy(this); ptr = ptr->GetNext(); return copy; };

		// Comparison Operators
		bool operator==(const ElementIterator& rhs) { return ptr == rhs.ptr; };
		bool operator!=(const ElementIterator& rhs) { return ptr != rhs.ptr; };

		// Dereference Operators
		int& operator*() { return ptr->GetValRef(); };
		int& operator->() { return ptr->GetValRef(); };

	protected:
		pointer ptr;
	};

	class ElementIteratorConst : std::iterator<std::forward_iterator_tag, Element>
	{
	public:
		// Constructors and copy operator
		ElementIteratorConst(pointer p = nullptr) : ptr(p) {}
		ElementIteratorConst(reference p) : ptr(&p) {}
		ElementIteratorConst(ElementIteratorConst* source) : ptr(source->ptr) {}
		ElementIteratorConst& operator=(const ElementIteratorConst& src) { ptr = src.ptr; return *this; }

		// Increment operators
		ElementIteratorConst& operator++() { ptr = ptr->GetNext(); return *this; }
		ElementIteratorConst& operator++(int){ ElementIteratorConst copy(this); ptr = ptr->GetNext(); return copy; };

		// Comparison Operators
		bool operator==(const ElementIteratorConst& rhs) const { return ptr == rhs.ptr; };
		bool operator!=(const ElementIteratorConst& rhs) const { return ptr != rhs.ptr; };

		// Dereference Operators
		const int& operator*() const { return ptr->GetValRef(); };
		const int& operator->() const { return ptr->GetValRef(); };
	protected:
		pointer ptr;
	};
	
	Stack() = default;
	Stack( const Stack& src )
	{
		*this = src;
	}
	Stack& operator=( const Stack& src )
	{
		if( &src != this )
		{
			if( !Empty() )
			{
				delete pTop;
				pTop = nullptr;
			}

			if( !src.Empty() )
			{
				pTop = new Element( *src.pTop );
			}
		}
		return *this;
	}
	~Stack()
	{
		delete pTop;
		pTop = nullptr;
	}
	void Push( int val )
	{
		pTop = new Element( val,pTop );
	}
	int Pop()
	{
		if( !Empty() )
		{
			const int tempVal = pTop->GetVal();
			auto pOldTop = pTop;
			pTop = pTop->Disconnect();
			delete pOldTop;
			return tempVal;
		}
		else
		{
			return -1;
		}
	}
	int Size() const
	{
		if( !Empty() )
		{
			return pTop->CountElements();
		}
		else
		{
			return 0;
		}
	}

	int Peek()
	{
		return pTop->GetVal();
	}
	bool Empty() const
	{
		return pTop == nullptr;
	}


	// Iterator methods
	ElementIterator& begin() { return ElementIterator{ pTop }; };
	ElementIterator& end() { return ElementIterator{}; };
	ElementIteratorConst& begin() const { return ElementIteratorConst{ pTop }; };
	ElementIteratorConst& end() const { return ElementIteratorConst{}; }

private:
	Element* pTop = nullptr;
};

