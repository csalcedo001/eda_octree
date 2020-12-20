#ifndef OCTREE_BASE_OCTREE_IPP_
#define OCTREE_BASE_OCTREE_IPP_

#include "base_octree.hpp"

#include <iostream>
#include <vector>

namespace eda {

namespace octree {

template <typename T, class Node>
BaseOctree<T, Node>::BaseOctree() :
	head_(nullptr)
{ }

template <typename T, class Node>
BaseOctree<T, Node>::~BaseOctree() {
	this->clear();
}

template <typename T, class Node>
void BaseOctree<T, Node>::insert(int x, int y, int z, T data) {
	this->insert(this->head_, x, y, z, data);
}

template <typename T, class Node>
void BaseOctree<T, Node>::print() {
	this->print(this->head_, 0, 0);
}

template <typename T, class Node>
void BaseOctree<T, Node>::clear() {
	this->kill(this->head_);
}

template <typename T, class Node>
void BaseOctree<T, Node>::save(std::ostream &os) {
	if (this->head_ == nullptr) return;

	os.seekp(0, os.beg);

	this->save_header(os);

	long long data_position = os.tellp();

	os.seekp(3 * sizeof(int) + sizeof(T) + 8 * sizeof(long long), os.cur);

	long long disk_children[8];

	for (int i = 0; i < 8; i++) {
		disk_children[i] = this->save(this->head_->children_[i], os);
	}

	os.seekp(data_position, os.beg);

	os.write((char *) &this->head_->x_, sizeof(int));
	os.write((char *) &this->head_->y_, sizeof(int));
	os.write((char *) &this->head_->z_, sizeof(int));
	os.write((char *) &this->head_->data_, sizeof(T));

	for (int i = 0; i < 8; i++) {
		os.write((char *) &disk_children[i], sizeof(long long));
	}
}

template <typename T, class Node>
void BaseOctree<T, Node>::load(std::istream &is) {
	this->clear();

	is.seekg(0, is.beg);

	this->load_header(is);

	int x, y, z;
	T data;

	is.read((char *) &x, sizeof(int));
	is.read((char *) &y, sizeof(int));
	is.read((char *) &z, sizeof(int));
	is.read((char *) &data, sizeof(T));

	this->head_ = new Node(x, y, z, data);

	long long positions[8];

	for (int i = 0; i < 8; i++) {
		is.read((char *) &positions[i], sizeof(long long));
	}

	for (int i = 0; i < 8; i++) {
		this->head_->children_[i] = this->load(positions[i], is);
	}
}

template <typename T, class Node>
size_t BaseOctree<T, Node>::getRAM() {
	return getRAM(head_);
}

template <typename T, class Node>
void BaseOctree<T, Node>::insert(Node *&node, int x, int y, int z, T data) {
	if (node == nullptr) {
		node = new Node(x, y, z, data);
		return;
	}

	bool right_side = x > node->x_;
	bool down_side = y > node->y_;
	bool back_side = z > node->z_;

	this->insert(node->children_[(back_side << 2) + (down_side << 1) + right_side], x, y, z, data);
}

template <typename T, class Node>
void BaseOctree<T, Node>::print(Node *node, int level, int quadrant) {
	if (node != nullptr) {
		int l = 0;

		for (; l < 4; l++) {
			this->print(node->children_[l], level + 1, l);
		}

		for (int i = 0; i < level; i++) {
			std::cout << "    ";
		}
		std::cout << '(' << quadrant << ") " << node->x_ << ' ' << node->y_ << ' ' << node->z_ << ": " << node->data_ << std::endl;


		for (; l < 8; l++) {
			this->print(node->children_[l], level + 1, l);
		}
	}
}

template <typename T, class Node>
void BaseOctree<T, Node>::kill(Node *node) {
	if (node != nullptr) {
		int l = 8;

		while (l--) {
			this->kill(node->children_[l]);
		}
	}
}

template <typename T, class Node>
long long BaseOctree<T, Node>::save(Node *node, std::ostream &os) {
	if (node == nullptr) return 0;

	long long disk_children[8];

	for (int i = 0; i < 8; i++) {
		disk_children[i] = this->save(node->children_[i], os);
	}

	long long position = os.tellp();

	os.write((char *) &node->x_, sizeof(int));
	os.write((char *) &node->y_, sizeof(int));
	os.write((char *) &node->z_, sizeof(int));
	os.write((char *) &node->data_, sizeof(T));

	for (int i = 0; i < 8; i++) {
		os.write((char *) &disk_children[i], sizeof(long long));
	}

	return position;
}

template <typename T, class Node>
Node *BaseOctree<T, Node>::load(long long position, std::istream &is) {
	if (position == 0) return nullptr;

	is.seekg(position, is.beg);

	int x, y, z;
	T data;

	is.read((char *) &x, sizeof(int));
	is.read((char *) &y, sizeof(int));
	is.read((char *) &z, sizeof(int));
	is.read((char *) &data, sizeof(T));

	Node *node = new Node(x, y, z, data);

	long long positions[8];

	for (int i = 0; i < 8; i++) {
		is.read((char *) &positions[i], sizeof(long long));
	}

	for (int i = 0; i < 8; i++) {
		node->children_[i] = this->load(positions[i], is);
	}

	return node;
}

template <typename T, class Node>
void BaseOctree<T, Node>::save_header(std::ostream &os) { }

template <typename T, class Node>
void BaseOctree<T, Node>::load_header(std::istream &is) { }

template <typename T, class Node>
size_t BaseOctree<T, Node>::getRAM(Node *node) {
	if (node) {
		size_t size = node->getRAM();
		for (int i = 0; i < 8; i++) {
            size += getRAM(node->children_[i]);
        }
        return size;
	}
	return 0;
}


} // namespace octree

} // namespace eda

#endif // OCTREE_BASE_OCTREE_IPP_
