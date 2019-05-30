#include "stdafx.h"
#include "GameEng.h"

float GameEng::angle = 0;
double GameEng::timercount = 0;
bool GameEng::speedup = false;

GameEng::GameEng()
{

}

GameEng::~GameEng()
{
}

#pragma region DirectX Init

void GameEng::InitViewport()
{
	ViewPort.MinDepth = 0.0f;
	ViewPort.MaxDepth = 1.0f;
	ViewPort.Width = Window_Width;
	ViewPort.Height = Window_Height;
	ViewPort.TopLeftX = 0.0f;
	ViewPort.TopLeftY = 0.0f;
}

void GameEng::SetPipelineState(pipeline_state_t* pipeline)
{
	PIP_index = *pipeline;
}

void GameEng::SetBufferToDefaultGraphics(ID3D11Buffer*& VertexBuffer, ID3D11Buffer*& IndexBuffer)
{
	//VertexBuffer = NULL;
	//IndexBuffer = NULL;

	Vertex vertexs[] =
	{
		//red
		//+X
		{ XMFLOAT3(0.5f, 0.5f,-0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f,-0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f, 0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		//-X
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f,-0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ XMFLOAT3(-0.5f,-0.5f, 0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ XMFLOAT3(-0.5f,-0.5f,-0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },

		//green
		//+Y
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f,-0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f, 0.5f,-0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		//-Y					 
		{ XMFLOAT3(-0.5f,-0.5f,-0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f,-0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(-0.5f,-0.5f, 0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f, 0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },

		//blue
		//+Z
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f, 0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f,-0.5f, 0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		//-Z				
		{ XMFLOAT3(-0.5f,-0.5f,-0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f,-0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f,-0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f, 0.5f,-0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },

	};

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(Vertex) * 24;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
	desc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = vertexs;

	Device->CreateBuffer(&desc, &data, &VertexBuffer);

	WORD index[] =
	{
		0,1,2,
		1,2,3,
		4,5,6,
		5,6,7,

		8,9,10,
		9,10,11,
		12,13,14,
		13,14,15,

		16,17,18,
		17,18,19,
		20,21,22,
		21,22,23
	};

	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = sizeof(WORD) * 36;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	ZeroMemory(&data, sizeof(data));
	data.pSysMem = index;

	Device->CreateBuffer(&desc, &data, &IndexBuffer);
}

void GameEng::SetBufferToDefaultGraphics(UINT vindex, UINT iindex)
{
	//VertexBuffer = NULL;
	//IndexBuffer = NULL;
	HRESULT hr = 0;
	Vertex vertexs[] =
	{
		//red
		//+X
		{ XMFLOAT3(0.5f, 0.5f,-0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f,-0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f, 0.5f),		XMFLOAT4(1.0f,0.0f,0.0f,1.0f) },
		//-X
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),		XMFLOAT4(0.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f,-0.5f),		XMFLOAT4(0.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f,-0.5f, 0.5f),		XMFLOAT4(0.0f,1.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f,-0.5f,-0.5f),		XMFLOAT4(0.0f,1.0f,1.0f,1.0f) },

		//green
		//+Y
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f,-0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f, 0.5f,-0.5f),		XMFLOAT4(0.0f,1.0f,0.0f,1.0f) },
		//-Y					 
		{ XMFLOAT3(-0.5f,-0.5f,-0.5f),		XMFLOAT4(1.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f,-0.5f),		XMFLOAT4(1.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f,-0.5f, 0.5f),		XMFLOAT4(1.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f, 0.5f),		XMFLOAT4(1.0f,0.0f,1.0f,1.0f) },

		//blue
		//+Z
		{ XMFLOAT3(0.5f, 0.5f, 0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f, 0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f, 0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		{ XMFLOAT3(-0.5f,-0.5f, 0.5f),		XMFLOAT4(0.0f,0.0f,1.0f,1.0f) },
		//-Z				
		{ XMFLOAT3(-0.5f,-0.5f,-0.5f),		XMFLOAT4(1.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f,-0.5f,-0.5f),		XMFLOAT4(1.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(-0.5f, 0.5f,-0.5f),		XMFLOAT4(1.0f,1.0f,0.0f,1.0f) },
		{ XMFLOAT3(0.5f, 0.5f,-0.5f),		XMFLOAT4(1.0f,1.0f,0.0f,1.0f) },
	};

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(Vertex) * 24;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
	desc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = vertexs;

	hr = Device->CreateBuffer(&desc, &data, &Vertex_Buffer[vindex]);

	WORD index[] =
	{
		0,1,2,
		2,1,3,
		4,5,6,
		6,5,7,

		8,9,10,
		10,9,11,
		12,13,14,
		14,13,15,

		16,17,18,
		18,17,19,
		22,21,20,
		23,21,22
	};

	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = sizeof(WORD) * 36;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	ZeroMemory(&data, sizeof(data));
	data.pSysMem = index;

	Device->CreateBuffer(&desc, &data, &Index_Buffer[iindex]);
}

void GameEng::Init_Device_DeviceContext_SwapChain(HWND* hwnd)
{
	DXGI_MODE_DESC modeDesc;
	DXGI_SWAP_CHAIN_DESC SCdesc;
	ZeroMemory(&modeDesc, sizeof(modeDesc));
	ZeroMemory(&SCdesc, sizeof(SCdesc));
	modeDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	RECT window;
	GetWindowRect(*hwnd, &window);

	modeDesc.Width = window.right - window.left;
	modeDesc.Height = window.bottom - window.top;
	modeDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	modeDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	modeDesc.RefreshRate = { 60,60 };

	SCdesc.BufferDesc = modeDesc;
	SCdesc.SampleDesc = { 1,0 };
	SCdesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SCdesc.BufferDesc.Width = window.right - window.left;
	SCdesc.BufferDesc.Height = window.bottom - window.top;
	SCdesc.BufferCount = 1;
	SCdesc.OutputWindow = *hwnd;
	SCdesc.Windowed = true;
	SCdesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SCdesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL lv[4];
	lv[0] = D3D_FEATURE_LEVEL_10_0;
	lv[1] = D3D_FEATURE_LEVEL_10_1;
	lv[2] = D3D_FEATURE_LEVEL_11_0;
	lv[3] = D3D_FEATURE_LEVEL_11_1;
#if _DEBUG
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		lv,
		4,
		D3D11_SDK_VERSION,
		&SCdesc,
		&SwapChain,
		&Device,
		NULL,
		&Device_Context);
#else
	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		lv,
		4,
		D3D11_SDK_VERSION,
		&SCdesc,
		&SwapChain,
		&Device,
		NULL,
		&Device_Context);
#endif
}

void GameEng::InitDepthStencilState(D3D11_DEPTH_STENCIL_DESC dsdesc)
{
	Device->CreateDepthStencilState(&dsdesc, Depth_Stencil_State);
}

void GameEng::InitDepthStencilView(HWND hwnd, D3D11_TEXTURE2D_DESC desc)
{
	ID3D11Texture2D *Buffer = 0;
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&Buffer);
	Device->CreateRenderTargetView(Buffer, 0, &Render_Target[PIP_index.render_target_index]);
	if (PIP_index.render_target_index != 253) PIP_index.render_target_index++;

	Device->CreateTexture2D(&desc, 0, &DepthStencilBuffer);
	Device->CreateDepthStencilView(DepthStencilBuffer, 0, &Depth_Stencil_View[PIP_index.depthStencilView_index]);
	if (PIP_index.depthStencilView_index != 253) PIP_index.depthStencilView_index++;
	Buffer->Release();
}

void GameEng::InitRasterizerState(D3D11_RASTERIZER_DESC desc)
{
	Device->CreateRasterizerState(&desc, &Raster_State[PIP_index.rasterState_index]);
	if (PIP_index.rasterState_index != 253) PIP_index.rasterState_index++;
}

void GameEng::InitSamplerState()
{
	D3D11_SAMPLER_DESC sdesc;
	ZeroMemory(&sdesc, sizeof(sdesc));
	sdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sdesc.MipLODBias;
	sdesc.MaxAnisotropy;
	sdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sdesc.BorderColor[4];
	sdesc.MinLOD = 0;
	sdesc.MaxLOD = D3D11_FLOAT32_MAX;
	HRESULT hr = Device->CreateSamplerState(&sdesc, &mSamplerState);

}

void GameEng::InitShaderAndInputLayout(const BYTE *ps, UINT ps_size, const BYTE *vs, UINT vs_size, D3D11_INPUT_ELEMENT_DESC* desc, UINT arraysize)
{
	HRESULT hr = 0;
	//D3D11_INPUT_ELEMENT_DESC layout[] =
	//{
	//	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "UV",			0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "TANGENT",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "WEIGHT",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	//{ "INDEX",		0, DXGI_FORMAT_R32G32B32A32_SINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};
	//UINT numElements = ARRAYSIZE(layout);
	Device->CreateVertexShader(vs, vs_size, NULL, &Vertex_Shader[PIP_index.vertex_shader_index]);
	Device->CreatePixelShader(ps, ps_size, NULL, &Pixel_Shader[PIP_index.pixel_shader_index]);
	hr = Device->CreateInputLayout(desc, arraysize, vs, vs_size, &Input_Layout[PIP_index.input_layout_index]);

	if (PIP_index.vertex_shader_index != 253)			PIP_index.vertex_shader_index++;
	if (PIP_index.pixel_shader_index != 253)			PIP_index.pixel_shader_index++;
	if (PIP_index.input_layout_index != 253)			PIP_index.input_layout_index++;
}

void GameEng::dXRelease()
{
	for (size_t i = 0; i < 256; i++)
	{
		if (Input_Layout[i] != NULL)					Input_Layout[i]->Release();
		if (Vertex_Shader[i] != NULL)					Vertex_Shader[i]->Release();
		if (Pixel_Shader[i] != NULL)					Pixel_Shader[i]->Release();
		if (Render_Target[i] != NULL)					Render_Target[i]->Release();
		if (Depth_Stencil_State[i] != NULL)				Depth_Stencil_State[i]->Release();
		if (Depth_Stencil_View[i] != NULL)				Depth_Stencil_View[i]->Release();
		if (Raster_State[i] != NULL)					Raster_State[i]->Release();
		if (Vertex_Buffer[i] != NULL)					Vertex_Buffer[i]->Release();
		if (Index_Buffer[i] != NULL)					Index_Buffer[i]->Release();
		if (ShaderResourceView[i] != NULL)				ShaderResourceView[i]->Release();
		if (Texture2D[i] != NULL)						Texture2D[i]->Release();
	}

	if (Device != NULL)									Device->Release();
	if (Device_Context != NULL)							Device_Context->Release();
	if (SwapChain != NULL)								SwapChain->Release();
	if (DepthStencilBuffer != NULL)						DepthStencilBuffer->Release();
	if (VConstBuffer != NULL)							VConstBuffer->Release();
	if (mSamplerState != NULL)							mSamplerState->Release();
	if (LightingCB != NULL)								LightingCB->Release();
	if (JointCB != NULL)								JointCB->Release();
	//testSRV->Release();
}

#pragma endregion

#pragma region Game Cycle

void GameEng::GameInit(HWND hwnd)
{
	Cube1.World.r[3].m128_f32[2] = 0.1f;
	D3D11_CREATE_DEVICE_FLAG flag = D3D11_CREATE_DEVICE_SINGLETHREADED;
#if _DEBUG
	flag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	this->hwnd = hwnd;
	RECT window;
	GetWindowRect(hwnd, &window);
	Window_Width = (float)(window.right - window.left);
	Window_Height = (float)(window.bottom - window.top);

	InitViewport();
	Init_Device_DeviceContext_SwapChain(&hwnd);
	D3D11_TEXTURE2D_DESC tex_desc;

	tex_desc.Width = (UINT)Window_Width;
	tex_desc.Height = (UINT)Window_Height;
	tex_desc.MipLevels = 1;
	tex_desc.ArraySize = 1;
	tex_desc.Format = DXGI_FORMAT_D32_FLOAT;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex_desc.CPUAccessFlags = 0;
	tex_desc.MiscFlags = 0;

	InitDepthStencilView(hwnd, tex_desc);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV",			0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "WEIGHT",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "INDEX",		0, DXGI_FORMAT_R32G32B32A32_UINT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	InitShaderAndInputLayout(PixelShader, sizeof(PixelShader), VertexShader, sizeof(VertexShader), layout, numElements);
	//Set buffers
	SetBufferToDefaultGraphics(0, 0);
	SetBufferToDefaultGraphics(1, 1);

	//#pragma region Terrain
	//	//Import Meshes
	//	Terrain.V_Buffer_index = 20; Terrain.I_Buffer_index = 20;
	//	Meshimport_BIN(Terrain,"terrain.bin");
	//
	//	int totalTri = Terrain.pos.size() / 3;
	//	for (size_t i = 0; i < totalTri; i++)
	//	{
	//		Terrain.WVP.World = XMMatrixTranslation(-30.0f, -15.0f, -30.0f);
	//		XMFLOAT3 p1 = Terrain.pos[i * 3], p2 = Terrain.pos[i * 3+1], p3 = Terrain.pos[i * 3+2];
	//		XMVECTOR n1 = XMLoadFloat3(&Terrain.norms[i * 3]), n2 = XMLoadFloat3(&Terrain.norms[i * 3 + 1]), n3 = XMLoadFloat3(&Terrain.norms[i * 3 + 2]);
	//		XMVECTOR temp= XMVector4Transform(XMVectorSet(p1.x,p1.y,p1.z,1.0f), Terrain.WVP.World);
	//		XMStoreFloat3(&p1, temp);
	//		temp = XMVector4Transform(XMVectorSet(p2.x, p2.y, p2.z, 1.0f), Terrain.WVP.World);
	//		XMStoreFloat3(&p2, temp);
	//		temp = XMVector4Transform(XMVectorSet(p3.x, p3.y, p3.z, 1.0f), Terrain.WVP.World);
	//		XMStoreFloat3(&p3, temp);
	//		XMFLOAT3 temppos;
	//		temppos.x = (p1.x + p2.x + p3.x) / 3.0f;
	//		temppos.y = (p1.y + p2.y + p3.y) / 3.0f;
	//		temppos.z = (p1.z + p2.z + p3.z) / 3.0f;
	//		_BVH.PushTerrainCent(temppos);
	//
	//		XMVECTOR tempnorm = XMVector3Normalize(XMVector3Cross(XMVectorSubtract( n2, n1), XMVectorSubtract( n3, n2)));
	//		_BVH.PushTerrainNorm(tempnorm);
	//		_BVH.PushAABB(DR.createAABB(p1, p2, p3));
	//	}
	//		_BVH.BuildTree();
	//#pragma endregion

	Terrain.V_Buffer_index = 20; Terrain.I_Buffer_index = 20;
	Bear.V_Buffer_index = 11; Bear.I_Buffer_index = 11;
	//Meshimport_BIN2(Terrain, "Idle_test",1.0f,1.0f,1.0f);
	FBXLoader("Teddy_Idle_test", &Anim_Idle, Bear, 1.0f, 1.0f, 1.0f);
	FBXLoader("Teddy_Run_test", &Anim_Walk, Bear, 1.0f, 1.0f, 1.0f);
	//AnimationLoader("Teddy_Run_test", &Anim_Walk);
	//AnimationLoader("Teddy_Idle_test", &Anim_Idle);
	Bear_Pos = XMMatrixIdentity();
	CurrentAnimation = &Anim_Idle;
	//Meshimport_BIN2(Bear, "Teddy_test",0.17f,0.17f,0.17f);
	CreateWICTextureFromFile(Device, L"Teddy_D.png", (ID3D11Resource**)&Texture2D[4], &ShaderResourceView[4]);
#pragma region SetConstBuffer
	D3D11_BUFFER_DESC cbdesc;
	ZeroMemory(&cbdesc, sizeof(cbdesc));

	cbdesc.ByteWidth = sizeof(VertexWVP);
	cbdesc.Usage = D3D11_USAGE_DYNAMIC;
	cbdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbdesc.MiscFlags = 0;
	cbdesc.StructureByteStride = 0;
	Device->CreateBuffer(&cbdesc, NULL, &VConstBuffer);

	ZeroMemory(&cbdesc, sizeof(cbdesc));
	cbdesc.ByteWidth = sizeof(Lighting);
	cbdesc.Usage = D3D11_USAGE_DYNAMIC;
	cbdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbdesc.MiscFlags = 0;
	cbdesc.StructureByteStride = 0;
	Device->CreateBuffer(&cbdesc, NULL, &LightingCB);

	ZeroMemory(&cbdesc, sizeof(cbdesc));
	cbdesc.ByteWidth = sizeof(XMMATRIX)*60;
	cbdesc.Usage = D3D11_USAGE_DYNAMIC;
	cbdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbdesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbdesc.MiscFlags = 0;
	cbdesc.StructureByteStride = 0;
	Device->CreateBuffer(&cbdesc, NULL, &JointCB);
#pragma endregion

	Device_Context->OMSetRenderTargets(1, &Render_Target[0], Depth_Stencil_View[0]);
	Device_Context->RSSetViewports(1, &ViewPort);

#pragma region MyRegion
	WORD index[] =
	{
		0,1,
		2,3,
		0,2,
		3,1,

		4,5,
		6,7,
		4,6,
		7,5,

		8,9,
		10,11,
		8,10,
		11,9,

		12,13,
		14,15,
		12,14,
		15,13,

		16,17,
		18,19,
		16,18,
		19,17,

		20,21,
		22,23,
		20,22,
		23,21
	};

	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = sizeof(WORD) * 48;
	desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = index;

	Device->CreateBuffer(&desc, &data, &Index_Buffer[2]);
#pragma endregion
	InitSamplerState();
	CreateWICTextureFromFile(Device, L"PPG_3D_Player_D.png", (ID3D11Resource**)&Texture2D[0], &ShaderResourceView[0]);
	CreateWICTextureFromFile(Device, L"PPG_3D_Player_N.png", (ID3D11Resource**)&Texture2D[1], &ShaderResourceView[1]);
	CreateWICTextureFromFile(Device, L"PPG_3D_Player_emissive.png", (ID3D11Resource**)&Texture2D[2], &ShaderResourceView[2]);
	CreateWICTextureFromFile(Device, L"PPG_3D_Player_spec.png", (ID3D11Resource**)&Texture2D[3], &ShaderResourceView[3]);
	//TextureLoader(Device, L"PPG_3D_Player_D.png", Texture2D[0], testSRV);
}

void GameEng::GameUpdate()
{
	time.Signal();
	angle += t;

	KeyPressControl();
	//Matrix();
#pragma region cube1

	Cube1.World = XMMatrixMultiply(XMMatrixTranslation(CubeWorld.World[0], CubeWorld.World[1], CubeWorld.World[2]), Cube1.World);
	Cube1.World = XMMatrixMultiply(XMMatrixRotationY(CubeWorld.Rotate[1]), Cube1.World);
#pragma region View Proj set
	XMVECTOR pos = XMVectorSet(Cam_Pos[0], Cam_Pos[1], Cam_Pos[2], Cam_Pos[3]);
	XMVECTOR at = XMVectorSet(Cam_Look[0], Cam_Look[1], Cam_Look[2], Cam_Look[3]);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//pos = XMVector4Transform(pos,Cube1.World);
	mView = Look_AT(pos, at, up);
	mView = Mouse_Move(mView, Con.getMouseX(), Con.getMouseY());
	mProjection = XMMatrixPerspectiveFovLH(FOV*Con.getMouseWheel(), Window_Width / Window_Height, 0.1f, 1000.0f);
#pragma endregion
	Cube1.View = mView;
	Cube1.Proj = mProjection;
	DR.add_3axis(Cube1);
#pragma endregion

	Origin.World = XMMatrixIdentity();
	Origin.View = mView;
	Origin.Proj = mProjection;
	DR.add_3axis(Origin);

	//#pragma region VF
	//	ViewFrustum(Cube1);
	//#pragma endregion

#pragma region Mage
	Mage.World = Cube1.World;
	Mage.World.r[3].m128_f32[2] -= 5.0f;
	Mage.World = XMMatrixMultiply(Mage.World, XMMatrixRotationY(CubeWorld.Rotate[1]));
	Mage.View = mView;
	Mage.Proj = mProjection;

	Lighting.PointLightColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	XMStoreFloat4(&(Lighting.PointLightPos), Cube1.World.r[3]);
	Lighting.PointLightRange = 100.0f;
	XMStoreFloat4(&Lighting.CamPos, pos);
#pragma endregion

#pragma region cube3
	Cube3.World = XMMatrixIdentity();
	Cube3.World = XMMatrixMultiply(Cube3.World, XMMatrixTranslation(Cube3World.World[0], Cube3World.World[1], Cube3World.World[2]));
	Cube3.View = mView;
	Cube3.Proj = mProjection;
	//DR.add_3axis(Mage);
#pragma endregion

#pragma region Terrain
	Terrain.WVP.View = mView;
	Terrain.WVP.Proj = mProjection;
	//for (size_t i = 0; i < TerrainAABB.size(); i++)
	//{
	//	DR.DrawAABB(TerrainAABB[i]);
	//}
	AABB cubeAABB;
	cubeAABB.maxX = Cube1.World.r[3].m128_f32[0] + 0.5f;
	cubeAABB.minX = Cube1.World.r[3].m128_f32[0] - 0.5f;
	cubeAABB.maxY = Cube1.World.r[3].m128_f32[1] + 0.5f;
	cubeAABB.minY = Cube1.World.r[3].m128_f32[1] - 0.5f;
	cubeAABB.maxZ = Cube1.World.r[3].m128_f32[2] + 0.5f;
	cubeAABB.minZ = Cube1.World.r[3].m128_f32[2] - 0.5f;

	//_BVH.Recursive(cubeAABB,_BVH.Root,&DR);
#pragma endregion

#pragma region Bear
	Bear.WVP.World = Bear_Pos;
	Bear.WVP.World = XMMatrixMultiply(Bear.WVP.World, XMMatrixScaling(0.17f,0.17f, 0.17f));
	Bear.WVP.View = mView;
	Bear.WVP.Proj = mProjection;

	if (IsWalking == true)
	{
		if (CurrentAnimation != &Anim_Walk)
			AnimationTransition(CurrentAnimation, &Anim_Walk);
		else
			RunAnimation(&Anim_Walk);
	}
	else
	{
		if (CurrentAnimation != &Anim_Idle)
			AnimationTransition(CurrentAnimation, &Anim_Idle);
		else
			RunAnimation(&Anim_Idle);
	}
	for (size_t i = 0; i <CurrentAnimation->CurrJoints.size(); i++)
	{
		JointtoCB[i] = XMMatrixMultiply(CurrentAnimation->frames[0].Joints[i], CurrentAnimation->CurrJoints[i]);
		JointtoCB[i] = XMMatrixTranspose(JointtoCB[i]);
	}
	D3D11_MAPPED_SUBRESOURCE map;
	Device_Context->Map(JointCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, &JointtoCB, sizeof(XMMATRIX)*60);
	Device_Context->Unmap(JointCB, 0);
	
	//if (IsWalking == true)
	//{
	//	if (CurrentAnimation != &Anim_Walk)
	//		AnimationTransition(CurrentAnimation, &Anim_Walk);
	//	else
	//		RunAnimation(&Anim_Walk);
	//}
	//else
	//{
	//	if (CurrentAnimation != &Anim_Idle)
	//		AnimationTransition(CurrentAnimation, &Anim_Idle);
	//	else
	//		RunAnimation(&Anim_Idle);
	//}
#pragma endregion


	//VcBuffer.World = XMMatrixTranspose(World);
	//VcBuffer.View = XMMatrixTranspose(View);
	//VcBuffer.Proj = XMMatrixTranspose(Projection);
	//D3D11_MAPPED_SUBRESOURCE map;
	//Device_Context->VSSetConstantBuffers(0, 1, &VConstBuffer);

	////ZeroMemory(&VConstBuffer, sizeof(VConstBuffer));
	//Device_Context->Map(VConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	//memcpy(map.pData, &VcBuffer, sizeof(VcBuffer));
	//Device_Context->Unmap(VConstBuffer, 0);

	Device_Context->VSSetShader(Vertex_Shader[0], NULL, 0);
	Device_Context->PSSetShader(Pixel_Shader[0], NULL, 0);
}

void GameEng::GameRender()
{
	float rgba[4] = gray;
	Device_Context->ClearRenderTargetView(Render_Target[0], rgba);
	Device_Context->ClearDepthStencilView(Depth_Stencil_View[0], D3D11_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
	Device_Context->IASetInputLayout(Input_Layout[0]);

	//DrawObject(Cube1, 0, 0, 36, D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

//	DrawObject(Mage, 1, 1, 36, D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	/*if(isInVF(Mage))

	else
		DrawObject(Mage, 1, 2, 36, D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

	if (isInVF(Cube3))
		DrawObject(Cube3, 1, 1, 36, D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	else
		DrawObject(Cube3, 1, 2, 36, D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST);*/
	Lighting.Mode = 1;
	D3D11_MAPPED_SUBRESOURCE map;
	Device_Context->Map(LightingCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, &Lighting, sizeof(Lighting));
	Device_Context->Unmap(LightingCB, 0);

	Device_Context->PSSetSamplers(0, 1, &mSamplerState);
	Device_Context->PSSetShaderResources(0, 1, &ShaderResourceView[0]);
	Device_Context->PSSetShaderResources(1, 1, &ShaderResourceView[1]);
	Device_Context->PSSetShaderResources(2, 1, &ShaderResourceView[2]);
	Device_Context->PSSetShaderResources(3, 1, &ShaderResourceView[3]);
	Device_Context->PSSetConstantBuffers(0, 1, &LightingCB);
	DrawObject(Terrain.WVP, Terrain.V_Buffer_index, Terrain.I_Buffer_index, 0, D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	Lighting.Mode = 2;
	Device_Context->Map(LightingCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, &Lighting, sizeof(Lighting));
	Device_Context->Unmap(LightingCB, 0);

	Device_Context->PSSetShaderResources(0, 1, &ShaderResourceView[4]);
	Device_Context->VSSetConstantBuffers(1, 1, &JointCB);
	DrawObject(Bear.WVP, Bear.V_Buffer_index, Bear.I_Buffer_index, Bear.I_Buffer_Size, D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Lighting.Mode = 3;
	//	D3D11_MAPPED_SUBRESOURCE map;
	Device_Context->Map(LightingCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, &Lighting, sizeof(Lighting));
	Device_Context->Unmap(LightingCB, 0);

	DR.flush(Device, Device_Context, VConstBuffer, &VcBuffer);
	SwapChain->Present(0, 0);
}

void GameEng::GameShutdown()
{
	dXRelease();
}

#pragma endregion

#pragma region Control

void GameEng::KeyPressControl()
{
	t = (float)time.Delta()*5.0f;
	CubeWorld.Rotate[1] = 0;
	IsWalking = false;

	if (Con.isKeyPress(VK_SHIFT) == true)
	{
		speedup = true;
	}
	if (Con.isKeyPress(VK_SHIFT) == false)
	{
		speedup = false;
	}

	if (speedup)
		t2 = t * 10.0f;
	else
		t2 = t * 5.0f;
	t2 *= 5.0f;

	//if (Con.isKeyPress('W') == true)
	//	Cube1.World = XMMatrixMultiply(XMMatrixTranslation(0, 0, t2), Cube1.World);
	//if (Con.isKeyPress('S') == true)
	//	Cube1.World = XMMatrixMultiply(XMMatrixTranslation(0, 0, -t2), Cube1.World);
	//if (Con.isKeyPress('A') == true)
	//{
	//	Cube1.World = XMMatrixMultiply(XMMatrixRotationY(-t2), Cube1.World);
	//	Mage.World = XMMatrixMultiply(XMMatrixRotationY(-t2), Mage.World);
	//	CubeWorld.Rotate[1]-=t2;
	//}	
	//if (Con.isKeyPress('D') == true)
	//Cube1.World = XMMatrixMultiply(XMMatrixRotationY(t2), Cube1.World);

	if (Con.isKeyPress('W') == true)
	{
		IsWalking = true;
		Bear_Pos = XMMatrixMultiply(XMMatrixTranslation(0, 0, t2), Bear_Pos);
	}
	if (Con.isKeyPress('S') == true)
	{
		IsWalking = true;
		Bear_Pos = XMMatrixMultiply(XMMatrixTranslation(0, 0, -t2), Bear_Pos);
	}
	if (Con.isKeyPress('A') == true)
	{
		IsWalking = true;
		Bear_Pos = XMMatrixMultiply(XMMatrixRotationY(-t / 2.0f), Bear_Pos);
	}
	if (Con.isKeyPress('D') == true)
	{
		IsWalking = true;
		Bear_Pos = XMMatrixMultiply(XMMatrixRotationY(t / 2.0f), Bear_Pos);
	}

	if (Con.isKeyPress('Q') == true)
	{
		Cube1.World = XMMatrixMultiply(XMMatrixTranslation(0, t2, 0), Cube1.World);
	}
	if (Con.isKeyPress('E') == true)
	{
		Cube1.World = XMMatrixMultiply(XMMatrixTranslation(0, -t2, 0), Cube1.World);
	}

	if (Con.isKeyPress(VK_UP) == true) //UP
	{
		VF_far += t;
	}
	if (Con.isKeyPress(VK_DOWN) == true) //DOWN
	{
		VF_far -= t;
	}
	if (Con.isKeyPress(VK_LEFT) == true) //LEFT
	{
		VF_fov += t;
	}
	if (Con.isKeyPress(VK_RIGHT) == true) //RIGHT
	{
		VF_fov -= t;
	}

	if (Con.isKeyPress(VK_NUMPAD8) == true) //Front
	{
		Cam_Pos[2] += t2;
		Cam_Look[2] += t2;
	}
	if (Con.isKeyPress(VK_NUMPAD2) == true) //Back
	{
		Cam_Pos[2] -= t2;
		Cam_Look[2] -= t2;
	}
	if (Con.isKeyPress(VK_NUMPAD4) == true) //LEFT
	{
		Cam_Pos[0] -= t2;
		Cam_Look[0] -= t2;
	}
	if (Con.isKeyPress(VK_NUMPAD6) == true) //RIGHT
	{
		Cam_Pos[0] += t2;
		Cam_Look[0] += t2;
	}
	if (Con.isKeyPress(VK_NUMPAD7) == true) //UP
	{
		Cam_Pos[1] += t2;
		//Cam_Look[1] -= t;
	}
	if (Con.isKeyPress(VK_NUMPAD9) == true) //DOWN
	{
		Cam_Pos[1] -= t2;
		//Cam_Look[1] += t;
	}

	if (Con.isKeyPress('1') == true)
	{
		Lighting.Mode = 1;
	}
	if (Con.isKeyPress('2') == true)
	{
		Lighting.Mode = 2;
	}
}

#pragma endregion

#pragma region Mesh/Object

#pragma region Mesh/Texture Loader
#if 0
void GameEng::Meshimport_BIN(Mesh& mesh, const char * path)
{
	ifstream f;
	f.open(path, ios::binary | ios::in);
	if (f.is_open())
	{
		uint32_t				vert_count;			// Number of vertices 
		f.seekg(0, f.end);
		int length = f.tellg();
		f.seekg(0, f.beg);

		char* Buffer = new char[length];
		f.read(Buffer, length);

		memcpy(&vert_count, Buffer, sizeof(uint32_t));

		Vertex* vertexs = new Vertex[vert_count];

		int v_size = sizeof(XMFLOAT3) + sizeof(XMFLOAT3) + sizeof(XMFLOAT2);
		for (size_t i = 0; i < vert_count; i++)
		{
			XMFLOAT3 tempPos, tempNorm;
			XMFLOAT2 tempUV;

			memcpy(&tempPos, &Buffer[sizeof(XMFLOAT3)*i + 4], sizeof(XMFLOAT3));
			vertexs[i].Pos = tempPos;
			memcpy(&tempNorm, &Buffer[sizeof(XMFLOAT3)*vert_count + sizeof(XMFLOAT3)*i + 4], sizeof(XMFLOAT3));
			vertexs[i].Color = XMFLOAT4(tempNorm.x, tempNorm.y, tempNorm.z, 1.0f);
			memcpy(&tempUV, &Buffer[sizeof(XMFLOAT3)*vert_count * 2 + sizeof(XMFLOAT2)*i + 4], sizeof(XMFLOAT2));

			mesh.pos.push_back(tempPos);
			mesh.norms.push_back(tempNorm);
			mesh.uvs.push_back(tempUV);
		}
		f.close();

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(Vertex) * vert_count;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
		desc.StructureByteStride = sizeof(Vertex);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertexs;

		Device->CreateBuffer(&desc, &data, &Vertex_Buffer[mesh.V_Buffer_index]);
		mesh.V_Buffer_Size = vert_count;

		WORD* index = new WORD[vert_count];
		for (size_t i = 0; i < vert_count; i++)
		{
			index[i] = i;
		}

		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(WORD) * vert_count;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

		ZeroMemory(&data, sizeof(data));
		data.pSysMem = index;

		Device->CreateBuffer(&desc, &data, &Index_Buffer[mesh.I_Buffer_index]);



		mesh.I_Buffer_Size = vert_count;

		delete[] index;
		delete[] vertexs;
		delete[] Buffer;



	}
	else
		cout << "Cant Open";
}
void GameEng::Meshimport_BIN2(Mesh & mesh, const char * path,float scalerX,float scalerY,float scalerZ)
{
	ifstream f;
	f.open(path, ios::binary | ios::in);
	if (f.is_open())
	{
		int				vert_count;			// Number of vertices 

		f.read((char*)&vert_count, sizeof(int));
		//vert_count = 3000;

		Vertex* vertexs = new Vertex[vert_count];

		for (size_t i = 0; i < vert_count; i++)
		{
			XMFLOAT4 tempPos, tempNorm, tempUV, tempTangent, tempweight;
			int tempindex[4];
			

			/*memcpy(&tempPos, &Buffer[sizeof(XMFLOAT4)*i + 4], sizeof(XMFLOAT3));
			vertexs[i].Pos = tempPos;
			memcpy(&tempNorm, &Buffer[sizeof(XMFLOAT4)*vert_count + sizeof(XMFLOAT4)*i + 4], sizeof(XMFLOAT3));
			vertexs[i].Color = XMFLOAT4(tempNorm.x, tempNorm.y, tempNorm.z, 1.0f);*/

			f.read((char*)&tempPos, sizeof(XMFLOAT4));
			f.read((char*)&tempweight, sizeof(XMFLOAT4));
			f.read((char*)&tempindex, sizeof(int)*4);
			f.read((char*)&tempNorm, sizeof(XMFLOAT4));
			f.read((char*)&tempUV, sizeof(XMFLOAT4));
			f.read((char*)&tempTangent, sizeof(XMFLOAT4));

			//mesh.pos.push_back(tempPos);
			//mesh.norms.push_back(tempNorm);

			//tempPos *= XMMatrixScaling(scalerX, scalerY, scalerZ);

			vertexs[i].Pos.x = tempPos.x*scalerX;
			vertexs[i].Pos.y = tempPos.y*scalerY;
			vertexs[i].Pos.z = tempPos.z*scalerZ;
			vertexs[i].Color = tempNorm;

			vertexs[i].weight[0] = tempweight.x;
			vertexs[i].weight[1] = tempweight.y;
			vertexs[i].weight[2] = tempweight.z;
			vertexs[i].weight[3] = tempweight.w;

			vertexs[i].index[0] = tempindex[0];
			vertexs[i].index[1] = tempindex[1];
			vertexs[i].index[2] = tempindex[2];
			vertexs[i].index[3] = tempindex[3];

			vertexs[i].UV.x = tempUV.x;
			vertexs[i].UV.y = 1.0f - tempUV.y;

			vertexs[i].Normal.x = tempNorm.x;
			vertexs[i].Normal.y = tempNorm.y;
			vertexs[i].Normal.z = tempNorm.z;

			vertexs[i].Tangent.x = tempTangent.x;
			vertexs[i].Tangent.y = tempTangent.y;
			vertexs[i].Tangent.z = tempTangent.z;
		}
		int Mat_Count;
		XMFLOAT4 temp;
		f.read((char*)&Mat_Count, sizeof(int));
		f.read((char*)&temp, sizeof(XMFLOAT4));
		Lighting.Emissive.x = temp.x;
		Lighting.Emissive.y = temp.y;
		Lighting.Emissive.z = temp.z;
		Lighting.Emissive.w = temp.w;

		f.read((char*)&temp, sizeof(XMFLOAT4));
		Lighting.Diffuse.x = temp.x;
		Lighting.Diffuse.y = temp.y;
		Lighting.Diffuse.z = temp.z;
		Lighting.Diffuse.w = temp.w;

		f.read((char*)&temp, sizeof(XMFLOAT4));
		Lighting.Ambient.x = temp.x;
		Lighting.Ambient.y = temp.y;
		Lighting.Ambient.z = temp.z;
		Lighting.Ambient.w = temp.w;

		f.read((char*)&temp, sizeof(XMFLOAT4));
		Lighting.Specular.x = temp.x;
		Lighting.Specular.y = temp.y;
		Lighting.Specular.z = temp.z;
		Lighting.Specular.w = temp.w;


		f.close();

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = sizeof(Vertex) * vert_count;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
		desc.StructureByteStride = sizeof(Vertex);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertexs;

		Device->CreateBuffer(&desc, &data, &Vertex_Buffer[mesh.V_Buffer_index]);
		mesh.V_Buffer_Size = vert_count;

		WORD* index = new WORD[vert_count];
		for (size_t i = 0; i < vert_count; i++)
		{
			index[i] = i;
		}

		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(WORD) * vert_count;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

		ZeroMemory(&data, sizeof(data));
		data.pSysMem = index;

		Device->CreateBuffer(&desc, &data, &Index_Buffer[mesh.I_Buffer_index]);

		mesh.I_Buffer_Size = vert_count;

		delete[] index;
		delete[] vertexs;
	}
	else
		cout << "Cant Open";
}
#endif

void GameEng::TextureLoader(ID3D11Device * mDevice, const wchar_t * path, ID3D11Texture2D* texture, ID3D11ShaderResourceView * SRV)
{
	HRESULT hr = CreateWICTextureFromFile(mDevice, path, (ID3D11Resource**)&texture, &SRV);

}

void GameEng::FBXLoader(const char* path, Anim_Clip* _Clip,Mesh & mesh,float scalerX,float scalerY,float scalerZ)
{
	ifstream f;
	f.open(path, ios::binary | ios::in);
	if (f.is_open())
	{
		int	Joint_count, keyFramesize;			// Number of vertices 
		double duration;
		f.read((char*)&Joint_count, sizeof(int));
		f.read((char*)&keyFramesize, sizeof(int));
		f.read((char*)&duration, sizeof(double));
		_Clip->duration = duration;

		for (size_t i = 0; i < Joint_count; i++)
		{
			int whoismyrealmom;
			f.read((char*)&whoismyrealmom, sizeof(int));
			_Clip->parentlist.push_back(whoismyrealmom);
		}
		for (size_t key = 0; key < keyFramesize; key++)
		{
			Keyframe tempframe;
			double ttime;
			f.read((char*)&ttime, sizeof(double));
			tempframe.time = ttime;
			for (size_t joint = 0; joint < Joint_count; joint++)
			{
				XMMATRIX matrix;
				f.read((char*)&matrix, sizeof(XMMATRIX));
				matrix = XMMatrixMultiply(matrix, XMMatrixScaling(scalerX, scalerY, scalerZ));
				tempframe.Joints.push_back(matrix);
			}
			_Clip->frames.push_back(tempframe);
		}
		//inverse bind pose
		for (size_t i = 0; i < Joint_count; i++)
		{
			_Clip->frames[0].Joints[i] = XMMatrixInverse(NULL, _Clip->frames[0].Joints[i]);
		}

#pragma region Vertexs
		int				vert_count;			// Number of vertices 

		f.read((char*)&vert_count, sizeof(int));
		//vert_count = 3000;

		mesh.VertexToGPU = new Vertex[vert_count];

		for (size_t i = 0; i < vert_count; i++)
		{
			XMFLOAT4 tempPos, tempNorm, tempUV, tempTangent;
			int tempindex[4];
			float tempweight[4];
			/*memcpy(&tempPos, &Buffer[sizeof(XMFLOAT4)*i + 4], sizeof(XMFLOAT3));
			vertexs[i].Pos = tempPos;
			memcpy(&tempNorm, &Buffer[sizeof(XMFLOAT4)*vert_count + sizeof(XMFLOAT4)*i + 4], sizeof(XMFLOAT3));
			vertexs[i].Color = XMFLOAT4(tempNorm.x, tempNorm.y, tempNorm.z, 1.0f);*/

			f.read((char*)&tempPos, sizeof(XMFLOAT4));
			f.read((char*)&tempNorm, sizeof(XMFLOAT4));
			f.read((char*)&tempUV, sizeof(XMFLOAT4));
			f.read((char*)&tempTangent, sizeof(XMFLOAT4));
			f.read((char*)&tempweight, sizeof(XMFLOAT4));
			f.read((char*)&tempindex, sizeof(int)*4);

			//mesh.pos.push_back(tempPos);
			//mesh.norms.push_back(tempNorm);

			//tempPos *= XMMatrixScaling(scalerX, scalerY, scalerZ);

			tempPos.x *= scalerX;
			tempPos.y*=scalerY;
			tempPos.z*=scalerZ;

			mesh.VertexToGPU[i].Pos.x = tempPos.x;
			mesh.VertexToGPU[i].Pos.y = tempPos.y;
			mesh.VertexToGPU[i].Pos.z = tempPos.z;
			mesh.VertexToGPU[i].Color = tempNorm;

			mesh.VertexToGPU[i].UV.x = tempUV.x;
			mesh.VertexToGPU[i].UV.y = 1.0f - tempUV.y;

			mesh.VertexToGPU[i].Normal.x = tempNorm.x;
			mesh.VertexToGPU[i].Normal.y = tempNorm.y;
			mesh.VertexToGPU[i].Normal.z = tempNorm.z;

			//mesh.VertexToGPU[i].Tangent.x = tempTangent.x;
			//mesh.VertexToGPU[i].Tangent.y = tempTangent.y;
			//mesh.VertexToGPU[i].Tangent.z = tempTangent.z;
			mesh.VertexToGPU[i].index[0] = (unsigned int)tempindex[0];
			mesh.VertexToGPU[i].index[1] = (unsigned int)tempindex[1];
			mesh.VertexToGPU[i].index[2] = (unsigned int)tempindex[2];
			mesh.VertexToGPU[i].index[3] = (unsigned int)tempindex[3];

			mesh.VertexToGPU[i].weight[0] = tempweight[0];
			mesh.VertexToGPU[i].weight[1] = tempweight[1];
			mesh.VertexToGPU[i].weight[2] = tempweight[2];
			mesh.VertexToGPU[i].weight[3] = tempweight[3];

			Simple_Vertex tempvert;
			tempvert.Pos = tempPos;
			tempvert.Norm = XMFLOAT3(tempNorm.x, tempNorm.y, tempNorm.z);
			tempvert.UV = XMFLOAT2(tempUV.x, 1.0f - tempUV.y);
			//tempvert.Tangent = mesh.VertexToGPU[i].Tangent;
			tempvert.weight[0] = tempweight[0];
			tempvert.weight[1] = tempweight[1];
			tempvert.weight[2] = tempweight[2];
			tempvert.weight[3] = tempweight[3];

			tempvert.index[0] = (unsigned int)tempindex[0];
			tempvert.index[1] = (unsigned int)tempindex[1];
			tempvert.index[2] = (unsigned int)tempindex[2];
			tempvert.index[3] = (unsigned int)tempindex[3];
			mesh.ConstVertex.push_back(tempvert);
		}
#pragma region Material
		int Mat_Count;
		XMFLOAT4 temp;
		f.read((char*)&Mat_Count, sizeof(int));
		f.read((char*)&temp, sizeof(XMFLOAT4));
		Lighting.Emissive.x = temp.x;
		Lighting.Emissive.y = temp.y;
		Lighting.Emissive.z = temp.z;
		Lighting.Emissive.w = temp.w;

		f.read((char*)&temp, sizeof(XMFLOAT4));
		Lighting.Diffuse.x = temp.x;
		Lighting.Diffuse.y = temp.y;
		Lighting.Diffuse.z = temp.z;
		Lighting.Diffuse.w = temp.w;

		f.read((char*)&temp, sizeof(XMFLOAT4));
		Lighting.Ambient.x = temp.x;
		Lighting.Ambient.y = temp.y;
		Lighting.Ambient.z = temp.z;
		Lighting.Ambient.w = temp.w;

		f.read((char*)&temp, sizeof(XMFLOAT4));
		Lighting.Specular.x = temp.x;
		Lighting.Specular.y = temp.y;
		Lighting.Specular.z = temp.z;
		Lighting.Specular.w = temp.w;
#pragma endregion
		f.close();

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags= D3D11_CPU_ACCESS_WRITE;
		desc.ByteWidth = sizeof(Vertex) * vert_count;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.StructureByteStride = sizeof(Vertex);

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = mesh.VertexToGPU;

		Device->CreateBuffer(&desc, &data, &Vertex_Buffer[mesh.V_Buffer_index]);
		mesh.V_Buffer_Size = vert_count;

		WORD* index = new WORD[vert_count];
		for (size_t i = 0; i < vert_count; i++)
		{
			index[i] = i;
		}

		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(WORD) * vert_count;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

		ZeroMemory(&data, sizeof(data));
		data.pSysMem = index;

		Device->CreateBuffer(&desc, &data, &Index_Buffer[mesh.I_Buffer_index]);

		mesh.I_Buffer_Size = vert_count;

		delete[] index;
#pragma endregion
		f.close();
	}
	else
		cout << "Cant Open";
}

#pragma endregion

void GameEng::DrawObject(VertexWVP WVP, int V_buffer_index, int I_buffer_index, int index_size, D3D11_PRIMITIVE_TOPOLOGY top)
{
	VcBuffer.World = XMMatrixTranspose(WVP.World);
	VcBuffer.View = XMMatrixTranspose(WVP.View);
	VcBuffer.Proj = XMMatrixTranspose(WVP.Proj);
	//Device_Context->UpdateSubresource(VConstBuffer, 0, NULL, &VcBuffer, 0, 0);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Device_Context->VSSetConstantBuffers(0, 1, &VConstBuffer);

	////ZeroMemory(&VConstBuffer, sizeof(VConstBuffer));
	D3D11_MAPPED_SUBRESOURCE map;
	Device_Context->Map(VConstBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);
	memcpy(map.pData, &VcBuffer, sizeof(VcBuffer));
	Device_Context->Unmap(VConstBuffer, 0);
	Device_Context->IASetVertexBuffers(0, 1, &Vertex_Buffer[V_buffer_index], &stride, &offset);
	Device_Context->IASetIndexBuffer(Index_Buffer[I_buffer_index], DXGI_FORMAT_R16_UINT, 0);
	Device_Context->IASetPrimitiveTopology(top);
	Device_Context->DrawIndexed(index_size, 0, 0);
}

void GameEng::ViewFrustum(VertexWVP wvp)
{
	VF_WVP = wvp;
	float
		xf = tan(VF_fov / 2)*VF_far*VF_viewRatio,
		yf = tan(VF_fov / 2)*VF_far,
		zf = VF_far,
		xn = tan(VF_fov / 2)*VF_near*VF_viewRatio,
		yn = tan(VF_fov / 2)*VF_near,
		zn = VF_near;

	//far TL TR BL BR
	XMStoreFloat3(&VF_vertexs[0].Pos, XMVector3Transform(XMLoadFloat3(&XMFLOAT3(-xf, yf, zf)), wvp.World));
	XMStoreFloat3(&VF_vertexs[1].Pos, XMVector3Transform(XMLoadFloat3(&XMFLOAT3(xf, yf, zf)), wvp.World));
	XMStoreFloat3(&VF_vertexs[2].Pos, XMVector3Transform(XMLoadFloat3(&XMFLOAT3(-xf, -yf, zf)), wvp.World));
	XMStoreFloat3(&VF_vertexs[3].Pos, XMVector3Transform(XMLoadFloat3(&XMFLOAT3(xf, -yf, zf)), wvp.World));
	//near TL TR BL BR
	XMStoreFloat3(&VF_vertexs[4].Pos, XMVector3Transform(XMLoadFloat3(&XMFLOAT3(-xn, yn, zn)), wvp.World));
	XMStoreFloat3(&VF_vertexs[5].Pos, XMVector3Transform(XMLoadFloat3(&XMFLOAT3(xn, yn, zn)), wvp.World));
	XMStoreFloat3(&VF_vertexs[6].Pos, XMVector3Transform(XMLoadFloat3(&XMFLOAT3(-xn, -yn, zn)), wvp.World));
	XMStoreFloat3(&VF_vertexs[7].Pos, XMVector3Transform(XMLoadFloat3(&XMFLOAT3(xn, -yn, zn)), wvp.World));

	////far TL TR BL BR
	//VF_vertexs[0].Pos=XMFLOAT3(-xf,  yf, zf);
	//VF_vertexs[1].Pos=XMFLOAT3( xf,  yf, zf);
	//VF_vertexs[2].Pos=XMFLOAT3(-xf, -yf, zf);
	//VF_vertexs[3].Pos=XMFLOAT3( xf, -yf, zf);
	////near TL TR BL BR													   
	//VF_vertexs[4].Pos=XMFLOAT3(-xn,  yn, zn);
	//VF_vertexs[5].Pos=XMFLOAT3( xn,  yn, zn);
	//VF_vertexs[6].Pos=XMFLOAT3(-xn, -yn, zn);
	//VF_vertexs[7].Pos=XMFLOAT3( xn, -yn, zn);
	for (size_t i = 0; i < 8; i++)
		VF_vertexs[i].Color = XMFLOAT4(0.85f, 0.0f, 0.45f, 1.0f);

#pragma region Draw Frustrum
	DR.add_line(VF_vertexs[0], VF_vertexs[1]);
	DR.add_line(VF_vertexs[2], VF_vertexs[3]);
	DR.add_line(VF_vertexs[0], VF_vertexs[2]);
	DR.add_line(VF_vertexs[1], VF_vertexs[3]);

	DR.add_line(VF_vertexs[4], VF_vertexs[5]);
	DR.add_line(VF_vertexs[6], VF_vertexs[7]);
	DR.add_line(VF_vertexs[4], VF_vertexs[6]);
	DR.add_line(VF_vertexs[5], VF_vertexs[7]);

	DR.add_line(VF_vertexs[0], VF_vertexs[4]);
	DR.add_line(VF_vertexs[1], VF_vertexs[5]);
	DR.add_line(VF_vertexs[2], VF_vertexs[6]);
	DR.add_line(VF_vertexs[3], VF_vertexs[7]);

	/*DR.add_line(VF_vertexs[0], VF_vertexs[2]);
	DR.add_line(VF_vertexs[4], VF_vertexs[6]);
	DR.add_line(VF_vertexs[0], VF_vertexs[4]);
	DR.add_line(VF_vertexs[2], VF_vertexs[6]);*/

#pragma endregion

#pragma region Cal Normals
	//Left
	VF_N_L = XMVector3Cross(
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[2].Pos), XMLoadFloat3(&VF_vertexs[6].Pos)),
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[6].Pos), XMLoadFloat3(&VF_vertexs[4].Pos))
	);
	VF_N_L = XMVector3Normalize(VF_N_L);

	//Right
	VF_N_R = XMVector3Cross(
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[7].Pos), XMLoadFloat3(&VF_vertexs[5].Pos)),
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[3].Pos), XMLoadFloat3(&VF_vertexs[7].Pos))
	);
	VF_N_R = XMVector3Normalize(VF_N_R);

	//Top
	VF_N_T = XMVector3Cross(
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[5].Pos), XMLoadFloat3(&VF_vertexs[4].Pos)),
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[1].Pos), XMLoadFloat3(&VF_vertexs[5].Pos))
	);
	VF_N_T = XMVector3Normalize(VF_N_T);

	//Bottom
	VF_N_Bt = XMVector3Cross(
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[2].Pos), XMLoadFloat3(&VF_vertexs[6].Pos)),
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[3].Pos), XMLoadFloat3(&VF_vertexs[2].Pos))
	);
	VF_N_Bt = XMVector3Normalize(VF_N_Bt);

	//Front
	VF_N_F = XMVector3Cross(
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[7].Pos), XMLoadFloat3(&VF_vertexs[5].Pos)),
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[6].Pos), XMLoadFloat3(&VF_vertexs[7].Pos))
	);
	VF_N_F = XMVector3Normalize(VF_N_F);

	//Back
	VF_N_Bk = XMVector3Cross(
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[3].Pos), XMLoadFloat3(&VF_vertexs[2].Pos)),
		XMVectorSubtract(XMLoadFloat3(&VF_vertexs[1].Pos), XMLoadFloat3(&VF_vertexs[3].Pos))
	);
	VF_N_Bk = XMVector3Normalize(VF_N_Bk);
