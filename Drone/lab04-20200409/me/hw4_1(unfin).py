import numpy as np 
import cv2
import pathlib

cols = 8
rows = 6

# termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = np.zeros(((cols - 1) * (rows - 1), 3), np.float32)
objp[:, :2] = np.mgrid[0:(cols - 1), 0:(rows - 1)].T.reshape(-1, 2)
 
# Arrays to store object points and image points from all the images.
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.

camera_number = 1 #device
									   #DirectShow (via videoInput)
cap = cv2.VideoCapture(camera_number + cv2.CAP_DSHOW)

'''	
this picks the LARGEST image possible
cap.set( cv2.CAP_PROP_FRAME_HEIGHT, 10000 )
cap.set( cv2.CAP_PROP_FRAME_WIDTH, 10000 )
'''
photo_taken_path = 'photo_taken'
pathlib.Path(photo_taken_path).mkdir(parents=True, exist_ok=True) 

detected_corner_path = 'detected_corner'
pathlib.Path(detected_corner_path).mkdir(parents=True, exist_ok=True)

found = 0

while True:
    if (found == 4): 
        break
	else:
    ret, frame = cap.read()
    #ret is True if read() successed
    if not ret:
         continue
    gray = cv2.cvtColor(frame.copy(), cv2.COLOR_BGR2GRAY)
    height, width = gray.shape
    # Find the chess board corners
    ret, corners = cv2.findChessboardCorners(gray, ((cols - 1), (rows - 1)), None)

    # If found, add object points, image points (after refining them)
    if ret == True:
        objpoints.append(objp)

        corners2 = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
        imgpoints.append(corners2)

        # Draw and display the corners
        frame = cv2.drawChessboardCorners(frame, ((cols - 1), (rows - 1)), corners2,ret)
        retval, cameraMatrix, distCoeffs, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, height * width, None)

        cv2.imshow('img', img)
        f = cv2.FileStorage(filename, cv2.FILE_STORAGE_WRITE)
        f.write("intrinsic", mtx)
        f.write("distortion", dist)
        f.release()
    k = cv2.waitKey(33)
    # press q to quit.
    if k == ord('q'):
       break

