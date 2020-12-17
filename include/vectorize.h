#ifndef OCTREE_VECTORIZE_HPP_
#define OCTREE_VECTORIZE_HPP_

#include <iostream>
#include <vector>

#include "CImg.h"
#include "pixel.hpp"

namespace eda {

namespace octree {

std::vector<std::vector<Pixel>> get_matrix(cimg_library::CImg<double> &img, int umbral) {
	std::vector<std::vector<Pixel>> matrix;

	for (int y = 0; y < img.height(); ++y) {
		std::vector<Pixel> v;

		for (int x = 0; x < img.width(); ++x) {
			v.push_back(eda::octree::Pixel(img(x, y, 0), img(x, y, 1), img(x, y, 2)));
		}
		matrix.push_back(v);
	}

	return matrix;
}


std::vector<std::vector<std::vector<Pixel>>> get_vectors_from_mri(std::string directory, std::string filename, int n_max, int umbral) {
	std::vector<std::vector<std::vector<Pixel>>> images(n_max + 1);
	
	for (int i = 0; i <= n_max; ++i) {
		auto path = directory;
		path.append("/" + filename + std::to_string(i) + ".BMP");

		cimg_library::CImg<double> img(path.c_str());

		images[i] = get_matrix(img, umbral);
	}

	return images;
}

// Pixel pixel(std::vector<std::vector<std::vector<Pixel>>> &img, int x, int y, int z) {
// 	return img[z][y][x];
// }

cimg_library::CImg<double> get_image_from_matrix(std::vector<std::vector<Pixel>> &matrix) {
	int width = matrix[0].size();
	int height = matrix.size();

    cimg_library::CImg<double> img(width, height, 1, 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            img(x, y, 0) = matrix[y][x].r;
            img(x, y, 1) = matrix[y][x].g;
            img(x, y, 2) = matrix[y][x].b;
		}
    }

    return img;
}

} // namespace octree

} // namespace eda

#endif // OCTREE_VECTORIZE_HPP_