#pragma endregion

#pragma region Normal debug
	//Init
	XMFLOAT3 temp, temp2;
	XMFLOAT4 Color = { 0.0f,0.5f,1.0f,1.0f };
	XMFLOAT4 Color2 = { 1.0f,0.5f,0.0f,1.0f };

	//Front
	temp = PlaneMidPoint(VF_vertexs[0].Pos, VF_vertexs[1].Pos, VF_vertexs[2].Pos, VF_vertexs[3].Pos);
	XMStoreFloat3(&temp2, XMVectorAdd(XMLoadFloat3(&temp), VF_N_F));
	DR.add_line(Vertex{ temp , Color }, Vertex{ temp2 , Color2 });

	//Back
	temp = PlaneMidPoint(VF_vertexs[4].Pos, VF_vertexs[5].Pos, VF_vertexs[6].Pos, VF_vertexs[7].Pos);
	XMStoreFloat3(&temp2, XMVectorAdd(XMLoadFloat3(&temp), VF_N_Bk));
	DR.add_line(Vertex{ temp , Color }, Vertex{ temp2 , Color2 });

	//Left
	temp = PlaneMidPoint(VF_vertexs[0].Pos, VF_vertexs[4].Pos, VF_vertexs[2].Pos, VF_vertexs[6].Pos);
	XMStoreFloat3(&temp2, XMVectorAdd(XMLoadFloat3(&temp), VF_N_L));
	DR.add_line(Vertex{ temp , Color }, Vertex{ temp2 , Color2 });

	//Right
	temp = PlaneMidPoint(VF_vertexs[5].Pos, VF_vertexs[1].Pos, VF_vertexs[7].Pos, VF_vertexs[3].Pos);
	XMStoreFloat3(&temp2, XMVectorAdd(XMLoadFloat3(&temp), VF_N_R));
	DR.add_line(Vertex{ temp , Color }, Vertex{ temp2 , Color2 });

	//Top
	temp = PlaneMidPoint(VF_vertexs[0].Pos, VF_vertexs[1].Pos, VF_vertexs[4].Pos, VF_vertexs[5].Pos);
	XMStoreFloat3(&temp2, XMVectorAdd(XMLoadFloat3(&temp), VF_N_T));
	DR.add_line(Vertex{ temp , Color }, Vertex{ temp2 , Color2 });

	//Bot
	temp = PlaneMidPoint(VF_vertexs[6].Pos, VF_vertexs[7].Pos, VF_vertexs[2].Pos, VF_vertexs[3].Pos);
	XMStoreFloat3(&temp2, XMVectorAdd(XMLoadFloat3(&temp), VF_N_Bt));
	DR.add_line(Vertex{ temp , Color }, Vertex{ temp2 , Color2 });
