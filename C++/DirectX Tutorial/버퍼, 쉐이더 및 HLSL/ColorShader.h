#pragma once

class ColorShader : public AlignedAllocationPolicy<16>
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

private:
	VertexShader* m_vertex = nullptr;
	PixelShader* m_pixel = nullptr;
	Layout* m_layout = nullptr;
	Buffer* m_matBuffer = nullptr;

private:
	bool InitializeShader(Device*, HWND, MWCHAR*, MWCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(Blob*, HWND, MWCHAR*);

	bool SetShaderParameters(DC*, XMMATRIX, XMMATRIX, XMMATRIX);
	void RenderShader(DC*, int);

public:
	ColorShader();
	ColorShader(const ColorShader&);
	~ColorShader();

	bool Initialize(Device*, HWND);
	void Shutdown();
	bool Render(DC*, int, XMMATRIX, XMMATRIX, XMMATRIX);
};