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
			c = 1
			rvec, tvec, _objPoints = cv2.aruco.estimatePoseSingleMarkers(markerCorners, 10.7, mtx, dist) 
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
			#cv2.putText(frame,str(zp) ,(100,100), cv2.FONT_HERSHEY_SIMPLEX,0.8, (0, 255, 255), 2, cv2.LINE_AA)

			if(markerIds[dis_index][0] == 1):
				if zp > 100:
					drone.rotate_cw(zp - 90)
				elif zp < 80:
					drone.rotate_ccw(90 - zp)
				#time.sleep(0.7)
				if(tvec[dis_index][0][2] > 500):
					drone.move_forward(4)
				elif(tvec[dis_index][0][2] <= 500 and tvec[dis_index][0][2] > 200):
					drone.move_forward(1)
				elif(tvec[dis_index][0][2] <= 200 and tvec[dis_index][0][2] >= 110):
					drone.move_forward(0.4)
				elif(tvec[dis_index][0][2] < 110 and tvec[dis_index][0][2] > 60):
					drone.move_forward(0.2)
				#time.sleep(0.7)
			elif(markerIds[dis_index][0] == 11):
				if(tvec[0][0][2] < 80):
					drone.rotate_cw(80)
				elif zp > 100:
					drone.rotate_ccw(90-zp)
				elif zp < 60:
					drone.rotate_cw(zp-90)
				elif(tvec[dis_index][0][0] > 7):
					drone.move_right(0.2)
				elif(tvec[dis_index][0][0] < -7):
					drone.move_left(0.2)
				elif(tvec[dis_index][0][2] > 500):
					drone.move_forward(4)
				elif(tvec[dis_index][0][2] <= 500 and tvec[dis_index][0][2] > 200):
					drone.move_forward(1)
				elif(tvec[dis_index][0][2] <= 200 and tvec[dis_index][0][2] >= 110):
					drone.move_forward(0.4)
				elif(tvec[dis_index][0][2] < 110 and tvec[dis_index][0][2] > 75):
					drone.move_forward(0.2)
			elif(markerIds[dis_index][0] == 4):
				if(tvec[dis_index][0][0] > 7):
					drone.move_right(0.2)
				elif(tvec[dis_index][0][0] < -7):
					drone.move_left(0.2)
				elif(tvec[dis_index][0][2] > 500):
					drone.move_forward(4)
				elif(tvec[dis_index][0][2] <= 500 and tvec[dis_index][0][2] >= 300):
					drone.move_forward(2)
				elif(tvec[dis_index][0][2] < 300 and tvec[dis_index][0][2] >= 100):
					drone.move_forward(0.5)
				elif(tvec[dis_index][0][2] < 100 and tvec[dis_index][0][2] > 50):
					drone.move_forward(0.2)
				else:
					drone.land()
		cv2.imshow('frame', frame)
		cv2.waitKey(1)

if __name__ == "__main__":
	main()