#pragma endregion

	XMFLOAT3 t = PlaneMidPoint(VF_vertexs[0].Pos, VF_vertexs[2].Pos, VF_vertexs[4].Pos, VF_vertexs[6].Pos);
	XMVECTOR test = VF_N_L;
	XMVECTOR offset0 = XMVector3Dot(test, XMLoadFloat3(&VF_vertexs[0].Pos));
	XMVECTOR offset1 = XMVector3Dot(test, XMLoadFloat3(&VF_vertexs[1].Pos));
	XMVECTOR offset2 = XMVector3Dot(test, XMLoadFloat3(&VF_vertexs[2].Pos));
	XMVECTOR offset3 = XMVector3Dot(test, XMLoadFloat3(&VF_vertexs[3].Pos));
	XMVECTOR offset4 = XMVector3Dot(test, XMLoadFloat3(&VF_vertexs[4].Pos));
	XMVECTOR offset5 = XMVector3Dot(test, XMLoadFloat3(&VF_vertexs[5].Pos));
	XMVECTOR offset6 = XMVector3Dot(test, XMLoadFloat3(&VF_vertexs[6].Pos));
	XMVECTOR offset7 = XMVector3Dot(test, XMLoadFloat3(&VF_vertexs[7].Pos));
	XMVECTOR offset8 = XMVector3Dot(test, XMLoadFloat3(&t));


	//DR.add_line(Vertex{ XMFLOAT3(0,0,0),XMFLOAT4(1.0f,0.0f,1.0f,1.0f) }, VF_vertexs[0]);
	//DR.add_line(Vertex{ XMFLOAT3(0,0,0),XMFLOAT4(1.0f,0.0f,1.0f,1.0f) }, Vertex{ t,XMFLOAT4(1.0f,0.0f,1.0f,1.0f) });
}

