#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <iostream>
#include "XTime.h"
#include <fstream>
#include <vector>
#include "WICTextureLoader\WICTextureLoader.h"

using namespace std;
using namespace DirectX;
//Shaders
#include "VertexShader.csh"
#include "PixelShader.csh"

#define black {0.0f,0.0f,0.0f,1.0f}
#define white {1.0f,1.0f,1.0f,1.0f}
#define gray  {0.5f,0.5f,0.5f,1.0f}

struct Vertex
{
	XMFLOAT3 Pos = XMFLOAT3(0,0,0);
	XMFLOAT4 Color = XMFLOAT4(0,0,0,0);
	XMFLOAT2 UV = XMFLOAT2(0,0);
	XMFLOAT3 Normal = XMFLOAT3(0,0,0);
	//XMFLOAT3 Tangent;
	float		weight[4] = { 0,0,0,0 };
	unsigned int index[4] = { 0,0,0,0 };
};

struct Simple_Vertex
{
	XMFLOAT4	Pos;
	XMFLOAT3	Norm;
	XMFLOAT2	UV;
	XMFLOAT3	Tangent;
	float		weight[4];
	int			index[4];
};

struct Matrix
{
	float World[3];
	float Rotate[3];
};

struct VertexWVP
{
	XMMATRIX World = XMMatrixIdentity();
	XMMATRIX View;
	XMMATRIX Proj;
};

struct Mesh
{
	VertexWVP WVP;
	std::vector<Simple_Vertex> ConstVertex;
	Vertex*	VertexToGPU;
	int	V_Buffer_index;
	int V_Buffer_Size;;
	int I_Buffer_index;
	int I_Buffer_Size;

	~Mesh()
	{
		delete[] VertexToGPU;
	}
};

struct AABB
{
	float maxX, maxY, maxZ, minX, minY, minZ;
	XMFLOAT3 Center;
};

struct Light
{
	XMFLOAT4	PointLightPos;
	XMFLOAT4	PointLightColor;
	XMFLOAT4	Emissive;
	XMFLOAT4	Diffuse;
	XMFLOAT4	Ambient;
	XMFLOAT4	Specular;
	XMFLOAT4	CamPos;
	float		PointLightRange;
	int			Mode = 1;
	XMFLOAT2	Pad;
};

struct Keyframe
{
	double time;
	vector<XMMATRIX> Joints;
};

struct Anim_Clip
{
	double duration;
	vector<Keyframe> frames;
	vector<int> parentlist;
	vector<XMMATRIX> CurrJoints;
	int frame_index = 1;
};