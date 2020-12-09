#ifndef OCTREE_OCTREE_HPP_
#define OCTREE_OCTREE_HPP_

#include "base_octree.hpp"
#include "node.hpp"

namespace eda {

namespace octree {

template <typename T>
class Octree : public BaseOctree<T, Node<T> > { };

} // namespace octree

} // namespace eda

#endif // OCTREE_OCTREE_HPP_