void GameEng::RunAnimation(Anim_Clip * _Clip)
{
	timercount += time.Delta()*Anim_Speed;
	float ratio;
	//increment frame if needed
	if (_Clip->frame_index < _Clip->frames.size() - 1 && timercount < _Clip->duration)
	{
		if (timercount > _Clip->frames[_Clip->frame_index + 1].time)
			_Clip->frame_index++;
	}
	else //last frame
	{
		if (timercount > _Clip->duration)
		{
			_Clip->frame_index = 1;
			timercount -= _Clip->duration;
		}	
	}

	//calculating ratio
	if(_Clip->frame_index< _Clip->frames.size()-1)
		ratio = (timercount - _Clip->frames[_Clip->frame_index].time)
		/ (_Clip->frames[_Clip->frame_index + 1].time - _Clip->frames[_Clip->frame_index].time);
	else
		ratio = (timercount - _Clip->frames[_Clip->frame_index].time)
		/ (_Clip->duration - _Clip->frames[_Clip->frame_index].time);
	if (ratio < 0) ratio = 0;
	if (ratio > 1) ratio = 1;

	_Clip->CurrJoints.resize(_Clip->parentlist.size());
	for (size_t i = 0; i < _Clip->parentlist.size(); i++)
	{
		_Clip->CurrJoints[i] = _Clip->frames[_Clip->frame_index].Joints[i];
		XMMATRIX currF, nextF;
		//get current frame pos
		currF = _Clip->frames[_Clip->frame_index].Joints[i];
		//get next frame pos
		if (_Clip->frame_index < _Clip->frames.size() - 1)
			nextF = _Clip->frames[_Clip->frame_index + 1].Joints[i];
		else
			nextF = _Clip->frames[1].Joints[i];
		//slerp it with ratio above
		XMMATRIX result = _Clip->CurrJoints[i];		 
		result.r[0] = XMQuaternionSlerp(currF.r[0], nextF.r[0], ratio);
		result.r[1] = XMQuaternionSlerp(currF.r[1], nextF.r[1], ratio);
		result.r[2] = XMQuaternionSlerp(currF.r[2], nextF.r[2], ratio);
		result.r[3] = XMVectorLerp(currF.r[3], nextF.r[3], ratio);
		_Clip->CurrJoints[i] = result;
	}
	VertexWVP tempWVP;
	tempWVP.World = Bear_Pos;
	tempWVP.View = mView;
	tempWVP.Proj = mProjection;
	DR.add_3axis(tempWVP);
	for (size_t L = 1; L < _Clip->parentlist.size(); L++)
	{
		VertexWVP tempWVP;
		tempWVP.World = _Clip->CurrJoints[L];
		DR.add_3axis(tempWVP);
		Vertex A, B;
		A.Pos.x = _Clip->CurrJoints[L].r[3].m128_f32[0];
		A.Pos.y = _Clip->CurrJoints[L].r[3].m128_f32[1];
		A.Pos.z = _Clip->CurrJoints[L].r[3].m128_f32[2];

		B.Pos.x = _Clip->CurrJoints[_Clip->parentlist[L]].r[3].m128_f32[0];
		B.Pos.y = _Clip->CurrJoints[_Clip->parentlist[L]].r[3].m128_f32[1];
		B.Pos.z = _Clip->CurrJoints[_Clip->parentlist[L]].r[3].m128_f32[2];

		A.Color = white;
		B.Color = white;
		DR.add_line(A, B);
	}
}

