#pragma once

template <typename My>
class MySingletonB
{
private:
	static My *inst;

public:
	static My* GetInst();
	void Destroy();
};

template <typename My>
My *MySingletonB<My>::inst = nullptr;

template <typename My>
My* MySingletonB<My>::GetInst()
{
	if (inst == nullptr)
	{
		inst = new My;
	}
	return inst;
}

template <typename My>
void MySingletonB<My>::Destroy()
{
	delete inst;
	inst = nullptr;
}