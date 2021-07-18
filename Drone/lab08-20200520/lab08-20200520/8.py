import numpy as np
import cv2
 
face_cascade = cv2.CascadeClassifier('D:\opencv\sources\data\haarcascades/haarcascade_frontalface_default.xml')
hog = cv2.HOGDescriptor()
hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())

f = cv2.FileStorage("rslt.xml", cv2.FILE_STORAGE_READ)
mtx = f.getNode("instric").mat()
dist = f.getNode("distortion").mat()


##73 == shoulder length      180 == height
s_l = 50
height = 176
objp = [[0,0,0],[(s_l*1.05),0,0],[0,(height*1.05),0],[(s_l*1.05),(height*1.05),0]]
objp = np.array(objp,dtype=np.float32)

##73 == shoulder length      180 == height
objp_face = [[0,0,0],[(20*1.25),0,0],[0,(25*1.25),0],[(20*1.25),(25*1.25),0]]
objp_face = np.array(objp,dtype=np.float32)


cap = cv2.VideoCapture(0)
ret, frame = cap.read()
while ret == True:
    ret, frame = cap.read()
    img = frame.copy()
    imgpoint = []
    rects, weights = hog.detectMultiScale(img, winStride = (4, 4), scale = 1.05, useMeanshiftGrouping = False)	
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray,scaleFactor=1.05,minNeighbors=3,minSize = (5, 5))
    
    if (len(rects) != 0 and len(faces) != 0):
        for (faces_x, faces_y, faces_w, faces_h) in faces:
            for (rects_x, rects_y, rects_w, rects_h) in rects:
                if(faces_x > rects_x and faces_y > rects_y and (faces_x + faces_w) < (rects_x + rects_w) and (faces_y + faces_h) < (rects_y + rects_h)):
                    #imgpoint = [np.array([rects_x,rects_y], dtype=np.float32),np.array([rects_x + rects_w, rects_y], dtype=np.float32), np.array([rects_x,rects_y + rects_h], dtype=np.float32) , np.array([rects_x+rects_w, rects_y + rects_h], dtype=np.float32)]
                    #imgpoint.append(kkk)
                    #imgpoint = np.array(imgpoint)
                    imgpoint = np.array([[rects_x,rects_y],[rects_x + rects_w, rects_y], [rects_x,rects_y + rects_h], [rects_x+rects_w, rects_y + rects_h]], dtype=np.float32)
                    img = cv2.rectangle(img, (faces_x, faces_y), (faces_x + faces_w, faces_y + faces_h), (0, 255, 0), 2)
                    img = cv2.rectangle(img, (rects_x, rects_y), (rects_x + rects_w, rects_y + rects_h), (0, 255, 255), 2)
                    
                    ret, rvecs, tvecs = cv2.solvePnP(objp, imgpoint, mtx, dist)
                    cv2.putText(img, str(tvecs[2][0]), (rects_x+rects_w-10, rects_y + rects_h-10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 255), 2, cv2.LINE_AA)
                    
                    imgpoint_face = np.array([[faces_x,faces_y],[faces_x + faces_w, faces_y], [faces_x,faces_y + faces_h], [faces_x+faces_w, faces_y + faces_h]], dtype=np.float32)
                    ret, rvecs2, tvecs2 = cv2.solvePnP(objp_face, imgpoint_face, mtx, dist)
                    cv2.putText(img, str(tvecs[2][0]*1.0795), (faces_x+faces_w-5, faces_y +faces_h-5), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2, cv2.LINE_AA)
                    #print(tvecs[2][0])
    cv2.imshow('556622', img)
    cv2.waitKey(10)
    
    
cap.release()
cv2.destroyAllWindows()


#objp = np.zeros((4,3), np.float32),, [rects_x,rects_y + rects_h], [rects_x+rects_w, rects_y + rects_h]
#imgpoint.append(np.array([[rects_x,rects_y],[rects_x + rects_w, rects_y], [rects_x,rects_y + rects_h], [rects_x+rects_w, rects_y + rects_h]], dtype=np.float32))
#imgpoint = [[rects_x,rects_y],[rects_x + rects_w, rects_y], [rects_x,rects_y + rects_h], [rects_x+rects_w, rects_y + rects_h]]

