#pragma once

template <typename T>
class SingletonB
{
private:
	static T *m_instance;

public:
	static T*	GetInstance();
	void		Dest();
};

template <typename T>
T *SingletonB<T>::m_instance = nullptr;

template <typename T>
T *SingletonB<T>::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new T;
	}
	return m_instance;
}

template <typename T>
void SingletonB<T>::Dest()
{
	delete m_instance;
	m_instance = nullptr;
}