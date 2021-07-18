import numpy as np
import cv2
import math
img = cv2.imread('HyunBin.jpg')
new_img = img.copy()
height, weidth, channal = new_img.shape

#Histogram Equalization
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

for idx in range(256):
	freq_pixel[idx] = num_pixel[idx] / total_pixel

for idx in range(255):
	freq_pixel[idx + 1] = freq_pixel[idx] + freq_pixel[idx + 1] 

for idx in range(256):
	out_value[idx] = int(freq_pixel[idx] * 255)

for h in range(height):
	for w in range(weidth):
		new_img[h, w] = out_value[new_img[h, w]] 
new_img = new_img[:, :, :1]

sample_matrix = [[0, 0, 0], [1, 1, 1], [0, 0, 0]]
x_matrix = [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
y_matrix = [[-1, -2, -1], [0, 0, 0], [1, 2, 1]]

threshold = 100
Sobel_img_x = np.zeros((height - 2, weidth - 2))
Sobel_img_y = np.zeros((height - 2, weidth - 2))
Sobel_img_out = np.zeros((height - 2, weidth - 2))

for h in range(height - 2):
	for w in range(weidth - 2):
		for i in range(3):
			for j in range(3):
				Sobel_img_x[h, w] += int(img[h + i, w + j, 0]) * x_matrix[i][j]
				Sobel_img_y[h, w] += int(img[h + i, w + j, 0]) * y_matrix[i][j]
		#Sobel_img_out[h, w] = math.sqrt(Sobel_img_x[h, w] ** 2 + Sobel_img_y[h, w] ** 2) 
		Sobel_img_x[h, w] = 255 if Sobel_img_x[h, w] > threshold else 0
		Sobel_img_y[h, w] = 255 if Sobel_img_y[h, w] > threshold else 0
		#Sobel_img_out[h, w] = 255 if Sobel_img_out[h, w] > threshold else 0
		if Sobel_img_x[h, w] > 0 or Sobel_img_y[h, w] > 0:
			Sobel_img_out[h, w] = 255
		
Sobel_img_x.astype(np.uint8)
Sobel_img_y.astype(np.uint8)
Sobel_img_out.astype(np.uint8)

cv2.imshow('Histogram Equalization', new_img)
cv2.imwrite('hw2_2_Histogram_Equalization.jpg', new_img)
cv2.imshow('HyunBin_Sobel_img_x', Sobel_img_x)
cv2.imwrite('hw2_2_Sobel_img_x.jpg', Sobel_img_x)
cv2.imshow('HyunBin_Sobel_img_y', Sobel_img_y)
cv2.imwrite('hw2_2_Sobel_img_y.jpg', Sobel_img_y)
cv2.imshow('HyunBin_Sobel_img_out', Sobel_img_out)
cv2.imwrite('hw2_2_Sobel_img_out.jpg', Sobel_img_out)
cv2.waitKey(0)
cv2.destroyAllWindows()

