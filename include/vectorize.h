#include <iostream>
#include <vector>

#include "CImg.h"
using namespace cimg_library;
using namespace std;

vector<vector<int>> get_matrix(CImg<double> & img, int umbral) {
	vector<vector<int>> matrix;
	for (int y = 0; y < img.height(); ++y) {
		vector<int> v;
		for (int x = 0; x < img.width(); ++x) {
			int grey = (img(x,y,0) + img(x,y,1) + img(x,y,2)) / 3;
			v.push_back((grey>umbral)?255:0);
		}
		matrix.push_back(v);
	}

	return matrix;
}


vector<vector<vector<int>>> get_vectors_from_mri(string directory, string filename, int n_max, int umbral) {
	vector<vector<vector<int>>> images(n_max+1);
	for (int i = 0; i <= n_max; ++i) {
		string path = directory;
		path.append("/" + filename + to_string(i) + ".BMP");
		CImg<double> img(path.c_str());
		images[i] = get_matrix(img, umbral);
	}
	return images;
}

int pixel(vector<vector<vector<int>>> & img, int x, int y, int z) {
	return img[z][y][x];
}

CImg<char> get_image_from_matrix(vector<vector<int>> & matrix) {
    CImg<char> img(matrix[0].size(), matrix.size());
    for (int y = 0; y < matrix.size(); ++y) {
        for (int x = 0; x < matrix[y].size(); ++x)
            img(x,y,0) = matrix[y][x];
    }
    return img;
}

