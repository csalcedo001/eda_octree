#ifndef OCTREE_NODE_IPP_
#define OCTREE_NODE_IPP_

#include "base_node.hpp"

namespace eda {

namespace octree {

template <typename T>
Node<T>::Node(int x, int y, int z, T data) :
	BaseNode<T, Node<T> >(x, y, z, data)
{ }

} // namespace octree

} // namespace eda

#endif // OCTREE_NODE_IPP_
