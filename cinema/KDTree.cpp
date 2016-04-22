#include "KDTree.h"
#include "BBox.h"
#include "Geometry.h"
#include "Ray.h"

KDTree::KDTree(KDTreeNode * root) :m_root(root)
{
}


KDTree::~KDTree()
{
}

std::vector<Geometry*>* KDTree::Intersect(const Ray & ray)
{
	if (!m_root->bbox->Intersect(ray))
	{
		return nullptr;
	}
	return m_root->Intersect(ray);
}

std::vector<Geometry*>* KDTreeNode::Intersect(const Ray & ray)
{
	if (geometries == nullptr)
	{
		return nullptr;
	}
	if (children == nullptr)
	{
		return geometries;
	}
	bool leftHit = (*children)[0]->IntersectAABB(ray);
	bool rightHit = (*children)[1]->IntersectAABB(ray);
	if (leftHit && rightHit)
	{
		return geometries;
	}
	else if (leftHit)
	{
		return (*children)[0]->Intersect(ray);
	}
	else if (rightHit)
	{
		return (*children)[1]->Intersect(ray);
	}
	return nullptr;
}

bool KDTreeNode::IntersectAABB(const Ray & ray)
{
	if (bbox == nullptr)
	{
		return false;
	}
	return bbox->Intersect(ray);
}

KDTree * KDTree::Build(std::vector<Geometry*> &geometries)
{
	int maxDepth = 8.0 + 1.3*std::log2(geometries.size());
	return new KDTree(BuildTree(geometries, maxDepth));
}


KDTreeNode * KDTree::BuildTree(std::vector<Geometry*>& geometries, int depth)
{
	KDTreeNode * root(new KDTreeNode);
	if (!geometries.empty())
	{
		root->geometries = new std::vector<Geometry*>;
		root->geometries->insert(root->geometries->end(), geometries.begin(), geometries.end());
		BBox * box(new BBox);
		root->bbox = box;
		for (auto geometry : geometries)
		{
			box->Union(geometry->bbox);
		}
	}
	else
	{
		root->geometries = nullptr;
		root->bbox = nullptr;
	}

	if (depth <= 0 || geometries.size() <= 2)
	{	
		root->children = nullptr;
		return root;
	}
	
	int axis = root->bbox->MaxExtension();
	Point center = root->bbox->GetCenter();

	auto *leftGeometries(new std::vector<Geometry*>);
	auto *rightGeometries(new std::vector<Geometry*>);

	for (auto geometry : geometries)
	{
		if (geometry->bbox.GetCenter()[axis] <= center[axis])
		{
			leftGeometries->push_back(geometry);
		}
		else
		{
			rightGeometries->push_back(geometry);
		}
	}
	root->children = new std::vector<KDTreeNode*>;
	root->children->resize(2);
	int nextDepth = depth - 1;
	(*(root->children))[0] = BuildTree(*leftGeometries, nextDepth);
	delete leftGeometries;
	(*(root->children))[1] = BuildTree(*rightGeometries, nextDepth);
	delete rightGeometries;
	return root;
}

