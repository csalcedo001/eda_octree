#include "scan_octree.hpp"
#include "node.hpp"

namespace eda {

namespace octree {

ScanOctree::ScanOctree(int width, int height, double threshold) :
	BaseImageOctree(width, height, threshold)
{ }

ScanOctree::ScanOctree(Image3D &image, double threshold) :
	BaseImageOctree(image, threshold)
{
	this->build(this->head_, image, 0, this->width_ - 1, 0, this->height_ - 1);
}

void ScanOctree::fill(Image3D &image) {
	this->fill(this->head_, image, 0, this->width_ - 1, 0, this->height_ - 1);
}

void ScanOctree::build(Node<Pixel> *&node, Image3D &image, int x_i, int x_f, int y_i, int y_f) {
	int mid_x = (x_i + x_f) / 2;
	int mid_y = (y_i + y_f) / 2;

	if (x_i > x_f || y_i > y_f) {
		node = nullptr;
		return;
	}

	if (this->same_color(image, x_i, x_f, y_i, y_f)) {
		node = new Node<Pixel>(mid_x, mid_y, this->average_pixel(image, x_i, x_f, y_i, y_f));
		return;
	}

	Pixel tmp;
	node = new Node<Pixel>(mid_x, mid_y, tmp);
	
	this->build(node->children_[0], image, x_i, mid_x, y_i, mid_y);
	this->build(node->children_[1], image, mid_x + 1, x_f, y_i, mid_y);
	this->build(node->children_[2], image, x_i, mid_x, mid_y + 1, y_f);
	this->build(node->children_[3], image, mid_x + 1, x_f, mid_y + 1, y_f);
}

bool ScanOctree::same_color(Image3D &image, int x_i, int x_f, int y_i, int y_f) {
	if (x_i > x_f || y_i > y_f) return true;

	int min_color, max_color;

	min_color = max_color = image.grid()[y_i][x_i].average();

	for (int j = y_i; j <= y_f; j++) {
		for (int i = x_i; i <= x_f; i++) {
			int color = image.grid()[j][i].average();

			if (color < min_color) min_color = color;
			if (color > max_color) max_color = color;

			if (max_color - min_color >= this->threshold_) {
				return false;
			}
		}
	}

	return true;
}

Pixel ScanOctree::average_pixel(Image3D &image, int x_i, int x_f, int y_i, int y_f) {
	int r = 0, g = 0, b = 0;

	for (int j = y_i; j <= y_f; j++) {
		for (int i = x_i; i <= x_f; i++) {
			Pixel pixel = image.grid()[j][i];

			r += pixel.r;
			g += pixel.g;
			b += pixel.b;
		}
	}

	int total = (x_f - x_i + 1) * (y_f - y_i + 1);

	return Pixel(r / total, g / total, b / total);
}

void ScanOctree::fill(Node<Pixel> *node, Image3D &image, int x_i, int x_f, int y_i, int y_f) {
	if (node == nullptr) return;

	if (node->is_leave()) {
		for (int j = y_i; j <= y_f; j++) {
			for (int i = x_i; i <= x_f; i++) {
				image.grid()[j][i] = node->data_;
			}
		}
		return;
	}

	int mid_x = node->x_;
	int mid_y = node->y_;

	this->fill(node->children_[0], image, x_i, mid_x, y_i, mid_y);
	this->fill(node->children_[1], image, mid_x + 1, x_f, y_i, mid_y);
	this->fill(node->children_[2], image, x_i, mid_x, mid_y + 1, y_f);
	this->fill(node->children_[3], image, mid_x + 1, x_f, mid_y + 1, y_f);
}

} // namespace octree

} // namespace eda
