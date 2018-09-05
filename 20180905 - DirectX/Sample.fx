//	¡§¡° Ω¶¿Ã¥ı
float4 VS(float4 Pos : POSITION) : SV_POSITION
{
	return Pos;
}

float4 PS(float4 Pos : SV_POSITION) : SV_Target
{
	return float4(0.8f, 0.3f, 0.5f, 1.0f);
}