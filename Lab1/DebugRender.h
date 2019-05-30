#pragma once
#include "Define.h"
#define MaxVert 200000  // Upper limit. Raise if needed 
using namespace DirectX;
namespace graphics_system
{
	class DebugRender
	{
		ID3D11Buffer* gpu_side_buffer[MaxVert]; // Initialized to be MAX_VERTS in size  
		ID3D11Buffer* IndexBuffer;
		Vertex* cpu_side_buffer;
		//AABBTest AABBTest;
		//Vertex core3axis[6];
		int vert_count; 
	public:
		DebugRender();
		~DebugRender();

		// add_line  
		// puts verts into cpu_side_buffer  
		// increments vert_count 
		// DOES NOT CREATE/RESET/MODIFY the GPU vertex buffer  
		void add_line(Vertex a, Vertex b); 
		void add_3axis(VertexWVP wvp);
		// flush 
		// called only once per frame! 
		// Overwrites the GPU buffer contents with CPU buffer contents 
		// Draws the debug lines for vert_count  
		// resets vert_count to 0  
		void flush(ID3D11Device*	device,
		ID3D11DeviceContext* dc,
		ID3D11Buffer* vCB2GPU,
		VertexWVP*	Vcb);


		//AABBFunctions

		AABB createAABB(Vertex A, Vertex B, Vertex C);
		AABB createAABB(XMFLOAT3 A, XMFLOAT3 B, XMFLOAT3 C);
		void AABBtoCube(AABB*_aabb);
		void DrawAABB(AABB a);
		//Variables

		vector <AABB> TerrainAABB;
	};
};