void GameEng::RunAnimationReverse(Anim_Clip * _Clip)
{
	timercount -= time.Delta();
	float ratio;
	if (_Clip->frame_index > 0)
	{
		ratio = (timercount - _Clip->frames[_Clip->frame_index - 1].time)
			/ (_Clip->frames[_Clip->frame_index + 1].time - _Clip->frames[_Clip->frame_index].time);
		if (timercount > _Clip->frames[_Clip->frame_index + 1].time)
			_Clip->frame_index++;
	}
	else
	{
		ratio = (timercount - _Clip->frames[_Clip->frame_index].time)
			/ (_Clip->duration - _Clip->frames[_Clip->frame_index].time);
		if (timercount < 0)
		{
			_Clip->frame_index = _Clip->frames.size() - 1;
			timercount = _Clip->duration;
		}
	}
	if (ratio < 0) ratio = 0;
	if (ratio > 1) ratio = 1;
	_Clip->CurrJoints.resize(_Clip->parentlist.size());
	for (size_t i = 0; i < _Clip->parentlist.size(); i++)
	{
		_Clip->CurrJoints[i] = _Clip->frames[_Clip->frame_index].Joints[i];
		XMMATRIX currF, nextF;
		//get current frame pos
		currF = _Clip->frames[_Clip->frame_index].Joints[i];
		currF = XMMatrixMultiply(currF, Bear_Pos);
		//get next frame pos
		if (_Clip->frame_index > 0)
			nextF = _Clip->frames[_Clip->frame_index - 1].Joints[i];
		else
			nextF = _Clip->frames[_Clip->frames.size() - 1].Joints[i];
		nextF = XMMatrixMultiply(nextF, Bear_Pos);
		//slerp it with ratio above
		XMMATRIX result;
		result.r[0] = XMQuaternionSlerp(currF.r[0], nextF.r[0], ratio);
		result.r[1] = XMQuaternionSlerp(currF.r[1], nextF.r[1], ratio);
		result.r[2] = XMQuaternionSlerp(currF.r[2], nextF.r[2], ratio);
		result.r[3] = XMQuaternionSlerp(currF.r[3], nextF.r[3], ratio);
		_Clip->CurrJoints[i] = result;
	}
	VertexWVP tempWVP;
	tempWVP.World = Bear_Pos;
	tempWVP.View = mView;
	tempWVP.Proj = mProjection;
	DR.add_3axis(tempWVP);
	for (size_t L = 1; L < _Clip->parentlist.size(); L++)
	{
		VertexWVP tempWVP;
		tempWVP.World = _Clip->CurrJoints[L];
		DR.add_3axis(tempWVP);
		Vertex A, B;
		A.Pos.x = _Clip->CurrJoints[L].r[3].m128_f32[0];
		A.Pos.y = _Clip->CurrJoints[L].r[3].m128_f32[1];
		A.Pos.z = _Clip->CurrJoints[L].r[3].m128_f32[2];

		B.Pos.x = _Clip->CurrJoints[_Clip->parentlist[L]].r[3].m128_f32[0];
		B.Pos.y = _Clip->CurrJoints[_Clip->parentlist[L]].r[3].m128_f32[1];
		B.Pos.z = _Clip->CurrJoints[_Clip->parentlist[L]].r[3].m128_f32[2];

		A.Color = white;
		B.Color = white;
		DR.add_line(A, B);
	}
}

