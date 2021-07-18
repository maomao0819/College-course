import numpy as np
import cv2

img = cv2.imread('IU.png')
new_img = img.copy()
height, weidth, channal = new_img.shape
h = int(0.7 * height)
w = int(0.7 * weidth)
c = channal
#Bilinear Interpolation

dim = (w, h)
Bilinear_image = cv2.resize(new_img, dim, interpolation = cv2.INTER_LINEAR)
'''
def Bilinear_x(num1, num2, image):
	return (num1 - int(num1)) * image[int(num1) + 1][int(num2)] + (int(num1) + 1 - num1) * image[int(num1)][int(num2)]
def Bilinear_y(num, image1, image2):
	return (num - int(num)) * image2 + (int(num) + 1 - num) * image1
Bilinear_image = np.zeros((h, w, c), np.uint8)
for i in range(h):
	for j in range(w):

		Bilinear_image_h = i / 0.7
		Bilinear_image_w = j / 0.7
		#Q = (Bilinear_image_h - int(Bilinear_image_h)) * new_img[int(Bilinear_image_h) + 1][int(Bilinear_image_w)] + (int(Bilinear_image_h) + 1 - Bilinear_image_h) * new_img[int(Bilinear_image_h)][int(Bilinear_image_w)]
		img1 = Bilinear_x(Bilinear_image_h, int(Bilinear_image_w), new_img)
		img2 = Bilinear_x(Bilinear_image_h, int(Bilinear_image_w) + 1, new_img)
		Bilinear_image[i, j] = Bilinear_y(Bilinear_image_w, img1, img2)
'''
		
#Bilinear_image = Bilinear_image.astype(np.uint8)
cv2.imshow('IU', Bilinear_image)
cv2.imwrite('hw1_3.png', Bilinear_image)
cv2.waitKey(0)
cv2.destroyAllWindows()