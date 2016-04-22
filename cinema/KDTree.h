#pragma once
#include <vector>
class BBox;
class Geometry;
struct KDTreeNode;
class Ray;
class KDTree
{
public:
	KDTree(KDTreeNode * root);
	~KDTree();
	std::vector<Geometry*>* Intersect(const Ray & ray);
	static KDTree * Build(std::vector<Geometry*> &geometries);
private:
	KDTreeNode * m_root;
	static KDTreeNode * BuildTree(std::vector<Geometry*> &geometries, int depth);
};

struct KDTreeNode
{
	KDTreeNode() {}
	~KDTreeNode() {}
	std::vector<KDTreeNode*> * children;
	BBox *bbox;
	std::vector<Geometry*> * geometries;
	std::vector<Geometry*> * Intersect(const Ray & ray);
	bool IntersectAABB(const Ray & ray);
};