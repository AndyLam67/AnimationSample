struct INPUT_VERTEX
{
	float4 Coor : SV_POSITION;
	float3 World : POSITION;
	float3 Norm : NORMAL;
//	float3 Tang : TANGENT;
	float2 UV : UV;
	float4 Color : COLOR;
};

cbuffer Light : register(b0)
{
	float4	P_Light_Pos;
	float4	P_Light_Color;
	float4	Emissive;
	float4	Diffuse;
	float4	Ambient;
	float4	Specular;
	float4  CamPos;
	float	Range;
	int		Mode;
	float2	Pad;
}

Texture2D diffuse		: register(t0);
Texture2D NormalMap		: register(t1);
Texture2D emissive		: register(t2);
Texture2D specular		: register(t3);

SamplerState textures	: register(s0);

//float3 calNewNorm(INPUT_VERTEX input)
//{
//	float4 NMap = NormalMap.Sample(textures, input.UV);
//	NMap = (2.0f*NMap) - 1.0f;
//	//input.Tang = normalize(input.Tang - dot(input.Tang, input.Norm)*input.Norm);
//	//float3 biTang = cross(input.Tang, input.Norm);
//	float3 biTang = cross(input.Norm, input.Tang);
//	float3x3 texSpace = float3x3(input.Tang, biTang, input.Norm);
//	return normalize(mul(NMap, texSpace));
//	//return normalize(NMap);
//}

float4 PointLight(INPUT_VERTEX input)
{
	float4 source = diffuse.Sample(textures, input.UV);
	float3 dir = normalize(P_Light_Pos.xyz - input.World.xyz);
	float ratio = saturate(dot(dir, input.Norm));
	float4 result = ratio * P_Light_Color*source;
	float atten = 1.0f - saturate(length(P_Light_Pos - input.World) / Range);
	return result * atten;
}

float4 tSp(INPUT_VERTEX input)
{
	float4 source = specular.Sample(textures, input.UV);
	float3 reflectionVector = 2 * dot(P_Light_Pos.xyz, input.Norm)*input.Norm - P_Light_Pos.xyz;
	reflectionVector = pow(dot(reflectionVector,CamPos.xyz), Specular.w);

	return(float4)(mul(reflectionVector,source.xyz),1);

}

float4 main(INPUT_VERTEX input) : SV_TARGET
{
	input.Norm = normalize(input.Norm);
	float4 tE = emissive.Sample(textures, input.UV);
	float4 tS = specular.Sample(textures, input.UV);
	float4 tD = diffuse.Sample(textures, input.UV);
	tS.x *= Specular.x;
	tS.y *= Specular.y;
	tS.z *= Specular.z;
	tS = pow(tS, Specular.w);

	tE.x *= Emissive.x;
	tE.y *= Emissive.y;
	tE.z *= Emissive.z;

	float4 Color;
	float4 test = tSp(input);
	Color= (tE + tS) * tD* Diffuse[3];
	
	if (Mode == 2)
		return tD;
	if (Mode != 3)
		return Color + PointLight(input);
	else
		return input.Color;
}