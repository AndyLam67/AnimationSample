cbuffer _matrix : register(b0)
{
	matrix World;
	matrix View;
	matrix Proj;
}

cbuffer Joint : register(b1)
{
	matrix Joints[60];
}

struct INPUT_VERTEX
{
	float3 Coor : POSITION;
	float4 Color : COLOR;
	float2 UV : UV;
	float3 Normal : NORMAL;
	float4 weight : WEIGHT;
	uint4 index : INDEX;
};

struct OUTPUT_VERTEX
{
	float4 Coor : SV_POSITION;
	float3 World : POSITION;
	float3 Norm : NORMAL;
	//float3 Tang : TANGENT;
	float2 UV : UV;
	float4 Color : COLOR;
};

float4 CalCoor(INPUT_VERTEX input)
{
	float4 result = float4(0,0,0,0);
	float4 thisCoor = float4(input.Coor,1);
	for (int i = 0; i < 4; i++)
	{
		float weight = input.weight[i];
		if (weight == 0)
			continue;
		uint index = input.index[i];
		float4 temp = mul(thisCoor, Joints[index]);
		temp *= weight;
		result += temp;
	}
	return result;
}

OUTPUT_VERTEX main(INPUT_VERTEX input)
{
	OUTPUT_VERTEX output = (OUTPUT_VERTEX)0;
	output.Coor = CalCoor(input);
	output.Coor = mul(output.Coor, World);
	output.World = input.Coor;
	output.Coor = mul(output.Coor, View);
	output.Coor = mul(output.Coor, Proj);
	output.Norm = mul(float4(input.Normal,1),World);
	//output.Tang = mul(float4(input.Tang,1),World);
	output.UV = input.UV;
	output.Color = input.Color;
	return output;
}