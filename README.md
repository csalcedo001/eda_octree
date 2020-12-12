# Octree

Octree implementation

## Setup

Run `make` to compile the executables and run tests.

## Tests

### Octree

Test the plain octree implementation with

```
./bin/octree < data/octree/test.in
```

There are two evaluated 3D image formats: binary images and RGB images.

### 3D Image Octree

#### Binary images

Binary images consist of pixels whose values are only 0 or 1. In these kind of images, both the original an reconstructed image be the same. We can observe this behavior by running the following lines

```
./bin/binary < data/binary/sphere.in
```

which loads a precalculated binary 3D image of a sphere. If needed, custom sphere images can be generated with `./bin/sphere` which receives the radius of the sphere as input. To test any manually generated 3D image, first give the width, height and depth of the image in a first line, followed by width \* height \* depth chars (0 or 1).
