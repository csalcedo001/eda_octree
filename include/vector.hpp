#ifndef OCTREE_VECTOR_HPP_
#define OCTREE_VECTOR_HPP_

namespace eda {

namespace octree {

class Vector {
public:
	double x, y, z;

	Vector() = default;
	Vector(int, int, int);
	Vector(const Vector &);

	double length();

	Vector operator+(Vector);
	Vector operator-(Vector);
	Vector operator*(double);
	Vector operator/(double);
};

} // namespace octree

} // namespace eda

#endif // OCTREE_VECTOR_HPP_
