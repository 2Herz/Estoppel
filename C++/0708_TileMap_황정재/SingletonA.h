#pragma once

template <typename My>
class MySingletonA
{
public:
	static My& GetInst();
};

template <typename My>
My& MySingletonA<My>::GetInst()
{
	static My instance;
	return instance;
}