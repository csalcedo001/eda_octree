#ifndef OCTREE_BASE_NODE_IPP_
#define OCTREE_BASE_NODE_IPP_

#include "base_node.hpp"

namespace eda {

namespace octree {

template <typename T, class Node>
BaseNode<T, Node>::BaseNode(int x, int y, int z, T &data) :
	x_(x),
	y_(y),
	z_(z),
	data_(data)
{
	int l = 8;

	while (l--) {
		this->children_[l] = nullptr;
	}
}

template <typename T, class Node>
bool BaseNode<T, Node>::is_leave() {
	int l = 8;

	while (l--) {
		if (this->children_[l] != nullptr) return false;
	}

	return true;
}

} // namespace octree

} // namespace eda

#endif // OCTREE_BASE_NODE_IPP_
