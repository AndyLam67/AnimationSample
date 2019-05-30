#include "stdafx.h"
#include "DebugRender.h"
//using namespace graphics_system;

graphics_system::DebugRender::DebugRender()
{
	vert_count = 0;
	cpu_side_buffer = new Vertex[MaxVert];
}

graphics_system::DebugRender::~DebugRender()
{
	if (IndexBuffer != NULL) IndexBuffer->Release();
	for (size_t i = 0; i < MaxVert; i++)
	{
		if (gpu_side_buffer[i] != NULL) gpu_side_buffer[i]->Release();
	}
}

void graphics_system::DebugRender::add_line(Vertex a, Vertex b)
{
	cpu_side_buffer[vert_count] = a;
	vert_count++;
	cpu_side_buffer[vert_count] = b;
	vert_count++;
}

void graphics_system::DebugRender::add_3axis(VertexWVP wvp)
{
	Vertex temp1, temp2;
	XMVECTOR v1, v2;
	//X red
	v1 = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	wvp.World.r[0] = XMVector4Normalize(wvp.World.r[0]);
	wvp.World.r[1] = XMVector4Normalize(wvp.World.r[1]);
	wvp.World.r[2] = XMVector4Normalize(wvp.World.r[2]);
	
	v1 = XMVector4Transform(v1, wvp.World);

	v2 = XMVectorSet(1.0f, 0.0f, 0.0f, 1.0f);
	v2 = XMVector4Transform(v2, wvp.World);

	temp1 = Vertex{ XMFLOAT3(v1.m128_f32[0],v1.m128_f32[1],v1.m128_f32[2]),XMFLOAT4(1.0f,0.0f,0.0f,1.0f) };
	temp2 = Vertex{ XMFLOAT3(v2.m128_f32[0],v2.m128_f32[1],v2.m128_f32[2]),XMFLOAT4(1.0f,0.0f,0.0f,1.0f) };
	add_line(temp1, temp2);

	//Y green
	v1 = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	v1 = XMVector4Transform(v1, wvp.World);

	v2 = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);
	v2 = XMVector4Transform(v2, wvp.World);

	temp1 = Vertex{ XMFLOAT3(v1.m128_f32[0],v1.m128_f32[1],v1.m128_f32[2]),XMFLOAT4(0.0f,1.0f,0.0f,1.0f) };
	temp2 = Vertex{ XMFLOAT3(v2.m128_f32[0],v2.m128_f32[1],v2.m128_f32[2]),XMFLOAT4(0.0f,1.0f,0.0f,1.0f) };
	add_line(temp1, temp2);

	//Z blue
	v1 = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	v1 = XMVector4Transform(v1, wvp.World);

	v2 = XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
	v2 = XMVector4Transform(v2, wvp.World);

	temp1 = Vertex{ XMFLOAT3(v1.m128_f32[0],v1.m128_f32[1],v1.m128_f32[2]),XMFLOAT4(0.0f,0.0f,1.0f,1.0f) };
	temp2 = Vertex{ XMFLOAT3(v2.m128_f32[0],v2.m128_f32[1],v2.m128_f32[2]),XMFLOAT4(0.0f,0.0f,1.0f,1.0f) };
	add_line(temp1, temp2);
}

