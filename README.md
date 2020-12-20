# Octree

Octree implementation.

## Setup

Run `setup.sh` to create directories and compile executables.

## Usage

### Octree

Test the plain octree implementation with

```
./bin/octree/octree < data/octree/test.in
```

### 3D Image Octree

There are two supported 3D image formats: binary images and RGB images.

#### Binary images

Binary images consist of pixels whose values are either 0 or 1. In these kind of images, both the original an reconstructed image are the same. We can observe this behavior by running the following lines

```
./bin/binary/reconstruction < data/binary/sphere.in
```

which load a binary 3D image of a sphere. If needed, custom sphere images can be generated with `./bin/data/sphere` which receives the radius of the sphere as input. To test any manually generated 3D image, first give the width, height and depth of the image in a first line, followed by width \* height \* depth chars (0 or 1), as in data/binary/sphere.in.

#### RGB images

RGB images are composed of pixels with red, green and blue channels whose values range between 0 and 255.

## Tests

### Execution time

Both the octree and the grid representations of a 3D image implement an slicing function. To measure and compare the execution time of both structures we can run

```
./bin/measure/time data/mri <structure>
```

and give the number of queries as input. _Note_: when the selected structure is octree, the first argument is **always** the threshold the octree uses to compress the image.

### RAM usage


## Results

| Grid | Octree |
| ---- | ------ |
| ![Grid frontal scan](docs/gif/grid_frontal_scan.gif)<br> `./bin/rgb/scan data/mri/ grid < data/input/grid_frontal_scan.in` | ![Grid corner scan](docs/gif/octree_frontal_scan.gif)<br> `./bin/rgb/scan data/mri/ octree < data/input/octree_frontal_scan.in` |
| ![Grid corner scan](docs/gif/grid_corner_scan.gif)<br> `./bin/rgb/scan data/mri/ grid < data/input/grid_corner_scan.in` | ![Octree corner scan](docs/gif/octree_corner_scan.gif)<br> `./bin/rgb/scan data/mri/ octree < data/input/octree_corner_scan.in` |
| ![Grid rotation](docs/gif/grid_rotation.gif)<br> `./bin/rgb/rotation data/mri/ grid < data/input/grid_rotation.in` | ![Octree rotation](docs/gif/octree_rotation.gif)<br> `./bin/rgb/rotation data/mri/ octree < data/input/octree_rotation.in` |
