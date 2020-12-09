import cv2
import numpy
import matplotlib.pyplot as plt
import os
import sys

if (len(sys.argv)) != 3: 
	print("error: missign arguments. Usage: python3", sys.argv[0], "<image_path> <index_path>")
	exit()

# n_img = "data/image/input.png"
n_img = sys.argv[1]
img = cv2.imread(n_img);
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

altura  = img.shape[0]
ancho = img.shape[1]

# f = open("data/rgb/test.in", 'w')
f = open(sys.argv[2], 'w')
f.write(str(ancho))
f.write(" ")
f.write(str(altura) + "\n")

for i in range(altura):
  for j in range(ancho):
    f.write(str(img[i][j][0]) + " ")
    f.write(str(img[i][j][1]) + " ")
    f.write(str(img[i][j][2]) + " ")
    f.write('\n')

f.close()

