#pragma once

/*
	�� ���� �׷���(Graphics) Ŭ�����̴�.

	�� Ŭ���������� ���������� �׷���ī�带 �ý������κ��� ���ͼ�

	DirectX ���α׷��� ������ Ŭ�����̴�.

	�� Ŭ������ �ܺ���ġ�� �׷���ī��� ������ ������

	������ ����� ���� ��� DirectX 11 ���α׷��� �׷������� ��Ҹ� �Ѱ��ϴ� ���̴�.
*/

#include "Include.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	bool Init(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
};