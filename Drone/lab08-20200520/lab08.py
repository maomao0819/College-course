import numpy as np
import cv2
import math
import imutils

def main():
	cap = cv2.VideoCapture(1 + cv2.CAP_DSHOW)
	ret = True
	while ret:
		# initialize the HOG descriptor/person detector
		hog = cv2.HOGDescriptor()
		hog.setSVMDetector(cv2.HOGDescriptor_getDefaultPeopleDetector())
		# getDefaultPeopleDetector() : coefficients of the classifier trained for people detection (for default window size).

		# load the image and resize it to [faster, more accurate]
		# cv2.CAP_DSHOW
		ret, frame = cap.read()
		img = frame.copy()
		img = imutils.resize(img, width = 1000)

		# https://www.programcreek.com/python/example/84776/cv2.HOGDescriptor
		
		# detect people in the image 
										# 輸入圖, 在圖上抓取特徵時窗口的移動大小, 抓取不同scale(越小就要做越多次)
		rects, weights = hog.detectMultiScale(img, winStride = (4, 4), scale = 1.05, useMeanshiftGrouping = False)
			# https://docs.opencv.org/3.4/d5/d33/structcv_1_1HOGDescriptor.html#a91e56a2c317392e50fbaa2f5dc78d30b
			# img : Matrix of the type CV_8U or CV_8UC3 containing an image where objects are detected.
			# foundLocations : Vector of rectangles where each rectangle contains the detected object.
			# foundWeights : Vector that will contain confidence values for each detected object.
			# hitThreshold : Threshold for the distance between features and SVM classifying plane. Usually it is 0 and should be specified in the detector coefficients 
			#				 (as the last free coefficient). But if the free coefficient is omitted (which is allowed), you can specify it manually here.
			# winStride : Window stride. It must be a multiple of block stride.
			# scale : Coefficient of the detection window increase.
			# finalThreshold : Final threshold
			# useMeanshiftGrouping : indicates grouping algorithm
		
		face_cascade = cv2.CascadeClassifier('D:\opencv\sources\data\haarcascades/haarcascade_frontalface_default.xml')

											# 輸入圖, 抓取不同scale, 該區域附近被認為是臉的次數, 物體最小限制, 物體最大限制
		faces_rect = face_cascade.detectMultiScale(img, scaleFactor = 1.05, minNeighbors = 3, minSize = (3, 3))
			# https://docs.opencv.org/2.4/modules/objdetect/doc/cascade_classification.html
			# cascade – Haar classifier cascade (OpenCV 1.x API only). It can be loaded from XML or YAML file using Load(). 
			# 			When the cascade is not needed anymore, release it using cvReleaseHaarClassifierCascade(&cascade).
			# image – Matrix of the type CV_8U containing an image where objects are detected.
			# objects – Vector of rectangles where each rectangle contains the detected object.
			# scaleFactor – Parameter specifying how much the image size is reduced at each image scale.
			# minNeighbors – Parameter specifying how many neighbors each candidate rectangle should have to retain it.
			# flags – Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects. It is not used for a new cascade.
			# minSize – Minimum possible object size. Objects smaller than that are ignored.
			# maxSize – Maximum possible object size. Objects larger than that are ignored.


			# draw bounding boxes
		for (x, y, w, h) in rects:
			# draw bounding boxes
				# cv2.rectangle(image, start_point, end_point, color, thickness)
			img = cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 255), 2)
		for (x, y, w, h) in faces_rect:
			# draw bounding boxes
				# cv2.rectangle(image, start_point, end_point, color, thickness)
			img = cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)	
			cv2.imshow('img', img)
		k = cv2.waitKey(1)
		if k == ord('q'):
			break

	cap.release()
	cv2.destroyAllWindows()
	
	# while 1:
	# 	cap = cv2.VideoCapture(1)
	# 	ret, frame = cap.read()
	# 	cv2.imshow('img', frame)
	# 	cv2.waitKey(10)
	# 	cap.release()
	# 	cv2.destroyAllWindows()

if __name__ == "__main__":
	main()