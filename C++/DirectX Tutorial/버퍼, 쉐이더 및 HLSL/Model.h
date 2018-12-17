#pragma once

class Model : public AlignedAllocationPolicy<16>
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

private:
	Buffer* m_vertexBuffer = nullptr;
	Buffer* m_indexBuffer = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;

private:
	bool InitializeBuffers(Device*);
	void ShutdownBuffers();
	void RenderBuffers(DC*);

public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(Device*);
	void Shutdown();
	void Render(DC*);

	int GetIndexCount();
};