#include "scan_octree.hpp"
#include "node.hpp"

namespace eda {

namespace octree {

ScanOctree::ScanOctree(int width, int height, int depth) :
	BaseImageOctree(width, height, depth)
{ }

ScanOctree::ScanOctree(Image3D &image, double threshold) :
	BaseImageOctree(image)
{
	this->build(this->head_, image, threshold, 0, this->width_ - 1, 0, this->height_ - 1, 0, this->depth_ - 1);
}

void ScanOctree::fill(Image3D &image) {
	this->fill(this->head_, image, 0, this->width_ - 1, 0, this->height_ - 1, 0, this->depth_ - 1);
}

void ScanOctree::build(Node<Pixel> *&node, Image3D &image, double threshold, int x_i, int x_f, int y_i, int y_f, int z_i, int z_f) {
	int mid_x = (x_i + x_f) / 2;
	int mid_y = (y_i + y_f) / 2;
	int mid_z = (z_i + z_f) / 2;

	if (x_i > x_f || y_i > y_f || z_i > z_f) {
		node = nullptr;
		return;
	}

	if (this->same_color(image, threshold, x_i, x_f, y_i, y_f, z_i, z_f)) {
		node = new Node<Pixel>(mid_x, mid_y, mid_z, this->average_pixel(image, x_i, x_f, y_i, y_f, z_i, z_f));
		return;
	}

	Pixel tmp;
	node = new Node<Pixel>(mid_x, mid_y, mid_z, tmp);
	
	this->build(node->children_[0], image, threshold, x_i, mid_x, y_i, mid_y, z_i, mid_z);
	this->build(node->children_[1], image, threshold, mid_x + 1, x_f, y_i, mid_y, z_i, mid_z);
	this->build(node->children_[2], image, threshold, x_i, mid_x, mid_y + 1, y_f, z_i, mid_z);
	this->build(node->children_[3], image, threshold, mid_x + 1, x_f, mid_y + 1, y_f, z_i, mid_z);
	this->build(node->children_[4], image, threshold, x_i, mid_x, y_i, mid_y, mid_z + 1, z_f);
	this->build(node->children_[5], image, threshold, mid_x + 1, x_f, y_i, mid_y, mid_z + 1, z_f);
	this->build(node->children_[6], image, threshold, x_i, mid_x, mid_y + 1, y_f, mid_z + 1, z_f);
	this->build(node->children_[7], image, threshold, mid_x + 1, x_f, mid_y + 1, y_f, mid_z + 1, z_f);
}

bool ScanOctree::same_color(Image3D &image, double threshold, int x_i, int x_f, int y_i, int y_f, int z_i, int z_f) {
	if (x_i > x_f || y_i > y_f || z_i > z_f) return true;

	int min_color, max_color;

	min_color = max_color = image.grid()[z_i][y_i][x_i].average();

	for (int z = z_i; z <= z_f; z++) {
		for (int y = y_i; y <= y_f; y++) {
			for (int x = x_i; x <= x_f; x++) {
				int color = image.grid()[z][y][x].average();

				if (color < min_color) min_color = color;
				if (color > max_color) max_color = color;

				if (max_color - min_color >= threshold) {
					return false;
				}
			}
		}
	}

	return true;
}

Pixel ScanOctree::average_pixel(Image3D &image, int x_i, int x_f, int y_i, int y_f, int z_i, int z_f) {
	int r = 0, g = 0, b = 0;

	for (int z = z_i; z <= z_f; z++) {
		for (int y = y_i; y <= y_f; y++) {
			for (int x = x_i; x <= x_f; x++) {
				Pixel pixel = image.grid()[z][y][x];

				r += pixel.r;
				g += pixel.g;
				b += pixel.b;
			}
		}
	}

	int total = (x_f - x_i + 1) * (y_f - y_i + 1) * (z_f - z_i + 1);

	return Pixel(r / total, g / total, b / total);
}

void ScanOctree::fill(Node<Pixel> *node, Image3D &image, int x_i, int x_f, int y_i, int y_f, int z_i, int z_f) {
	if (node == nullptr) return;

	if (node->is_leave()) {
		for (int z = z_i; z <= z_f; z++) {
			for (int y = y_i; y <= y_f; y++) {
				for (int x = x_i; x <= x_f; x++) {
					image.grid()[z][y][x] = node->data_;
				}
			}
		}
		return;
	}

	int mid_x = node->x_;
	int mid_y = node->y_;
	int mid_z = node->z_;

	this->fill(node->children_[0], image, x_i, mid_x, y_i, mid_y, z_i, mid_z);
	this->fill(node->children_[1], image, mid_x + 1, x_f, y_i, mid_y, z_i, mid_z);
	this->fill(node->children_[2], image, x_i, mid_x, mid_y + 1, y_f, z_i, mid_z);
	this->fill(node->children_[3], image, mid_x + 1, x_f, mid_y + 1, y_f, z_i, mid_z);
	this->fill(node->children_[4], image, x_i, mid_x, y_i, mid_y, mid_z + 1, z_f);
	this->fill(node->children_[5], image, mid_x + 1, x_f, y_i, mid_y, mid_z + 1, z_f);
	this->fill(node->children_[6], image, x_i, mid_x, mid_y + 1, y_f, mid_z + 1, z_f);
	this->fill(node->children_[7], image, mid_x + 1, x_f, mid_y + 1, y_f, mid_z + 1, z_f);
}

} // namespace octree

} // namespace eda
