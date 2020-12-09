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
void BaseOctree<T, Node>::insert(int x, int y, T data) {
	this->insert(this->head_, x, y, data);
}

template <typename T, class Node>
void BaseOctree<T, Node>::print() {
	this->print(this->head_, 0);
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

	os.seekp(2 * sizeof(int) + sizeof(T) + 4 * sizeof(long long), os.cur);

	long long disk_children[4];

	for (int i = 0; i < 4; i++) {
		disk_children[i] = this->save(this->head_->children_[i], os);
	}

	os.seekp(data_position, os.beg);

	os.write((char *) &this->head_->x_, sizeof(int));
	os.write((char *) &this->head_->y_, sizeof(int));
	os.write((char *) &this->head_->data_, sizeof(T));

	for (int i = 0; i < 4; i++) {
		os.write((char *) &disk_children[i], sizeof(long long));
	}
}

template <typename T, class Node>
void BaseOctree<T, Node>::load(std::istream &is) {
	this->clear();

	is.seekg(0, is.beg);

	this->load_header(is);

	int x, y;
	T data;

	is.read((char *) &x, sizeof(int));
	is.read((char *) &y, sizeof(int));
	is.read((char *) &data, sizeof(T));

	this->head_ = new Node(x, y, data);

	long long positions[4];

	for (int i = 0; i < 4; i++) {
		is.read((char *) &positions[i], sizeof(long long));
	}

	for (int i = 0; i < 4; i++) {
		this->head_->children_[i] = this->load(positions[i], is);
	}
}

template <typename T, class Node>
void BaseOctree<T, Node>::insert(Node *&node, int x, int y, T data) {
	if (node == nullptr) {
		node = new Node(x, y, data);
		return;
	}

	bool right_side = x > node->x_;
	bool down_side = y > node->y_;

	this->insert(node->children_[(down_side << 1) + right_side], x, y, data);
}

template <typename T, class Node>
void BaseOctree<T, Node>::print(Node *node, int level) {
	if (node != nullptr) {
		this->print(node->children_[0], level + 1);
		this->print(node->children_[1], level + 1);

		for (int i = 0; i < level; i++) {
			std::cout << "    ";
		}
		std::cout << node->x_ << ' ' << node->y_ << ": " << node->data_ << std::endl;

		this->print(node->children_[2], level + 1);
		this->print(node->children_[3], level + 1);
	}
}

template <typename T, class Node>
void BaseOctree<T, Node>::kill(Node *node) {
	if (node != nullptr) {
		this->kill(node->children_[0]);
		this->kill(node->children_[1]);
		this->kill(node->children_[2]);
		this->kill(node->children_[3]);
	}
}

template <typename T, class Node>
long long BaseOctree<T, Node>::save(Node *node, std::ostream &os) {
	if (node == nullptr) return 0;

	long long disk_children[4];

	for (int i = 0; i < 4; i++) {
		disk_children[i] = this->save(node->children_[i], os);
	}

	long long position = os.tellp();

	os.write((char *) &node->x_, sizeof(int));
	os.write((char *) &node->y_, sizeof(int));
	os.write((char *) &node->data_, sizeof(T));

	for (int i = 0; i < 4; i++) {
		os.write((char *) &disk_children[i], sizeof(long long));
	}

	return position;
}

template <typename T, class Node>
Node *BaseOctree<T, Node>::load(long long position, std::istream &is) {
	if (position == 0) return nullptr;

	is.seekg(position, is.beg);

	int x, y;
	T data;

	is.read((char *) &x, sizeof(int));
	is.read((char *) &y, sizeof(int));
	is.read((char *) &data, sizeof(T));

	Node *node = new Node(x, y, data);

	long long positions[4];

	for (int i = 0; i < 4; i++) {
		is.read((char *) &positions[i], sizeof(long long));
	}

	for (int i = 0; i < 4; i++) {
		node->children_[i] = this->load(positions[i], is);
	}

	return node;
}

template <typename T, class Node>
void BaseOctree<T, Node>::save_header(std::ostream &os) { }

template <typename T, class Node>
void BaseOctree<T, Node>::load_header(std::istream &is) { }

} // namespace octree

} // namespace eda

#endif // OCTREE_BASE_OCTREE_IPP_
