# Octree

Octree implementation.

## Setup

Run `setup.sh` to create directories and compile executables.

## Tests

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

##### Examples

Example scan, from frontal face position towards the back.

**Pixel grid:**

![Corner scan](docs/gif/grid_frontal_scan.gif)

Generated with

```
./bin/rgb/scan data/mri/ grid < data/input/grid_frontal_scan.in
```

**Octree:**

![Corner scan](docs/gif/octree_frontal_scan.gif)

Generated with

```
./bin/rgb/scan data/mri/ octree < data/input/octree_frontal_scan.in
```

Example scan, from one corner to its oposite of the 3D image.

**Pixel grid:**

![Corner scan](data/gif/grid_corner_scan.gif)

Generated with

```
./bin/rgb/scan data/mri/ grid < data/input/grid_corner_scan.in
```

**Octree:**

![Corner scan](data/gif/octree_corner_scan.gif)

Generated with

```
./bin/rgb/scan data/mri/ octree < data/input/octree_corner_scan.in
```

Example rotation, starting at a frontal position and rotationg on the y axis.

**Pixel grid:**

![Corner scan](data/gif/grid_rotation.gif)

Generated with

```
./bin/rgb/rotation data/mri/ grid < data/input/grid_rotation.in
```

**Octree:**

![Corner scan](data/gif/octree_rotation.gif)

Generated with

```
./bin/rgb/rotation data/mri/ octree < data/input/octree_rotation.in
```



##### Examples

| Grid | Octree |
| ---- | ------ |
| ![Grid frontal scan](docs/gif/grid_frontal_scan.gif)<br> `./bin/rgb/scan data/mri/ grid < data/input/grid_frontal_scan.in` | ![Grid corner scan](docs/gif/octree_frontal_scan.gif)<br> `./bin/rgb/scan data/mri/ octree < data/input/octree_frontal_scan.in` |
| ![Grid corner scan](docs/gif/grid_corner_scan.gif)<br> `./bin/rgb/scan data/mri/ grid < data/input/grid_corner_scan.in` | ![Octree corner scan](docs/gif/octree_corner_scan.gif)<br> `./bin/rgb/scan data/mri/ octree < data/input/octree_corner_scan.in` |
| ![Grid rotation](docs/gif/grid_rotation.gif)<br> `./bin/rgb/rotation data/mri/ grid < data/input/grid_rotation.in` | ![Octree rotation](docs/gif/octree_rotation.gif)<br> `./bin/rgb/rotation data/mri/ octree < data/input/octree_rotation.in` |
