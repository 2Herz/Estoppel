#include "stdafx.h"
#include "ColorShader.h"

ColorShader::ColorShader()
{
}

ColorShader::ColorShader(const ColorShader& other)
{
}

ColorShader::~ColorShader()
{
}

bool ColorShader::Initialize(Device* device, HWND hWnd)
{
	return InitializeShader(device, hWnd, L"color.vs", L"color.ps");
}

void ColorShader::Shutdown()
{
	ShutdownShader();
}

bool ColorShader::Render(DC* pImm, int indexCount, XMMATRIX world, XMMATRIX view, XMMATRIX projection)
{
	if (!SetShaderParameters(pImm, world, view, projection))
	{
		return false;
	}

	RenderShader(pImm, indexCount);

	return true;
}

bool ColorShader::InitializeShader(Device* device, HWND hWnd, MWCHAR* vsFilename, MWCHAR* psFilename)
{
	Blob* errorMessage = nullptr;

	Blob* vertexShaderBuffer = nullptr;
	if (FAILED(D3DCompileFromFile(vsFilename, nullptr, nullptr, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS,
		0, &vertexShaderBuffer, &errorMessage)))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hWnd, vsFilename);
		}
		else
		{
			MessageBox(hWnd, vsFilename, L"쉐이더 파일을 찾지 못했습니다!", MB_OK);
		}

		return false;
	}

	Blob* pixelShaderBuffer = nullptr;
	if (FAILED(D3DCompileFromFile(psFilename, nullptr, nullptr, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS,
		0, &pixelShaderBuffer, &errorMessage)))
	{
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hWnd, psFilename);
		}
		else
		{
			MessageBox(hWnd, psFilename, L"쉐이더 파일을 찾지 못했습니다!", MB_OK);
		}

		return false;
	}

	if (FAILED(device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(),
		nullptr, &m_vertex)))
	{
		return false;
	}

	if (FAILED(device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(),
		nullptr, &m_pixel)))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	unsigned int numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	if (FAILED(device->CreateInputLayout(polygonLayout, numElements,
		vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_layout)))
	{
		return false;
	}

	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	D3D11_BUFFER_DESC matrixBufferDesc;
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	if (FAILED(device->CreateBuffer(&matrixBufferDesc, nullptr, &m_matBuffer)))
	{
		return false;
	}

	return true;
}

void ColorShader::ShutdownShader()
{
	if (m_matBuffer)
	{
		m_matBuffer->Release();
		m_matBuffer = 0;
	}

	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	if (m_pixel)
	{
		m_pixel->Release();
		m_pixel = 0;
	}

	if (m_vertex)
	{
		m_vertex->Release();
		m_vertex = 0;
	}
}

void ColorShader::OutputShaderErrorMessage(Blob* errorMessage, HWND hWnd, MWCHAR* shaderFilename)
{
	OutputDebugStringA(reinterpret_cast<const char*>(errorMessage->GetBufferPointer()));

	errorMessage->Release();
	errorMessage = 0;

	MessageBox(hWnd, L"쉐이더 컴파일 에러!", shaderFilename, MB_OK);
}

bool ColorShader::SetShaderParameters(DC* pImm, XMMATRIX world, XMMATRIX view, XMMATRIX projection)
{
	world = XMMatrixTranspose(world);
	view = XMMatrixTranspose(view);
	projection = XMMatrixTranspose(projection);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	if (FAILED(pImm->Map(m_matBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		return false;
	}

	MatrixBufferType* dataPtr = (MatrixBufferType*)mappedResource.pData;

	dataPtr->world = world;
	dataPtr->view = view;
	dataPtr->projection = projection;

	pImm->Unmap(m_matBuffer, 0);

	unsigned bufferNumber = 0;

	pImm->VSSetConstantBuffers(bufferNumber, 1, &m_matBuffer);

	return true;
	return false;
}

void ColorShader::RenderShader(DC* pImm, int indexCount)
{
	pImm->IASetInputLayout(m_layout);

	pImm->VSSetShader(m_vertex, nullptr, 0);
	pImm->PSSetShader(m_pixel, nullptr, 0);

	pImm->DrawIndexed(indexCount, 0, 0);
}