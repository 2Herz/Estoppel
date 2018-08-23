#pragma once

template <typename T>
class SingletonA
{
public:
	static T& GetInst();
};

template <typename T>
T& SingletonA<T>::GetInst()
{
	static T inst;
	return inst;
}