void GameEng::AnimationTransition(Anim_Clip * _from, Anim_Clip * _to, double transitiontime)
{
	_to->frame_index = 1;
	timercount = 0;
	CurrentAnimation = _to;
	RunAnimation(CurrentAnimation);
}

void GameEng::RunAnimationTransition(Anim_Clip* _to)
{
	if (timercount < Anim_Transition.duration)
	{
		timercount += time.Delta();
		float ratio;

		ratio = (timercount - Anim_Transition.frames[Anim_Transition.frame_index].time)
			/ (Anim_Transition.duration - Anim_Transition.frames[Anim_Transition.frame_index].time);
		if (timercount > Anim_Transition.duration)
		{
			Anim_Transition.frame_index = 0;
		}
		if (ratio < 0) ratio = 0;
		if (ratio > 1) ratio = 1;
		Anim_Transition.CurrJoints.resize(Anim_Transition.parentlist.size());
		for (size_t i = 0; i < Anim_Transition.parentlist.size(); i++)
		{
			Anim_Transition.CurrJoints[i] = Anim_Transition.frames[Anim_Transition.frame_index].Joints[i];
			XMMATRIX currF, nextF;
			//get current frame pos
			currF = Anim_Transition.frames[Anim_Transition.frame_index].Joints[i];
			currF = XMMatrixMultiply(currF, Bear_Pos);
			//get next frame pos
			if (Anim_Transition.frame_index < Anim_Transition.frames.size() - 1)
				nextF = Anim_Transition.frames[Anim_Transition.frame_index + 1].Joints[i];
			else
				nextF = Anim_Transition.frames[0].Joints[i];
			nextF = XMMatrixMultiply(nextF, Bear_Pos);
			//slerp it with ratio above
			XMMATRIX result;
			result.r[0] = XMQuaternionSlerp(currF.r[0], nextF.r[0], ratio);
			result.r[1] = XMQuaternionSlerp(currF.r[1], nextF.r[1], ratio);
			result.r[2] = XMQuaternionSlerp(currF.r[2], nextF.r[2], ratio);
			result.r[3] = XMQuaternionSlerp(currF.r[3], nextF.r[3], ratio);
			Anim_Transition.CurrJoints[i] = result;
		}
		VertexWVP tempWVP;
		tempWVP.World = Bear_Pos;
		tempWVP.View = mView;
		tempWVP.Proj = mProjection;
		DR.add_3axis(tempWVP);
		for (size_t L = 1; L < Anim_Transition.parentlist.size(); L++)
		{
			VertexWVP tempWVP;
			tempWVP.World = Anim_Transition.CurrJoints[L];
			DR.add_3axis(tempWVP);
			Vertex A, B;
			A.Pos.x = Anim_Transition.CurrJoints[L].r[3].m128_f32[0];
			A.Pos.y = Anim_Transition.CurrJoints[L].r[3].m128_f32[1];
			A.Pos.z = Anim_Transition.CurrJoints[L].r[3].m128_f32[2];

			B.Pos.x = Anim_Transition.CurrJoints[Anim_Transition.parentlist[L]].r[3].m128_f32[0];
			B.Pos.y = Anim_Transition.CurrJoints[Anim_Transition.parentlist[L]].r[3].m128_f32[1];
			B.Pos.z = Anim_Transition.CurrJoints[Anim_Transition.parentlist[L]].r[3].m128_f32[2];

			A.Color = white;
			B.Color = white;
			DR.add_line(A, B);
		}
	}
	else
	{
		timercount = 0;
		Transiting = false;
		CurrentAnimation = _to;
	}
}

