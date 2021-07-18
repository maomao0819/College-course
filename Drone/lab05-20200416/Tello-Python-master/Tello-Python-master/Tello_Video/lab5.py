import tello
import cv2
from tello_control_ui import TelloUI
import time
import numpy as np
import pathlib
import glob
import os

def main():
	drone = tello.Tello('', 8889)

	time.sleep(5)

	# termination criteria
	criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

	row = 6
	col = 8
	# prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
	objp = np.zeros(((col - 1) * (row - 1), 3), np.float32)
													#row unknown, column 2
	objp[:,:2] = np.mgrid[0:(col - 1), 0:(row - 1)].T.reshape(-1, 2)

	# Arrays to store object points and image points from all the images.
	objpoints = [] 
	# 3d point in real world space
	# a vector of vectors of calibration pattern points in the calibration pattern coordinate space
	imgpoints = [] 
	# 2d points in image plane.
	# a vector of vectors of the projections of calibration pattern points

	photo_taken_path = 'photo_taken'
	detected_corner_path = 'detected_corner'

	ispathexist = False
	if os.path.exists(photo_taken_path):
		ispathexist = True

	found = 0
	if (ispathexist == False): 
		cap = drone.read()
		pathlib.Path(photo_taken_path).mkdir()
		pathlib.Path(detected_corner_path).mkdir()


	while (ispathexist == False): 
		if (found == 50): 
			ispathexist = True
			break
		else:
			key = cv2.waitKey(1) & 0xFF
			frame = drone.read()
			# "Ret" will obtain return value from getting the camera frame, either true of false.
			# "ret" is a boolean variable that returns true if the frame is available.
			# "Frame" will get the next frame in the camera (via "cap"). 
			# frame is an image array vector captured based on the default frames per second defined explicitly or implicitly
			cv2.imshow('frame', frame)
			# will display a frame for 30 ms, after which display will be automatically closed
			cv2.waitKey(30)
			img = frame.copy()
			gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
			ret, corners = cv2.findChessboardCorners(gray, ((col - 1), (row - 1)), None)
			if ret == True:
				objpoints.append(objp)   # Certainly, every loop objp is the same, in 3D.
				corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
				imgpoints.append(corners2)
				# Draw and display the corners
				img = cv2.drawChessboardCorners(img, ((col - 1), (row - 1)), corners2, ret)
				found += 1
				#cv2.imshow('img', img)
				cv2.waitKey(500)

				ogn_image_name = photo_taken_path + '/photo_taken' + str(found) +'.png'
				cv2.imwrite(ogn_image_name, frame)

				cal_image_name = detected_corner_path + '/calibresult' + str(found) + '.png'
				cv2.imwrite(cal_image_name, img)
				if key!= -1:
				drone.keyboard(key)
			if key!= -1:
				drone.keyboard(key)
		'''
		if key == ord('q'):
			ispathexist = True
			break
		'''


	#path = os.getcwd()  #current path
	num_files_rec = 0
	for root, dirs, files in os.walk(photo_taken_path): 
		for each in files:
			num_files_rec += 1

	found = 1


	while (num_files_rec): 
		if (found == num_files_rec): break
		else:
			key = cv2.waitKey(1) & 0xFF
			frame = cv2.imread(photo_taken_path + '/photo_taken' + str(found) + '.png')
			print(photo_taken_path + '/photo_taken' + str(found) + '.png')
			# "Ret" will obtain return value from getting the camera frame, either true of false.
			# "ret" is a boolean variable that returns true if the frame is available.
			# "Frame" will get the next frame in the camera (via "cap"). 
			# frame is an image array vector captured based on the default frames per second defined explicitly or implicitly
			# will display a frame for 30 ms, after which display will be automatically closed
			img = frame.copy()
			gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
			ret, corners = cv2.findChessboardCorners(gray, ((col - 1), (row - 1)), None)
			if ret == True:
				objpoints.append(objp)   # Certainly, every loop objp is the same, in 3D.
				corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
				imgpoints.append(corners2)
				# Draw and display the corners
				img = cv2.drawChessboardCorners(img, ((col - 1), (row - 1)), corners2, ret)
				found += 1
				'''
				ogn_image_name = photo_taken_path + '/photo_taken' + str(found) +'.png'
				cv2.imwrite(ogn_image_name, frame)

				cal_image_name = detected_corner_path + '/calibresult' + str(found) + '.png'
				cv2.imwrite(cal_image_name, img)
				'''
				if key!= -1:
				drone.keyboard(key)
		if key!= -1:
			drone.keyboard(key)
		'''
		if key == ord('q'):
			ispathexist = True
			break
		'''

	print("Number of images used for calibration: ", found)
	#cv2.destroyAllWindows()
	#                                                                             size                                    
	ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
	# mtx: floating-point camera matrix
	# dist: distortion coefficients
	# rvecs: rotation vectors
	# tvecs: translation vectors

	dictionary = cv2.aruco.Dictionary_get(cv2.aruco.DICT_6X6_250)
	parameters = cv2.aruco.DetectorParameters_create()
	frame = drone.read()

	while(1):
		frame = drone.read() 
		#frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

		markerCorners, markerIds, rejectedCandidates = cv2.aruco.detectMarkers(frame, dictionary, parameters = parameters)
		# dictionary: indicates the type of markers that will be searched
		# markerCorners: vector of detected marker corners. For each marker, its four corners are provided. For N detected markers, the dimensions of this array is Nx4. The order of the corners is clockwise.
		# markerIds: vector of identifiers of the detected markers. The identifier is of type int. For N detected markers, the size of ids is also N. The identifiers have the same order than the markers in the imgPoints array.
		# rejectedCandidates: contains the imgPoints of those squares whose inner code has not a correct codification. Useful for debugging purposes.
		frame =  cv2.aruco.drawDetectedMarkers(frame, markerCorners, markerIds)
		# markerIds: vector of identifiers for markers in markersCorners
		if key!= -1:
			drone.keyboard(key)
		if(markerIds == 1):
			#                                                                      markerLength
			rvec, tvec, _objPoints = cv2.aruco.estimatePoseSingleMarkers(markerCorners, 14, mtx, dist) 
			# rvecs = rotation vectors        # tvecs = translation vectors, Each element in tvecs corresponds to the specific marker in imgPoints.
			# _objPoints: array of object points of all the marker corners
			#                                                      length
			frame = cv2.aruco.drawAxis(frame, mtx, dist, rvec, tvec, 1)
			# X Y Z 's translation vector
			XYZ_pose = "x:%.2f y:%.2f z:%.2f"%(tvec[0][0][0], tvec[0][0][1], tvec[0][0][2]) 
			
			x_loc = 0
			y_loc = 0
			for i in range(4):
				x_loc += markerCorners[0][0][i][0]
				y_loc += markerCorners[0][0][i][1]
			x_loc = int(x_loc / 4)
			y_loc = int(y_loc / 4)
			
			# cv2.putText(image, text, coordinate, font_style, size, color, line_width, line_type)
			cv2.putText(frame, XYZ_pose, (x_loc + 10, y_loc + 10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 255), 2, cv2.LINE_AA)
			if key!= -1:
				drone.keyboard(key)

		cv2.imshow("frame",frame)
		key = cv2.waitKey(1)

		if key!= -1:
			drone.keyboard(key)

	# release camera
	cap.release()

	# close all the OpenCV window
	cv2.destroyAllWindows()


if __name__ == "__main__":
	main()