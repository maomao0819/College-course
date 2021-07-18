# credit: https://silverwind1982.pixnet.net/blog/post/153218861-pinhole-camera%3A-%E7%9B%B8%E6%A9%9F%E6%A0%A1%E6%AD%A3-%28camera-calibration%29
# credit: https://nikatsanka.github.io/camera-calibration-using-opencv-and-python.html
# credit: https://opencv-python-tutroals.readthedocs.io/en/latest/py_tutorials/py_calib3d/py_calibration/py_calibration.html

import numpy as np
import cv2
import pathlib
import glob

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
cap = cv2.VideoCapture(0)

photo_taken_path = 'photo_taken'
pathlib.Path(photo_taken_path).mkdir() #(parents = True, exist_ok = True)

detected_corner_path = 'detected_corner'
pathlib.Path(detected_corner_path).mkdir() #(parents = True, exist_ok = True)

found = 0
while (True): 
    if (found == 10): break
    else:
        key = cv2.waitKey(1) & 0xFF
        ret, frame = cap.read()
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
            cv2.imshow('img', img)
            cv2.waitKey(500)

            ogn_image_name = photo_taken_path + '/photo_taken' + str(found) +'.png'
            cv2.imwrite(ogn_image_name, frame)

            cal_image_name = detected_corner_path + '/calibresult' + str(found) + '.png'
            cv2.imwrite(cal_image_name, img)
    if key == ord('q'):
        break

print("Number of images used for calibration: ", found)
cv2.destroyAllWindows()
#                                                                             size                                    
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1], None, None)
# mtx: floating-point camera matrix
# dist: distortion coefficients
# rvecs: rotation vectors
# tvecs: translation vectors

cap = cv2.VideoCapture(0)
dictionary = cv2.aruco.Dictionary_get(cv2.aruco.DICT_6X6_250)
parameters = cv2.aruco.DetectorParameters_create()
ret, frame = cap.read()
while(ret == True):
    ret, frame = cap.read()      
    markerCorners, markerIds, rejectedCandidates = cv2.aruco.detectMarkers(frame, dictionary, parameters = parameters)
    # dictionary: indicates the type of markers that will be searched
    # markerCorners: vector of detected marker corners. For each marker, its four corners are provided. For N detected markers, the dimensions of this array is Nx4. The order of the corners is clockwise.
    # markerIds: vector of identifiers of the detected markers. The identifier is of type int. For N detected markers, the size of ids is also N. The identifiers have the same order than the markers in the imgPoints array.
    # rejectedCandidates: contains the imgPoints of those squares whose inner code has not a correct codification. Useful for debugging purposes.
    frame =  cv2.aruco.drawDetectedMarkers(frame, markerCorners, markerIds)
    # markerIds: vector of identifiers for markers in markersCorners
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

    cv2.imshow('frame', frame)
    key = cv2.waitKey(10)
    if key == ord('q'):
        break

# release camera
cap.release()

# close all the OpenCV window
cv2.destroyAllWindows()
# print(mtx)
# print(dist)
# not finished yet, encounter some problem.
# ----------------undistort()----------------

# undist_pic_path = 'undist_pic'
# pathlib.Path(undist_pic_path).mkdir(parents=True, exist_ok=True) 

# images = glob.glob(r'photo_taken/*.png')
# for i in images:
#     undistimg = cv2.imread(i)
#     h, w = undistimg[:2]
#     newcameramtx, roi=cv2.getOptimalNewCameraMatrix(mtx,dist,(w,h),1,(w,h))
#     # undistort
#     mapx,mapy = cv2.initUndistortRectifyMap(mtx,dist,None,newcameramtx,(w,h),5)
#     dst = cv2.remap(img,mapx,mapy,cv2.INTER_LINEAR)

#     # crop the image
#     x,y,w,h = roi
#     dst = dst[y:y+h, x:x+w]
#     undist_image_name = undist_pic_path + '/undist_image' + str(i) + '.png'
#     cv2.imwrite(undist_image, dst)
#     # cv2.imwrite('calibresult.png',dst)