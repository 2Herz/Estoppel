cbuffer MatrixBuffer
{
	matrix worldMat;
	matrix viewMat;
	matrix projectionMat;
}

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

PixelInputType ColorVertexShader(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.0f;

	output.position = mul(input.position, worldMat);
	output.position = mul(input.position, viewMat);
	output.position = mul(input.position, projectionMat);

	output.color = input.color;

	return output;
}