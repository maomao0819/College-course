import numpy as np
import cv2
import math
img = cv2.imread('mj.tif')
new_img = img.copy()
height, weidth, channal = new_img.shape

total_pixel = height * weidth
num_pixel = np.zeros(256)
freq_pixel = np.zeros(256)
out_value = np.zeros(256)

for h in range(height):
	for w in range(weidth):
		color = new_img[h, w]
		gray_intensity = int((color[0] / 3 + color[1] / 3 + color[2] / 3))
		new_img[h, w] = gray_intensity
		num_pixel[gray_intensity] += 1
#Histogram Equalization
for idx in range(256):
	freq_pixel[idx] = num_pixel[idx] / total_pixel

for idx in range(255):
	freq_pixel[idx + 1] = freq_pixel[idx] + freq_pixel[idx + 1] 

for idx in range(256):
	out_value[idx] = int(freq_pixel[idx] * 255)

for h in range(height):
	for w in range(weidth):
		new_img[h, w] = out_value[new_img[h, w]]

cv2.imshow('Michael Jackson', new_img)
cv2.imwrite('hw2_1.tif', new_img)
cv2.waitKey(0)
cv2.destroyAllWindows()