void graphics_system::DebugRender::flush(ID3D11Device*	device,
	ID3D11DeviceContext* dc,
	ID3D11Buffer* vCB2GPU,
	VertexWVP*	Vcb)
{
	//set buffer
	for (int i = 0; i < vert_count/2; i++)
	{
		Vertex vertexs[2];
		vertexs[0] = cpu_side_buffer[i * 2];
		vertexs[1] = cpu_side_buffer[i * 2+1];
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(Vertex) * 2;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.StructureByteStride = sizeof(Vertex);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertexs;

		if(gpu_side_buffer[i]==NULL)
		device->CreateBuffer(&desc, &data, &gpu_side_buffer[i]);
		else
		{
			D3D11_MAPPED_SUBRESOURCE map;
			dc->Map(gpu_side_buffer[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
			memcpy(map.pData,&vertexs, sizeof(vertexs));
			dc->Unmap(gpu_side_buffer[i], 0);
		}
	}

	//draw buffer
	Vcb->World = XMMatrixIdentity();
	//Device_Context->UpdateSubresource(VConstBuffer, 0, NULL, &VcBuffer, 0, 0);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	dc->VSSetConstantBuffers(0, 1, &vCB2GPU);

	////ZeroMemory(&VConstBuffer, sizeof(VConstBuffer));
	D3D11_MAPPED_SUBRESOURCE map;
	dc->Map(vCB2GPU, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, Vcb, sizeof(VertexWVP));
	dc->Unmap(vCB2GPU, 0);
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

	for (size_t i = 0; i < vert_count/2; i++)
	{
		dc->IASetVertexBuffers(0, 1, &gpu_side_buffer[i], &stride, &offset);
		//Device_Context->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
		dc->Draw(2, 0);
	}

	//reset to 0
	vert_count = 0;
}

AABB graphics_system::DebugRender::createAABB(XMFLOAT3 A, XMFLOAT3 B, XMFLOAT3 C)
{
	AABB temp;
	if (A.x > B.x)
	{
		if (A.x > C.x)
		{
			temp.maxX = A.x;
			if (B.x > C.x)
				temp.minX = C.x;
			else
				temp.minX = B.x;
		}
		else
		{
			temp.maxX = C.x;
			temp.minX = B.x;
		}
	}
	else
	{
		if (B.x > C.x)
		{
			temp.maxX = B.x;
			if (A.x > C.x)
				temp.minX = C.x;
			else
				temp.minX = A.x;
		}
		else
		{
			temp.maxX = C.x;
			temp.minX = A.x;
		}
	}

	if (A.y > B.y)
	{
		if (A.y > C.y)
		{
			temp.maxY = A.y;
			if (B.y > C.y)
				temp.minY = C.y;
			else
				temp.minY = B.y;
		}
		else
		{
			temp.maxY = C.y;
			temp.minY = B.y;
		}
	}
	else
	{
		if (B.y > C.y)
		{
			temp.maxY = B.y;
			if (A.y > C.y)
				temp.minY = C.y;
			else
				temp.minY = A.y;
		}
		else
		{
			temp.maxY = C.y;
			temp.minY = A.y;
		}
	}

	if (A.z > B.z)
	{
		if (A.z > C.z)
		{
			temp.maxZ = A.z;
			if (B.z > C.z)
				temp.minZ = C.z;
			else
				temp.minZ = B.z;
		}
		else
		{
			temp.maxZ = C.z;
			temp.minZ = B.z;
		}
	}
	else
	{
		if (B.z > C.z)
		{
			temp.maxZ = B.z;
			if (A.z > C.z)
				temp.minZ = C.z;
			else
				temp.minZ = A.z;
		}
		else
		{
			temp.maxZ = C.z;
			temp.minZ = A.z;
		}
	}

	temp.Center.x = 0.5f*(temp.maxX + temp.minX);
	temp.Center.y = 0.5f*(temp.maxY + temp.minY);
	temp.Center.z = 0.5f*(temp.maxZ + temp.minZ);
	return temp;
}

void graphics_system::DebugRender::DrawAABB(AABB a)
{
	Vertex temp[8];
	for (size_t i = 0; i < 8; i++)
	temp[i].Color=XMFLOAT4(1.0f, 1.0f, 0.5f, 1.0f);
	//top
	temp[0].Pos = XMFLOAT3(a.minX, a.maxY, a.minZ);
	temp[1].Pos = XMFLOAT3(a.maxX, a.maxY, a.minZ);
	temp[2].Pos = XMFLOAT3(a.maxX, a.maxY, a.maxZ);
	temp[3].Pos = XMFLOAT3(a.minX, a.maxY, a.maxZ);
	//bot
	temp[4].Pos = XMFLOAT3(a.minX, a.minY, a.minZ);
	temp[5].Pos = XMFLOAT3(a.maxX, a.minY, a.minZ);
	temp[6].Pos = XMFLOAT3(a.maxX, a.minY, a.maxZ);
	temp[7].Pos = XMFLOAT3(a.minX, a.minY, a.maxZ);

	add_line(temp[0], temp[1]); add_line(temp[2], temp[1]); add_line(temp[2], temp[3]); add_line(temp[0], temp[3]);
	add_line(temp[0], temp[4]); add_line(temp[1], temp[5]); add_line(temp[2], temp[6]); add_line(temp[3], temp[7]);
	add_line(temp[4], temp[5]); add_line(temp[5], temp[6]); add_line(temp[6], temp[7]); add_line(temp[4], temp[7]);
}
