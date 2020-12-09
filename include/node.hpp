#ifndef OCTREE_NODE_HPP_
#define OCTREE_NODE_HPP_

#include "base_node.hpp"

namespace eda {

namespace octree {

template <typename T>
class Node : public BaseNode<T, Node<T> > {
public:
	Node(int, int, int, T);
};

} // namespace octree

} // namespace eda

#include "impl/node.ipp"

#endif // OCTREE_NODE_HPP_
