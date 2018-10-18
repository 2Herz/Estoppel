#pragma once
template <typename T>
class Node
{
private:
	Node() : m_Next(nullptr), m_Prev(nullptr)
	{
	}

	~Node()
	{
	}

private:
	template <typename T>
	friend class TemplateDLL;
	template <typename T>
	friend class Iterator;
	template <typename T>
	friend class Reverse_Iterator;

private:
	T			m_Data;
	Node<T>*	m_Next;
	Node<T>*	m_Prev;
};

template <typename T>
class Iterator
{
public:
	Iterator()
	{}
	~Iterator()
	{}

private:
	template <typename T>
	friend class TemplateDLL;

private:
	typedef Node<T>		NODE;
	typedef Node<T>*	PNODE;

private:
	PNODE m_Node;

public:
	bool operator==(const Iterator<T>& right)
	{
		return m_Node == right.m_Node;
	}

	bool operator!=(const Iterator<T>& right)
	{
		return m_Node != right.m_Node;
	}

	void operator ++()
	{
		m_Node = m_Node->m_Next;
	}

	void operator --()
	{
		m_Node = m_Node->m_Prev;
	}

	T operator *()
	{
		return m_Node->m_Data;
	}
};

template <typename T>
class Reverse_Iterator
{
public:
	Reverse_Iterator()
	{}

	~Reverse_Iterator()
	{}

private:
	template <typename T>
	friend class TemplateDLL;

private:
	typedef Node<T>		NODE;
	typedef Node<T>*	PNODE;

private:
	PNODE m_Node;

public:
	bool operator==(const Reverse_Iterator<T>& right)
	{
		return m_Node == right.m_Node;
	}

	bool operator!=(const Reverse_Iterator<T>& right)
	{
		return m_Node != right.m_Node;
	}

	void operator ++()
	{
		m_Node = m_Node->m_Prev;
	}

	void operator--()
	{
		m_Node = m_Node->m_Next;
	}

	T operator*()
	{
		return m_Node->m_Data;
	}
};

template <typename T>
class TemplateDLL
{
public:
	TemplateDLL()
	{
		m_Begin = new NODE;
		m_End = new NODE;

		m_Begin->m_Next = m_End;
		m_End->m_Prev = m_Begin;

		m_Size = 0;
	}
	~TemplateDLL()
	{
		clear();
		delete m_Begin;
		delete m_End;
		m_Size = 0;
	}

private:
	typedef Node<T>		NODE;
	typedef Node<T>*	PNODE;

public:
	typedef Iterator<T> iterator;
	typedef Reverse_Iterator<T> Reverse_iterator;

private:
	PNODE			m_Begin;
	PNODE			m_End;
	unsigned int	m_Size;

public:
	void push_back(const T& data)
	{
		PNODE Node = new NODE;

		Node->m_Data = data;

		PNODE Prev = m_End->m_Prev;

		Prev->m_Next = Node;
		Node->m_Prev = Prev;

		Node->m_Next = m_End;
		m_End->m_Prev = Node;

		m_Size++;
	}

	void push_front(const T& data)
	{
		PNODE Node = new NODE;

		Node->m_Data = data;

		PNODE First = m_Begin->m_Next;

		First->m_Prev = Node;
		Node->m_Next = First;

		Node->m_Prev = m_Begin;
		m_Begin->m_Next = Node;

		m_Size++;
	}

	unsigned int size() const
	{
		return m_Size;
	}

	bool empty() const
	{
		return m_Size == 0;
	}

	void clear()
	{
		PNODE Node = m_Begin->m_Next;

		while (Node != m_End)
		{
			PNODE Next = Node->m_Next;
			delete Node;
			Node = Next;
		}

		m_Begin->m_Next = m_End;
		m_End->m_Prev = m_Begin;
		m_Size = 0;
	}

	iterator begin()
	{
		iterator iter;
		iter.m_Node = m_Begin->m_Next;
		return iter;
	}

	iterator end()
	{
		iterator iter;
		iter.m_Node = m_End;
		return iter;
	}

	Reverse_iterator rbegin()
	{
		Reverse_iterator riter;
		riter.m_Node = m_End->m_Prev;
		return riter;
	}

	Reverse_iterator rend()
	{
		Reverse_iterator riter;
		riter.m_Node = m_Begin->m_Next->m_Prev;
		return riter;
	}
};