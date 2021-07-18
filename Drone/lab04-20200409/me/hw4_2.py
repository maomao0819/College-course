import cv2
import numpy as np

img = cv2.imread('warp.jpg')
height, weidth, channal = img.shape

camera_number = 1 #device
									   #DirectShow (via videoInput)
cap = cv2.VideoCapture(camera_number + cv2.CAP_DSHOW)

ret, frame = cap.read()
h, w = frame.shape[:2]

'''
rows = 8
cols = 6
Side_length = 80
'''
# pts1 = my camera, pts2 = given picture
pts1 = np.float32([[0, 0], [w, 0], [w, h], [0, h]])
pts2 = np.float32([[194, 115], [451, 53], [442, 275], [179, 272]])

M = cv2.getPerspectiveTransform(pts1, pts2)
while(True):
	ret, frame = cap.read()
	if not ret:
		continue
	if ret == True:
		res = cv2.warpPerspective(frame, M, (weidth, height))
		cv2.fillConvexPoly(img, pts2.astype(np.int), (0, 0, 0))
		cv2.imshow('wrap', img + res)
	k = cv2.waitKey(3)
	# press q to quit.
	if k == ord('q'):
		break