#pragma endregion

#pragma region MathFunctions

bool GameEng::isInVF(int V_buffer_index, int V_buffer_size)
{
	for (size_t i = 0; i < V_buffer_size; i++)
	{

	}
	return false;
}

bool GameEng::isInVF(VertexWVP obj_wvp)
{
	XMVECTOR Center = obj_wvp.World.r[3];
	XMVECTOR Extents = XMVectorSet(0.5f, 0.5f, 0.5f, 1.0f);
	XMVECTOR offsetE, offsetC;

	//Left
	//Sphere width
	offsetE = XMVector3Dot(XMVectorSet(abs(VF_N_L.m128_f32[0]), abs(VF_N_L.m128_f32[1]), abs(VF_N_L.m128_f32[2]), 1.0f), Extents);
	//center to origin
	offsetC = XMVectorSubtract(XMVector3Dot(VF_N_L, Center), XMVector3Dot(VF_N_L, XMLoadFloat3(&VF_vertexs[0].Pos)));
	if (offsetC.m128_f32[0] + offsetE.m128_f32[0] < 0)
		return false;
	//Right
	offsetE = XMVector3Dot(XMVectorSet(abs(VF_N_R.m128_f32[0]), abs(VF_N_R.m128_f32[1]), abs(VF_N_R.m128_f32[2]), 1.0f), Extents);
	offsetC = XMVectorSubtract(XMVector3Dot(VF_N_R, Center), XMVector3Dot(VF_N_R, XMLoadFloat3(&VF_vertexs[1].Pos)));
	if (offsetC.m128_f32[0] + offsetE.m128_f32[0] < 0)
		return false;
	//Top
	offsetE = XMVector3Dot(XMVectorSet(abs(VF_N_T.m128_f32[0]), abs(VF_N_T.m128_f32[1]), abs(VF_N_T.m128_f32[2]), 1.0f), Extents);
	offsetC = XMVectorSubtract(XMVector3Dot(VF_N_T, Center), XMVector3Dot(VF_N_T, XMLoadFloat3(&VF_vertexs[1].Pos)));
	if (offsetC.m128_f32[0] + offsetE.m128_f32[0] < 0)
		return false;
	//Bot
	offsetE = XMVector3Dot(XMVectorSet(abs(VF_N_Bt.m128_f32[0]), abs(VF_N_Bt.m128_f32[1]), abs(VF_N_Bt.m128_f32[2]), 1.0f), Extents);
	offsetC = XMVectorSubtract(XMVector3Dot(VF_N_Bt, Center), XMVector3Dot(VF_N_Bt, XMLoadFloat3(&VF_vertexs[2].Pos)));
	if (offsetC.m128_f32[0] + offsetE.m128_f32[0] < 0)
		return false;
	//Front
	offsetE = XMVector3Dot(XMVectorSet(abs(VF_N_F.m128_f32[0]), abs(VF_N_F.m128_f32[1]), abs(VF_N_F.m128_f32[2]), 1.0f), Extents);
	offsetC = XMVectorSubtract(XMVector3Dot(VF_N_F, Center), XMVector3Dot(VF_N_F, XMLoadFloat3(&VF_vertexs[0].Pos)));
	if (offsetC.m128_f32[0] + offsetE.m128_f32[0] < 0)
		return false;
	//Back
	offsetE = XMVector3Dot(XMVectorSet(abs(VF_N_Bk.m128_f32[0]), abs(VF_N_Bk.m128_f32[1]), abs(VF_N_Bk.m128_f32[2]), 1.0f), Extents);
	offsetC = XMVectorSubtract(XMVector3Dot(VF_N_Bk, Center), XMVector3Dot(VF_N_Bk, XMLoadFloat3(&VF_vertexs[4].Pos)));
	if (offsetC.m128_f32[0] + offsetE.m128_f32[0] < 0)
		return false;

	return true;
}

