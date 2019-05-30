#include "stdafx.h"
#include "BVH.h"
BVH::BVH()
{
}


BVH::~BVH()
{
}

float BVH::manhat(Node A, Node B)
{
	return abs(A.aabb.Center.x -B.aabb.Center.x) + abs(A.aabb.Center.y -B.aabb.Center.y) + abs(A.aabb.Center.z -B.aabb.Center.z);
}

AABB BVH::ExpandAABBBound(AABB Host, AABB guest)
{
	if (Host.maxX < guest.maxX)			Host.maxX = guest.maxX;
	if (Host.maxY < guest.maxY)			Host.maxY = guest.maxY;
	if (Host.maxZ < guest.maxZ)			Host.maxZ = guest.maxZ;

	if (Host.minX > guest.minX)			Host.minX = guest.minX;
	if (Host.minY > guest.minY)			Host.minY = guest.minY;
	if (Host.minZ > guest.minZ)			Host.minZ = guest.minZ;

	Host.Center.x = 0.5f*(Host.maxX + Host.minX);
	Host.Center.y = 0.5f*(Host.maxY + Host.minY);
	Host.Center.z = 0.5f*(Host.maxZ + Host.minZ);
	return Host;
}

void BVH::BuildTree()
{
	while (true)
	{
		if (TerrainAABB.size() == 0)
			break;
		int index = rand()%TerrainAABB.size();

		Node* temp = new Node();
		temp->aabb = TerrainAABB[index];
		if (Root == nullptr)
		{
			Root = temp;
			continue;
		}
		bool ReachEnd = false;
		Node* Curr = Root;
		while (!ReachEnd)
		{
			//If leaf node
			if (Curr->Left == nullptr && Curr->Right == nullptr)
			{
				ReachEnd = true;
				Count++;

				Node* tempcurr = new Node();
				tempcurr->aabb = Curr->aabb;
				Curr->Right = tempcurr;

				Curr->aabb = ExpandAABBBound(Curr->aabb, temp->aabb);
				Curr->Left = temp;
		}
			else
			{
				Curr->aabb = ExpandAABBBound(Curr->aabb, temp->aabb);
				if (manhat(*temp, *Curr->Left) < manhat(*temp, *Curr->Right))
					Curr = Curr->Left;
				else
					Curr = Curr->Right;
			}
		}
		TerrainAABB.erase(TerrainAABB.begin()+index);
	}
}

void BVH::Recursive(AABB x,Node* y, graphics_system::DebugRender * Dr)
{
	if (IsAABBsCollide(x, y->aabb))
	{
		Dr->DrawAABB(y->aabb);
		if (y->Left != nullptr)
		{
			Recursive(x, y->Left, Dr);
			Recursive(x, y->Right, Dr);
		}
	}
}

bool BVH::IsAABBsCollide(AABB A, AABB B)
{
	if (A.maxX < B.minX || A.minX > B.maxX) return false;
	if (A.maxY < B.minY || A.minY > B.maxY) return false;
	if (A.maxZ < B.minZ || A.minZ > B.maxZ) return false;
	return true;
}
#if 0
void BVH::AABBImport(Mesh* mesh)
{
	int totalTri = mesh->pos.size() / 3;
	graphics_system::DebugRender Dr;
	for (size_t i = 0; i < totalTri; i++)
	{
		XMFLOAT3 p1 = mesh->pos[i * 3], p2 = mesh->pos[i * 3 + 1], p3 = mesh->pos[i * 3 + 2];
		XMVECTOR n1 = XMLoadFloat3(&mesh->norms[i * 3]), n2 = XMLoadFloat3(&mesh->norms[i * 3 + 1]), n3 = XMLoadFloat3(&mesh->norms[i * 3 + 2]);
		XMVECTOR temp = XMVector4Transform(XMVectorSet(p1.x, p1.y, p1.z, 1.0f), mesh->WVP.World);
		XMStoreFloat3(&p1, temp);
		temp = XMVector4Transform(XMVectorSet(p2.x, p2.y, p2.z, 1.0f), mesh->WVP.World);
		XMStoreFloat3(&p2, temp);
		temp = XMVector4Transform(XMVectorSet(p3.x, p3.y, p3.z, 1.0f), mesh->WVP.World);
		XMStoreFloat3(&p3, temp);
		XMFLOAT3 temppos;
		temppos.x = (p1.x + p2.x + p3.x) / 3.0f;
		temppos.y = (p1.y + p2.y + p3.y) / 3.0f;
		temppos.z = (p1.z + p2.z + p3.z) / 3.0f;
		TerrainCentroid.push_back(temppos);

		XMVECTOR tempnorm = XMVector3Normalize(XMVector3Cross(XMVectorSubtract(n2, n1), XMVectorSubtract(n3, n2)));
		TerrainNorm.push_back(tempnorm);

		TerrainAABB.push_back(Dr.createAABB(p1, p2, p3));
	}

	BuildTree();
}
#endif
void BVH::PushTerrainNorm(XMVECTOR x)
{
	TerrainNorm.push_back(x);
}

void BVH::PushTerrainCent(XMFLOAT3 X)
{
	TerrainCentroid.push_back(X);
}

void BVH::PushAABB(AABB x)
{
	TerrainAABB.push_back(x);
}
