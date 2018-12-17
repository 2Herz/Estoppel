#pragma once

template <typename T>
class SingletonA
{
public:
	static T&	GetInstance();
};

template <typename T>
T& SingletonA<T>::GetInstance()
{
	static T instance;
	return instance;
}