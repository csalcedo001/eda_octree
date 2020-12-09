import cv2
import numpy as np
import matplotlib.pyplot as plt

n_file = "data/rgb/test.out"
n_img = "data/image/result.png"

f = open(n_file, 'r')
altura = 0
ancho = 0
if f.mode == 'r':
	line = f.readline()
	b,a = line.split()
	altura  = int(a)
	ancho = int(b)

img = np.empty((altura, ancho, 3))
a = ""
b = ""
c = ""

if f.mode == 'r':
	for i in range(altura):
		for j in range(ancho):
			line = f.readline()
			a, b, c = line.split();
			img[i][j][2] = int(a)
			img[i][j][1] = int(b)
			img[i][j][0] = int(c)

f.close()
cv2.imwrite(n_img, img)
