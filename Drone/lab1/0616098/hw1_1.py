import numpy as np
import cv2

img = cv2.imread('kobe.jpg')

#new_img = np.round(img.copy().mean(axis = 2).reshape((img.shape[0], img.shape[1], 1))).astype(np.uint8)
#new_img = np.round(img.copy().mean(axis = 2, keepdims = True)).astype(np.uint8)
new_img = cv2.cvtColor(img.copy(), cv2.COLOR_BGR2GRAY)
'''
new_img = img.copy()
height, weidth, channal = new_img.shape
for h in range(height):
	for w in range(weidth):
		color = new_img[h, w]
		gray_i = int((color[0] / 3 + color[1] / 3 + color[2] / 3))
		new_img[h, w] = gray_i
'''
cv2.imshow('kobe', new_img)
cv2.imwrite('hw1_1.jpg', new_img)
cv2.waitKey(0)
cv2.destroyAllWindows()
