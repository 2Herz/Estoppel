#pragma once

template <typename T>
class SingletonB
{
private:
	static T *m_inst;

public:
	static T* GetInst();
	void Destroy();
};

template <typename T>
T *SingletonB<T>::m_inst = nullptr;

template <typename T>
T* SingletonB<T>::GetInst()
{
	if (m_inst == nullptr)
	{
		m_inst = new T;
	}
	return m_inst;
}

template <typename T>
void SingletonB<T>::Destroy()
{
	delete m_inst;
	m_inst = nullptr;
}