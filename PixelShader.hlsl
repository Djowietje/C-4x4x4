cbuffer Colors {
	float4 rgba;
};

float4 main(): SV_TARGET
{
	return rgba;
}