void GameEng::Matrix()
{
	XMVECTOR pos = XMVectorSet(Cam_Pos[0], Cam_Pos[1], Cam_Pos[2], Cam_Pos[3]);
	XMVECTOR at = XMVectorSet(Cam_Look[0], Cam_Look[1], Cam_Look[2], Cam_Look[3]);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	World = XMMatrixIdentity();
	World = XMMatrixRotationY(CubeWorld.Rotate[1]);
	World = XMMatrixMultiply(World, XMMatrixTranslation(CubeWorld.World[0], CubeWorld.World[1], CubeWorld.World[2]));
	//View = XMMatrixLookAtLH(pos, at, up);
	mView = Look_AT(pos, at, up);
	if (lookat == false)
		mView = Turn_TO(mView, at, 1.0f);
	mView = Mouse_Move(mView, Con.getMouseX(), Con.getMouseY());
	mProjection = XMMatrixPerspectiveFovLH(0.61f, Window_Width / Window_Height, 0.1f, 1000.0f);
}

XMMATRIX GameEng::Look_AT(XMVECTOR Pos, XMVECTOR At, XMVECTOR Up)
{
	XMVECTOR z = XMVector4Normalize(XMVectorSubtract(At, Pos));
	XMVECTOR x = XMVector4Normalize(XMVector3Cross(Up, z));
	XMVECTOR y = XMVector4Normalize(XMVector3Cross(z, x));
	XMVECTOR ori = XMVectorSet(XMVectorGetX(XMVector3Dot(x, Pos)), XMVectorGetX(XMVector3Dot(y, Pos)), XMVectorGetX(XMVector3Dot(z, Pos)), 1.0f);
	ori = XMVectorSet(-1.0f * XMVectorGetX(ori), -1.0f * XMVectorGetY(ori), -1.0f * XMVectorGetZ(ori), 1.0f);
	XMVECTOR xr = XMVectorSet(XMVectorGetX(x), XMVectorGetX(y), XMVectorGetX(z), 0.0f);
	XMVECTOR yr = XMVectorSet(XMVectorGetY(x), XMVectorGetY(y), XMVectorGetY(z), 0.0f);
	XMVECTOR zr = XMVectorSet(XMVectorGetZ(x), XMVectorGetZ(y), XMVectorGetZ(z), 0.0f);
	return XMMATRIX(xr, yr, zr, ori);
}

XMMATRIX GameEng::Turn_TO(XMMATRIX _View, XMVECTOR Target, float speed)
{
	XMVECTOR Cam_pos = _View.r[3];
	XMVECTOR mVector = Target - Cam_pos;
	mVector = XMVector3Normalize(mVector);
	XMVECTOR resulty = XMVector3Dot(mVector, _View.r[1]);
	float vdoty = XMVectorGetX(resulty);
	_View = XMMatrixMultiply(XMMatrixRotationX(-vdoty * 1.0f), _View);

	XMVECTOR resultx = XMVector3Dot(mVector, _View.r[0]);
	float vdotx = XMVectorGetX(resultx);
	_View = XMMatrixMultiply(XMMatrixRotationY(vdotx*1.0f), _View);

	//XMVECTOR z = XMVector4Normalize(_View.r[2]);
	//XMVECTOR x = XMVector4Normalize(XMVector3Cross(XMVectorSet(0.0f,1.0f,0.0f,1.0f), z));
	//XMVECTOR y = XMVector4Normalize(XMVector3Cross(z, x));
	//XMVECTOR ori = XMVectorSet(XMVectorGetX(XMVector3Dot(x, -View.r[3])), XMVectorGetX(XMVector3Dot(y, -View.r[3])), XMVectorGetX(XMVector3Dot(z, -View.r[3])), 1.0f);
	//ori = XMVectorSet(-1.0f * XMVectorGetX(ori), -1.0f * XMVectorGetY(ori), -1.0f * XMVectorGetZ(ori), 1.0f);
	//XMVECTOR xr = XMVectorSet(XMVectorGetX(x), XMVectorGetX(y), XMVectorGetX(z), 0.0f);
	//XMVECTOR yr = XMVectorSet(XMVectorGetY(x), XMVectorGetY(y), XMVectorGetY(z), 0.0f);
	//XMVECTOR zr = XMVectorSet(XMVectorGetZ(x), XMVectorGetZ(y), XMVectorGetZ(z), 0.0f);
	//return XMMATRIX(xr, yr, zr, ori);

	return _View;
}

XMMATRIX GameEng::Mouse_Move(XMMATRIX _View, int dX, int dY)
{
	_View = XMMatrixMultiply(_View, XMMatrixRotationX(-(float)dY / Window_Height * MouseSensitive));
	_View = XMMatrixMultiply(_View, XMMatrixRotationY(-(float)dX / Window_Width * MouseSensitive));
	return _View;
}

XMFLOAT3 GameEng::PosMulWorld(XMFLOAT3 pos, XMMATRIX world)
{
	return XMFLOAT3();
}

XMFLOAT3 GameEng::PlaneMidPoint(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c, XMFLOAT3 d)
{
	return XMFLOAT3(
		a.x *0.25f + b.x *0.25f + c.x *0.25f + d.x *0.25f,
		a.y *0.25f + b.y *0.25f + c.y *0.25f + d.y *0.25f,
		a.z *0.25f + b.z *0.25f + c.z *0.25f + d.z *0.25f
	);
}

#pragma endregion