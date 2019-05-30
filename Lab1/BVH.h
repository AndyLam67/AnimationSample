#pragma once
#include "Define.h"
#include "DebugRender.h"
struct Node
{
	AABB aabb;
	Node* Left = nullptr;
	Node* Right = nullptr;
};

class BVH
{
	vector<XMVECTOR>				TerrainNorm;
	vector<XMFLOAT3>				TerrainCentroid;
	vector<AABB>					TerrainAABB;
	vector<Node>					NodeTree;
	unsigned int					Count=0;

	float manhat(Node A, Node B);
	AABB ExpandAABBBound(AABB Host, AABB guest);
	graphics_system::DebugRender dr;
public:
	Node* Root=nullptr;
	BVH();
	~BVH();
	void AABBImport(Mesh* mesh);
	void PushTerrainNorm(XMVECTOR x);
	void PushTerrainCent(XMFLOAT3 X);
	void PushAABB(AABB x);
	void BuildTree();
	void Recursive(AABB x,Node* y,graphics_system::DebugRender *Dr);
	//True means Collide, False means not//
	bool IsAABBsCollide(AABB A, AABB B);
	
};

