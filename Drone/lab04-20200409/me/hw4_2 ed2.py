import cv2
import numpy as np
cap = cv2.VideoCapture(0)

img = cv2.imread('warp.jpg')
# cv2.imshow('wrap',img)
w, h = img.shape[:2]

# pts1 = my camera, pts2 = given picture
pts1 = np.float32([[0, 0], [640, 0], [0, 480], [640, 480]])
pts2 = np.float32([[194, 115], [451, 53], [179, 272], [442, 275]])
area = np.array([[194, 115], [451, 53], [442, 275], [179, 272]])
while(True):
	ret, frame = cap.read()
	cv2.waitKey(3)
	M = cv2.getPerspectiveTransform(pts1, pts2)
	res = cv2.warpPerspective(frame, M, (h, w))
	cv2.fillConvexPoly(img, area, (0, 0, 0))
	# cv2.imshow('wrap',img)
	# cv2.imshow('pic',res)
	# for y in range(w):
	# 	for x in range(h):
	# 		img[y][x] += res[y][x]
	img += res
	cv2.imshow('wrap',img)
	# cv2.waitKey(0)
	# cv2.destroyAllWindows()
