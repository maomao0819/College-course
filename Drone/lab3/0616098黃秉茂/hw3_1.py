import numpy as np
import cv2
import math
img = cv2.imread('input.jpg')
new_img = img.copy()
height, weidth, channal = new_img.shape

total_pixel = height * weidth
num_pixel = np.zeros(256)
sum_pixel = 0
for h in range(height):
	for w in range(weidth):
		color = new_img[h, w]
		gray_intensity = int(color[0])
		num_pixel[gray_intensity] += 1
		sum_pixel += gray_intensity

num_b = num_pixel[0]
num_o = total_pixel - num_b
avg_b = 0 * num_b / num_b
avg_o = sum_pixel / num_o
variance_between = np.zeros(256)
for pixel in range(255):
	next_pixel = pixel + 1
	next_num_b = num_b + num_pixel[next_pixel]
	next_num_o = num_o - num_pixel[next_pixel]
	#next_num_o = total_pixel - next_num_b
	variance_between[pixel] = num_b * num_o * (avg_b - avg_o) * (avg_b - avg_o)
											  #math.pow((avg_b - avg_o), 2)
	if next_num_b > 0 and next_num_o > 0:
		next_avg_b = (avg_b * num_b + (next_pixel) * num_pixel[next_pixel]) / next_num_b
		next_avg_o = (avg_o * num_o - (next_pixel) * num_pixel[next_pixel]) / next_num_o
	num_b = next_num_b
	num_o = next_num_o
	avg_b = next_avg_b
	avg_o = next_avg_o

threshold = np.where(variance_between == max(variance_between))
Otsu_Threshold = int(threshold[0])
for h in range(height):
	for w in range(weidth):
		if new_img[h, w, 0] > Otsu_Threshold:
			for i in range(3):
				new_img[h, w, i] = 255
		else:
			for i in range(3):
				new_img[h, w, i] = 0
				
cv2.imshow('Otsu Threshold', new_img)
cv2.imwrite('hw3_1.jpg', new_img)
cv2.waitKey(0)
cv2.destroyAllWindows()