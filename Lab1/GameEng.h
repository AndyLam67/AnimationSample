#pragma once
#include "InputControl.h"
//#include "DebugRender.h"
#include "BVH.h"

class GameEng
{
public:
	struct pipeline_state_t
	{
		uint8_t input_layout_index			=0;
		uint8_t vertex_shader_index			=0;
		uint8_t pixel_shader_index			=0;
		uint8_t render_target_index			=0;
		uint8_t depthStencilState_index		=0;
		uint8_t depthStencilView_index		=0;
		uint8_t rasterState_index			=0;
		uint8_t vertex_buffer_index			=0;
		uint8_t index_buffer_index			=0;
	}PIP_index;

	GameEng();
	~GameEng();

	void GameInit(HWND hwnd);
	void GameRender();
	void GameUpdate();
	void GameShutdown();

	InputControl					Con;


private:
	graphics_system::DebugRender	DR;
	BVH								_BVH;
	HWND							hwnd;
	float							Window_Width;
	float							Window_Height;
	ID3D11InputLayout*				Input_Layout[256]{};
	ID3D11VertexShader*				Vertex_Shader[256]{};
	ID3D11PixelShader*				Pixel_Shader[256]{};
	ID3D11RenderTargetView*			Render_Target[256]{};
	ID3D11DepthStencilState*		Depth_Stencil_State[256]{};
	ID3D11DepthStencilView*			Depth_Stencil_View[256]{};
	ID3D11RasterizerState*			Raster_State[256]{};
	ID3D11Buffer*					Vertex_Buffer[256]{};
	ID3D11Buffer*					Index_Buffer[256]{};
	ID3D11ShaderResourceView*		ShaderResourceView[256]{};
	ID3D11Texture2D*				Texture2D[256]{};

	ID3D11Device*					Device = NULL;
	ID3D11DeviceContext*			Device_Context = NULL;
	VertexWVP						VcBuffer;
	ID3D11Buffer*					VConstBuffer;
	ID3D11SamplerState*				mSamplerState;

	ID3D11Texture2D*				DepthStencilBuffer;
	IDXGISwapChain*					SwapChain = NULL;
	D3D11_VIEWPORT					ViewPort;

	ID3D11ShaderResourceView*		testSRV;

	XTime							time;
	float							t;
	float							t2;
	float							turntoangle;
	static float					angle;
	float							Cam_Pos[4]= { 0.0f,100.0f,100.0f,0.0f };
	float							Cam_Look[4] = { 0.0f,5.0f,0.0f,0.0f };
	float							Cam_Up[4] = { 0.0f,1.0f,0.0f,0.0f };
	float							FOV = 0.61f;
	XMMATRIX						World;
	XMMATRIX						mView;
	XMMATRIX						mProjection;
	float							MouseSensitive=0.75f;
	Matrix							CubeWorld = { 0.0f,0.0f,0.0f,0.0f,0.0f,0.0f };
	Matrix							MageWorld = { 5.0f,0.0f,2.0f,0.0f,0.0f,0.0f };
	Matrix							Cube3World = { 2.0f,0.0f,5.0f,0.0f,0.0f,0.0f };
	bool							lookat = true;

	//Lighting
	Light							Lighting;
	ID3D11Buffer*					LightingCB;

	//Matrix
	VertexWVP						Cube1;
	VertexWVP						Mage;
	VertexWVP						Cube3;
	VertexWVP						Origin;
	VertexWVP						VF_WVP;
	XMMATRIX						Bear_Pos;

	//View Frustum
	Vertex							VF_vertexs[8];
	float							VF_fov = 70.0f;
	float							VF_viewRatio = 1.0f;
	float							VF_near = 0.5f;
	float							VF_far = 5.0f;
	XMVECTOR						VF_N_L;
	XMVECTOR						VF_N_R;
	XMVECTOR						VF_N_T;
	XMVECTOR						VF_N_Bt;
	XMVECTOR						VF_N_F;
	XMVECTOR						VF_N_Bk;
	//XMMATRIX						VF_Matrix;

	//Terrain
	Mesh							Terrain;
	Mesh							Bear;

	//Animation
	Anim_Clip						Anim_Walk;
	Anim_Clip						Anim_Idle;
	Anim_Clip						Anim_Transition;
	Anim_Clip*						CurrentAnimation;
	bool							IsWalking = false;
	bool							Transiting = false;
	float							Anim_Speed = 1.0f;
	static double					timercount;
	XMMATRIX						JointtoCB[60];
	ID3D11Buffer*					JointCB;


	void InitViewport();
	void SetPipelineState(pipeline_state_t* pipeline);
	void SetBufferToDefaultGraphics(ID3D11Buffer*& VertexBuffer, ID3D11Buffer*& IndexBuffer);
	void SetBufferToDefaultGraphics(UINT vindex,UINT iindex);
	void Init_Device_DeviceContext_SwapChain(HWND* hwnd);
	void InitDepthStencilState(D3D11_DEPTH_STENCIL_DESC dsdesc);
	void InitDepthStencilView(HWND hwnd, D3D11_TEXTURE2D_DESC desc);
	void InitRasterizerState(D3D11_RASTERIZER_DESC desc);
	void InitSamplerState();
	void InitShaderAndInputLayout(const BYTE *ps, UINT ps_size, const BYTE *vs, UINT vs_size, D3D11_INPUT_ELEMENT_DESC* desc, UINT arraysize);
	void dXRelease();
	void KeyPressControl(); static bool speedup;
	void Matrix();
	void DrawObject(VertexWVP WVP,int V_buffer_index,int I_buffer_index,int index_size,D3D11_PRIMITIVE_TOPOLOGY top);
	void ViewFrustum(VertexWVP wvp);
	void RunAnimation(Anim_Clip* _Clip);
	void RunAnimationReverse(Anim_Clip* _Clip);
	void AnimationTransition(Anim_Clip* _from, Anim_Clip* _to, double transitiontime=0.1);
	void RunAnimationTransition(Anim_Clip* _to);

	bool isInVF(int V_buffer_index,int V_buffer_size);
	bool isInVF(VertexWVP obj_wvp);
	XMMATRIX Look_AT(XMVECTOR Pos,XMVECTOR At,XMVECTOR Up);
	XMMATRIX Turn_TO(XMMATRIX _View, XMVECTOR Target, float speed);
	XMMATRIX Mouse_Move(XMMATRIX _View, int dX, int dY);
	XMFLOAT3 PosMulWorld(XMFLOAT3 pos, XMMATRIX world);
	XMFLOAT3 PlaneMidPoint(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c, XMFLOAT3 d);

	void Meshimport_BIN(Mesh& mesh, const char* path);
	void Meshimport_BIN2(Mesh & mesh, const char * path,float scalerX =1.0f,float scalerY=1.0f,float scalerZ=1.0f);
	void TextureLoader(ID3D11Device * mDevice, const wchar_t * path, ID3D11Texture2D* texture, ID3D11ShaderResourceView * SRV);
	void FBXLoader(const char* path, Anim_Clip* _Clip,Mesh & mesh,float scalerX,float scalerY,float scalerZ);
};

