import numpy as np
import cv2
import pathlib
import glob
import cv2.aruco
# termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = np.zeros((7*5,3), np.float32)
objp[:,:2] = np.mgrid[0:7,0:5].T.reshape(-1,2)

# Arrays to store object points and image points from all the images.
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.

cap = cv2.VideoCapture(0)
'''
photo_taken_path = 'photo_taken'
pathlib.Path(photo_taken_path).mkdir(parents=True, exist_ok=True) 

detected_corner_path = 'detected_corner'
pathlib.Path(detected_corner_path).mkdir(parents=True, exist_ok=True) 
'''
ret, frame = cap.read()
img = frame.copy()
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

found = 0
while (True): 
    if (found == 4): break
    else:
        ret, frame = cap.read()
        cv2.imshow('frame', frame)
        cv2.waitKey(10)
        img = frame.copy()
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        ret, corners = cv2.findChessboardCorners(gray, (7,5), None)
        if ret == True:
            objpoints.append(objp)   # Certainly, every loop objp is the same, in 3D.
            corners2 = cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
            imgpoints.append(corners2)
            # Draw and display the corners
            img = cv2.drawChessboardCorners(img, (7,5), corners2, ret)
            found += 1
            cv2.imshow('img', img)
            cv2.waitKey(500)
'''
            ogn_image_name = photo_taken_path + '/photo_taken' + str(found) +'.png'
            cv2.imwrite(ogn_image_name, frame)

            cal_image_name = detected_corner_path + '/calibresult' + str(found) + '.png'
            cv2.imwrite(cal_image_name, img)
'''

print("Number of images used for calibration: ", found)
cv2.destroyAllWindows()
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)

'''
ret = 0.6954929068364099
mtx = ([[497.94891819,   0.        , 393.55408939],
       [  0.        , 481.46932712, 270.3141224 ],
       [  0.        ,   0.        ,   1.        ]])
dist = ([[ 0.02623114, -4.05985381,  0.05360422,  0.05733983, 22.04210193]])
rvecs = [([[-0.06943715],
       [ 0.38275179],
       [ 1.39047902]]), ([[0.11864281],
       [0.24519174],
       [1.35139053]]), ([[-0.43559537],
       [-0.35991522],
       [-0.5810137 ]]), ([[-0.38712778],
       [-0.34771199],
       [-0.41897211]])]
tvecs = [([[-1.64690099],
       [-3.56704555],
       [19.12639461]]), ([[-0.46591034],
       [-4.79188762],
       [15.20396837]]), ([[-4.64378573],
       [-1.02227445],
       [14.86066185]]), ([[-3.97149831],
       [-0.99578404],
       [15.21159641]])]
'''
f = cv2.FileStorage("rslt.xml",cv2.FILE_STORAGE_WRITE)
f.write("intrinsic", mtx)
f.write("distortion",dist)
f.release()

# Load the predefined dictionary
dictionary = cv2.aruco.Dictionary_get(cv2.aruco.DICT_6X6_250)
# Initialize the detector parameters using default values
parameters = cv2.aruco.DetectorParameters_create()
# Detect the markers in the image
markerCorners, markerIds, rejectedCandidates = cv2.aruco.detectMarkers(frame, dictionary, parameters = parameters)
frame = cv2.aruco.drawDetectedMarkers(frame, markerCorners, markerIds)
#Pose estimation for single markers.
intrinsic = mtx
distortion = dist

rvec, tvec, _objPoints = cv2.aruco.estimatePoseSingleMarkers(markerCorners, 0.1, intrinsic, distortion)
frame = cv2.aruco.drawAxis(frame, intrinsic, distortion, rvec, tvec, 0.1)