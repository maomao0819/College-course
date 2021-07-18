import numpy as np
import cv2

img = cv2.imread('IU.png')
new_img = img.copy()
height, weidth, channal = new_img.shape
h = 3 * height
w = 3 * weidth
c = channal
#Nearest-Neighbor Interpolation
dim = (w, h)
nn = cv2.resize(new_img, dim, interpolation = cv2.INTER_NEAREST)
'''
nn = np.zeros((h, w, c), np.uint8)
for i in range(h):
	for j in range(w):
		nn[i, j] = new_img[int(i / 3), int(j / 3)]
		
		nn_h = int(np.round(i / 3) if np.round(i / 3) < height else height - 1)
		nn_w = int(np.round(j / 3) if np.round(j / 3) < weidth else weidth - 1)
		nn[i, j] = new_img[nn_h, nn_w]

		nn_h = int(np.round(i / 3))
		if nn_h >= height:
			nn_h = int(height - 1)
		nn_w = int(np.round(j / 3))
		if nn_w >= weidth:
			nn_w = int(weidth - 1)
		nn[i, j] = new_img[nn_h, nn_w]

h = h - 3
w = w - 3
for i in range(h):
	for j in range(w):
		nn_h = int(np.round(i / 3))
		nn_w = int(np.round(j / 3)) 
		nn[i, j] = new_img[nn_h, nn_w]
for i in range(h, h + 3):
	for j in range(w, w + 3):
		nn_h = int(np.round(i / 3) if np.round(i / 3) < height else height - 1)
		nn_w = int(np.round(j / 3) if np.round(j / 3) < weidth else weidth - 1)
		nn[i, j] = new_img[nn_h, nn_w]
'''
#nn = nn.astype(np.uint8)
cv2.imshow('IU', nn)
cv2.imwrite('hw1_2.png', nn)
cv2.waitKey(0)
cv2.destroyAllWindows()