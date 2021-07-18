import tello
import numpy as np
import cv2
from tello_control_ui import TelloUI
import time
import math
import glob

def main():

	f = cv2.FileStorage("rslt.xml", cv2.FILE_STORAGE_READ)
	mtx = f.getNode("instric").mat()
	dist = f.getNode("distortion").mat()
	
	print(mtx, dist)

	drone = tello.Tello('', 8889)

	time.sleep(5)

	dictionary = cv2.aruco.Dictionary_get(cv2.aruco.DICT_6X6_250)
	parameters = cv2.aruco.DetectorParameters_create()
	
	while 1:
		distance = []
		frame = drone.read()
		frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)
		# cv2.imshow(frame)
		markerCorners, markerIds, rejectedCandidates = cv2.aruco.detectMarkers(frame, dictionary, parameters=parameters)
		# print(markerIds)
		frame =  cv2.aruco.drawDetectedMarkers(frame,markerCorners, markerIds)
		key = cv2.waitKey(1)
		if key!= -1:
			drone.keyboard(key)
			
		# new one
		c = 0
		if(len(str(markerIds))!=4):
			print("123")
			c = 1
			rvec, tvec, _objPoints = cv2.aruco.estimatePoseSingleMarkers(markerCorners, 9.5, mtx, dist) 
			for i in range(len(markerIds)):
				distance.append(tvec[i][0][2])

		if (c!=0):
			dis_index = distance.index(min(distance))
			print(distance[dis_index], dis_index)

		if(c==1):
			frame = cv2.aruco.drawAxis(frame, mtx, dist ,rvec[dis_index], tvec[dis_index], 4)
			XYZ_pose = "x:%.2f y:%.2f z:%.2f"%(tvec[dis_index][0][0],tvec[dis_index][0][1],tvec[dis_index][0][2])

			x_loc = 0
			y_loc = 0
			for i in range(4):
				x_loc += markerCorners[dis_index][0][i][0]
				y_loc += markerCorners[dis_index][0][i][1]
			x_loc = int(x_loc/4)
			y_loc = int(y_loc/4)
			cv2.putText(frame,XYZ_pose,(x_loc+10,y_loc+10),cv2.FONT_HERSHEY_SIMPLEX,0.8, (0, 255, 255), 2, cv2.LINE_AA)

			R = cv2.Rodrigues(rvec[dis_index])
			R = R[0]
			Z = np.array([0,0,1])
			Z = R.dot(Z)
			thea = math.atan2(Z[2],Z[0])

			zp = -np.rad2deg(thea)
			cv2.putText(frame,str(zp) ,(100,100), cv2.FONT_HERSHEY_SIMPLEX,0.8, (0, 255, 255), 2, cv2.LINE_AA)

			if(markerIds[dis_index][0] == 1):
				if zp > 0:
					drone.rotate_ccw(90-zp)
				else:
					drone.rotate_cw(zp-90)
				if(tvec[0][0][2] > 100):
					drone.move_forward(0.2)
			elif(markerIds[dis_index][0]==4):
				if(tvec[dis_index][0][0] > 5):
					drone.move_right(0.2)
				elif(tvec[dis_index][0][0] < -5):
					drone.move_left(0.2)
				elif(tvec[dis_index][0][2] > 50):
					drone.move_forward(0.2)
				else:
					drone.land()

		# old one
		# print("work here?")
		# if(markerIds==1):
		# 	rvec, tvec, _objPoints = cv2.aruco.estimatePoseSingleMarkers(markerCorners, 9.5, mtx, dist) 
		# 	frame = cv2.aruco.drawAxis(frame, mtx, dist ,rvec, tvec, 4)

		# 	XYZ_pose = "x:%.2f y:%.2f z:%.2f"%(tvec[0][0][0],tvec[0][0][1],tvec[0][0][2])

		# 	x_loc = 0
		# 	y_loc = 0
		# 	for i in range(4):
		# 		x_loc += markerCorners[0][0][i][0]
		# 		y_loc += markerCorners[0][0][i][1]
		# 	x_loc = int(x_loc/4)
		# 	y_loc = int(y_loc/4)
		# 	cv2.putText(frame,XYZ_pose,(x_loc+10,y_loc+10),cv2.FONT_HERSHEY_SIMPLEX,0.8, (0, 255, 255), 2, cv2.LINE_AA)

		# 	R = cv2.Rodrigues(rvec)
		# 	R = R[0]
		# 	Z = np.array([0,0,1])
		# 	Z = R.dot(Z)
		# 	thea = math.atan2(Z[2],Z[0])

		# 	zp = -np.rad2deg(thea)
		# 	cv2.putText(frame,str(zp) ,(100,100), cv2.FONT_HERSHEY_SIMPLEX,0.8, (0, 255, 255), 2, cv2.LINE_AA)
		# 	#zp = np.rad2deg(z)
		# 	# if zp > 10:
		# 	# 	drone.rotate_ccw(5)
		# 	# elif zp-90 > 10:
		# 		# drone.rotate_cw(5)
		# 	if zp > 0:
		# 		drone.rotate_ccw(90-zp)
		# 	else:
		# 		drone.rotate_cw(zp-90)

		# 	if(tvec[0][0][2] > 100):
		# 		drone.move_forward(0.2)
 
		cv2.imshow('frame', frame)
		cv2.waitKey(1)

if __name__ == "__main__":
    main()
