struct VSOUT {
	float4 color: COLOR;
	float4 pos: SV_POSITION;
};

cbuffer CBuf {
	matrix transform;
};

VSOUT main( float3 pos : POSITION, float4 color : COLOR )
{
	VSOUT vso;
	vso.pos = mul(float4(pos.x, pos.y, pos.z, 1.0f), transform);
	//vso.pos = float4(pos.x, pos.y, pos.z, 1.0f);
	vso.color = color;
	return vso;
}