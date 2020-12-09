#ifndef OCTREE_NODE_IPP_
#define OCTREE_NODE_IPP_

#include "base_node.hpp"

namespace eda {

namespace octree {

template <typename T>
Node<T>::Node(int x, int y, T data) :
	BaseNode<T, Node<T> >(x, y, data)
{ }

} // namespace octree

} // namespace eda

#endif // OCTREE_NODE_IPP_
