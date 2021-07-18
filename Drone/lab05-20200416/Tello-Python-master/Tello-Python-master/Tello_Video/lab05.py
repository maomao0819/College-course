import tello
import numpy as np
import cv2
from tello_control_ui import TelloUI
import time
import math
import glob

def main():

	# f = cv2.FileStorage("rslt.xml", cv2.FILE_STORAGE_READ)
	# mtx = f.getNode("intrinsic").mat()
	# dist = f.getNode("distortion").mat()
	# rvec = f.getNode("rvec").mat()
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
			# cv2.waitKey(500)


	cv2.destroyAllWindows()

	ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1],None,None)

	drone = tello.Tello('', 8889)

	time.sleep(5)

	# cap = drone.read()
	# cap = cv2.cvtColor(cap, cv2.COLOR_RGB2BGR)

	# cv2.imshow("frame",cap)
	dictionary = cv2.aruco.Dictionary_get(cv2.aruco.DICT_6X6_250)
	parameters = cv2.aruco.DetectorParameters_create()
	# ret, frame = cap.read()
	# cap = cv2.VideoCapture(1)
	while 1:
		frame = drone.read()
		frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

		# ret, frame = cap.read()
		# frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
		markerCorners, markerIds, rejectedCandidates = cv2.aruco.detectMarkers(frame, dictionary, parameters=parameters)
		# print(markerIds)
		frame =  cv2.aruco.drawDetectedMarkers(frame,markerCorners, markerIds)
		key = cv2.waitKey(1)
		if key!= -1:
			drone.keyboard(key)
		c = 0
		
		# if markerIds != None:
		# 	for i in range(len(markerIds)):
		# 		print(i)

		# 		if(int(i) == 1):
		# 			c = 1
		# if markerIds != None:
		# 	for i in len(markerIds):
		# 		print(i[0])
		# 		if i[0] == 1:
		# 			c = 1
		if len(str(markerIds)) == 4:
			continue
		else:
			c = 1
			rvec, tvec, _objPoints = cv2.aruco.estimatePoseSingleMarkers(markerCorners, 9.5, mtx, dist) 
			for i in range(len(markerIds)):
				distance.append(tvec[i][0][2])
		dis_index = distance.index(min(distance))
		print(c)
		
		if(c==1):
			rvec,tvec, _objPoints = cv2.aruco.estimatePoseSingleMarkers(markerCorners, 12.7, mtx, dist) 
			frame = cv2.aruco.drawAxis(frame, mtx, dist ,rvec, tvec, 4)
			XYZ_pose = "x:%.2f y:%.2f z:%.2f"%(tvec[0][0][0],tvec[0][0][1],tvec[0][0][2])

			x_loc = 0
			y_loc = 0
			for i in range(4):
				x_loc += markerCorners[0][0][i][0]
				y_loc += markerCorners[0][0][i][1]
			x_loc = int(x_loc/4)
			y_loc = int(y_loc/4)
			cv2.putText(frame,XYZ_pose,(x_loc+10,y_loc+10),cv2.FONT_HERSHEY_SIMPLEX,0.8, (0, 255, 255), 2, cv2.LINE_AA)



			R = cv2.Rodrigues(rvec)
			R = R[0]
			Z = np.array([0,0,1])
			Z = R.dot(Z)
			thea = math.atan2(Z[2],Z[0])

			zp = -np.rad2deg(thea)
			cv2.putText(frame,str(zp) ,(100,100), cv2.FONT_HERSHEY_SIMPLEX,0.8, (0, 255, 255), 2, cv2.LINE_AA)
			#zp = np.rad2deg(z)
			# if zp > 10:
			# 	drone.rotate_ccw(5)
			# elif zp-90 > 10:
			# 	# drone.rotate_cw(5)
			# if zp > 0:
			# 	drone.rotate_ccw(90-zp)
			# else:
			# 	drone.rotate_cw(zp-90)

			# if(tvec[0][0][2] > 100):
			# 	drone.move_forward(0.2)
 
		cv2.imshow('frame', frame)
		cv2.waitKey(1)

if __name__ == "__main__":
    main()
