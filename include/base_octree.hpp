#ifndef OCTREE_BASE_OCTREE_HPP_
#define OCTREE_BASE_OCTREE_HPP_

#include <fstream>

namespace eda {

namespace octree {

template <typename T, class Node>
class BaseOctree {
protected:
	Node *head_;

public:
	BaseOctree();
	~BaseOctree();
	void insert(int, int, T);
	void print();
	void clear();
	void save(std::ostream &);
	void load(std::istream &);

protected:
	void insert(Node *&, int, int, T);
	void print(Node *, int level);
	void kill(Node *);
	long long save(Node *, std::ostream &);
	Node *load(long long, std::istream &);
	virtual void save_header(std::ostream &);
	virtual void load_header(std::istream &);
};

} // namespace octree

} // namespace eda

#include "impl/base_octree.ipp"

#endif // OCTREE_BASE_OCTREE_HPP_
