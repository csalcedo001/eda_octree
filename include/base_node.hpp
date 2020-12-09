#ifndef OCTREE_BASE_NODE_HPP_
#define OCTREE_BASE_NODE_HPP_

namespace eda {

namespace octree {

template <typename T, class Node>
class BaseNode {
public:
	int x_;
	int y_;
	T data_;
	Node *children_[4];

public:
	BaseNode(int, int, T &);
	bool is_leave();
};

} // namespace octree

} // namespace eda

#include "impl/base_node.ipp"

#endif // OCTREE_BASE_NODE_HPP_
