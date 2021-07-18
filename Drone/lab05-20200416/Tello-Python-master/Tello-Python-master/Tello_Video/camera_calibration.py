# author: ian cheng
# e-mail: iancheng0321@gmail.com
import tello
import numpy as np
import cv2
from tello_control_ui import TelloUI
import time
import glob

def main():
	# using drone
	# drone = tello.Tello('', 8889)
	# time.sleep(5)

	# # using webcam
	# # cap = cv2.VideoCapture(0)

	# print("press any key to take pic, q to quit")

	# n = 18
	# while (1):
	# 	# drone
	# 	frame = drone.read()
	# 	frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
	# 	# web cam
	# 	# ret, frame = cap.read()
	# 	cv2.waitKey(10)

	# 	cv2.imshow("frame",frame)
	# 	key = cv2.waitKey(10)
		
	# 	if key == ord('q'):
	# 		break
	# 	if key != -1:
	# 		print(key)
	# 		img_name = 'pic' + "%02d"%n + '.png'
	# 		print(img_name)
	# 		cv2.imwrite(img_name,frame)
	# 		n = n + 1

	# # cap.release()
	# cv2.destroyAllWindows()
	# print("check the taken photo manually, can del unfocus one now")


	criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
	
	# objp = np.zeros((7*5,3), np.float32)
	objp = np.zeros((7*7,3), np.float32)	
	objp[:,:2] = np.mgrid[0:7,0:7].T.reshape(-1,2)	
	# objp[:,:2] = np.mgrid[0:7,0:5].T.reshape(-1,2)

	objpoints = [] # 3d point in real world space
	imgpoints = [] # 2d points in image plane.
	
	images = glob.glob('*.png')

	for fname in images:
		print(fname)
		img = cv2.imread(fname)
		img = cv2.imread(fname)
		gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		ret, corners = cv2.findChessboardCorners(gray, (7,7), None)
		if ret == True:
			objpoints.append(objp)

			corners2 = cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
			imgpoints.append(corners2)

			# Draw and display the corners
			img = cv2.drawChessboardCorners(img, (7,7), corners2,ret)
			cv2.imshow('img',img)
			cv2.waitKey(500)


	cv2.destroyAllWindows()

	ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1],None,None)

	f = cv2.FileStorage("rslt.xml",cv2.FILE_STORAGE_WRITE)
	f.write("instric", mtx)
	f.write("distortion",dist)
	f.write("rvecs",rvecs)
	f.release()

if __name__ == "__main__":
    main()
