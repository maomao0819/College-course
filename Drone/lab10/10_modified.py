import tello
import numpy as np
from tello_control_ui import TelloUI
import math
import glob
import argparse
import time
import cv2
import os
# step1 = 0
def main():
	step1 = 0
	turn_ed = 0
	f = cv2.FileStorage("rslt.xml", cv2.FILE_STORAGE_READ)
	mtx = f.getNode("instric").mat()
	dist = f.getNode("distortion").mat()
	width = 19
	height = 25
	objp = [[0, 0, 0], [width, 0, 0], [0, height, 0], [width, height, 0]]
	objp = np.array(objp, dtype=np.float32)

	imgpoint = []

	# USAGE
	# python yolo.py --image images/baggage_claim.jpg --yolo yolo-coco

	# construct the argument parse and parse the arguments
	ap = argparse.ArgumentParser()
	ap.add_argument("-i", "--image", required=False,
		help="path to input image")
	ap.add_argument("-y", "--yolo", required=True,
		help="base path to YOLO directory")
	ap.add_argument("-c", "--confidence", type=float, default=0.5,
		help="minimum probability to filter weak detections")
	ap.add_argument("-t", "--threshold", type=float, default=0.3,
		help="threshold when applyong non-maxima suppression")
	args = vars(ap.parse_args())
	
	# load the COCO class labels our YOLO model was trained on
	labelsPath = os.path.sep.join([args["yolo"], "coco.names"])
	LABELS = open(labelsPath).read().strip().split("\n")

	# initialize a list of colors to represent each possible class label
	np.random.seed(42)
	COLORS = np.random.randint(0, 255, size=(len(LABELS), 3),
		dtype="uint8")

	# derive the paths to the YOLO weights and model configuration
	weightsPath = os.path.sep.join([args["yolo"], "yolov3.weights"])
	configPath = os.path.sep.join([args["yolo"], "yolov3.cfg"])

	# load our YOLO object detector trained on COCO dataset (80 classes)
	print("[INFO] loading YOLO from disk...")
	net = cv2.dnn.readNetFromDarknet(configPath, weightsPath)

	drone = tello.Tello('', 8889)

	time.sleep(5)

	dictionary = cv2.aruco.Dictionary_get(cv2.aruco.DICT_6X6_250)
	parameters = cv2.aruco.DetectorParameters_create()
	init = 1
	while 1:
		
		key = cv2.waitKey(1)
		if key!= -1:
			if key == ord('2'):
				drone.land()
				time.sleep(2)
			drone.keyboard(key)
		distance = []
		image = drone.read()
		image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
		markerCorners, markerIds, rejectedCandidates = cv2.aruco.detectMarkers(image, dictionary, parameters=parameters)
		# print(markerIds)
		frame =  cv2.aruco.drawDetectedMarkers(image, markerCorners, markerIds)
		(H, W) = image.shape[:2]
		# cv2.imshow(frame)
		ln = net.getLayerNames()
		# for i in net.getUnconnectedOutLayers():
			# ln = ln[i[0] - 1]
		ln = [ln[i[0] - 1] for i in net.getUnconnectedOutLayers()]	

		# construct a blob from the input image and then perform a forward
		# pass of the YOLO object detector, giving us our bounding boxes and
		# associated probabilities
		blob = cv2.dnn.blobFromImage(image, 1 / 255.0, (416, 416), swapRB=True, crop=False)
		net.setInput(blob)
		start = time.time()
		layerOutputs = net.forward(ln)
		end = time.time()

		# show timing information on YOLO
		print("[INFO] YOLO took {:.6f} seconds".format(end - start))

		# initialize our lists of detected bounding boxes, confidences, and
		# class IDs, respectively
		boxes = []
		confidences = []
		classIDs = []

		# loop over each of the layer outputs
		for output in layerOutputs:
			# loop over each of the detections
			for detection in output:
				# extract the class ID and confidence (i.e., probability) of
				# the current object detection
				scores = detection[5:]
				classID = np.argmax(scores)
				confidence = scores[classID]

				# filter out weak predictions by ensuring the detected
				# probability is greater than the minimum probability
				if confidence > args["confidence"]:
					# scale the bounding box coordinates back relative to the
					# size of the image, keeping in mind that YOLO actually
					# returns the center (x, y)-coordinates of the bounding
					# box followed by the boxes' width and height
					box = detection[0:4] * np.array([W, H, W, H])
					(centerX, centerY, width, height) = box.astype("int")

					# use the center (x, y)-coordinates to derive the top and
					# and left corner of the bounding box
					x = int(centerX - (width / 2))
					y = int(centerY - (height / 2))

					# update our list of bounding box coordinates, confidences,
					# and class IDs
					boxes.append([x, y, int(width), int(height)])
					confidences.append(float(confidence))
					classIDs.append(classID)

		# apply non-maxima suppression to suppress weak, overlapping bounding
		# boxes
		idxs = cv2.dnn.NMSBoxes(boxes, confidences, args["confidence"],
			args["threshold"])

		horse_exist = False
		# ensure at least one detection exists
		if len(idxs) > 0:
			# loop over the indexes we are keeping
			for i in idxs.flatten():
				# print(classIDs[i])
				if(classIDs[i] == 17):
					horse_exist = True
					# extract the bounding box coordinates
					(x, y) = (boxes[i][0], boxes[i][1])
					(w, h) = (boxes[i][2], boxes[i][3])
					 # draw a bounding box rectangle and label on the image
					color = [int(c) for c in COLORS[classIDs[i]]]
					cv2.rectangle(image, (x, y), (x + w, y + h), color, 2)
					print("a")
					text = "{}: {:.4f}".format(LABELS[classIDs[i]], confidences[i])
					cv2.putText(image, text, (x, y - 5), cv2.FONT_HERSHEY_SIMPLEX,
								0.5, color, 2)
					imgpoint = np.array([[x,y],[x + w, y], [x, y + h], [x +w, y + h]], dtype=np.float32)
					ret, rvecs, tvecs = cv2.solvePnP(objp, imgpoint, mtx, dist)
					horse_distance = tvecs[2][0]
					cv2.putText(image, str(horse_distance), (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 255), 2, cv2.LINE_AA)
					if horse_distance > 80:
						drone.move_forward(0.3)
					else:
						drone.move_right(0.85)
						step1 = 1
				if key!= -1:
					drone.keyboard(key)	

				if turn_ed and classIDs[i] == 9:
					# extract the bounding box coordinates
					(x, y) = (boxes[i][0], boxes[i][1])
					(w, h) = (boxes[i][2], boxes[i][3])
					 # draw a bounding box rectangle and label on the image
					color = [int(c) for c in COLORS[classIDs[i]]]
					cv2.rectangle(image, (x, y), (x + w, y + h), color, 2)
					print("a")
					text = "{}: {:.4f}".format(LABELS[classIDs[i]], confidences[i])
					cv2.putText(image, text, (x, y - 5), cv2.FONT_HERSHEY_SIMPLEX,
								0.5, color, 2)
					imgpoint = np.array([[x,y],[x + w, y], [x, y + h], [x +w, y + h]], dtype=np.float32)
					ret, rvecs, tvecs = cv2.solvePnP(objp, imgpoint, mtx, dist)
					traffic_distance = tvecs[2][0]
					cv2.putText(image, str(traffic_distance), (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 255), 2, cv2.LINE_AA)
					turn_ed = 0
					time.sleep(5)
					drone.move_left(0.4)
					time.sleep(5)
					drone.land()

		if turn_ed:
			drone.move_left(0.3)

		if(horse_exist == False and step1):
			# new one
			is_marker_detect = False
			if(len(str(markerIds)) != 4):
				is_marker_detect = True
				rvec, tvec, _objPoints = cv2.aruco.estimatePoseSingleMarkers(markerCorners, 11.5, mtx, dist) 
				for i in range(len(markerIds)):
					distance.append(tvec[i][0][2])

			if (is_marker_detect != False):
				dis_index = distance.index(min(distance))
				print(distance[dis_index], dis_index)

			if(is_marker_detect == True):
				image = cv2.aruco.drawAxis(image, mtx, dist ,rvec[dis_index], tvec[dis_index], 4)
				XYZ_pose = "x:%.2f y:%.2f z:%.2f"%(tvec[dis_index][0][0],tvec[dis_index][0][1],tvec[dis_index][0][2])
				print(XYZ_pose)
				x_loc = 0
				y_loc = 0
				for i in range(4):
					x_loc += markerCorners[dis_index][0][i][0]
					y_loc += markerCorners[dis_index][0][i][1]
				x_loc = int(x_loc / 4)
				y_loc = int(y_loc / 4)
				cv2.putText(image,XYZ_pose,(x_loc - 10, y_loc -10),cv2.FONT_HERSHEY_SIMPLEX,0.8, (0, 255, 255), 2, cv2.LINE_AA)
				# print(is_marker_detect)

				# R = cv2.Rodrigues(rvec[dis_index])
				# R = R[0]
				# Z = np.array([0,0,1])
				# Z = R.dot(Z)
				# thea = math.atan2(Z[2],Z[0])

				# zp = -np.rad2deg(thea)

				if(markerIds[dis_index][0] == 1):
					if(tvec[dis_index][0][0] > 7):
						drone.move_right(0.2)
					elif(tvec[dis_index][0][0] < -7):
						drone.move_left(0.2)
					elif(tvec[dis_index][0][2] > 500):
						drone.move_forward(4)
					elif(tvec[dis_index][0][2] <= 500 and tvec[dis_index][0][2] > 200):
						drone.move_forward(1)
					elif(tvec[dis_index][0][2] <= 200 and tvec[dis_index][0][2] >= 110):
						drone.move_forward(0.4)
					elif(tvec[dis_index][0][2] < 110 and tvec[dis_index][0][2] > 50):
						drone.move_forward(0.2)
					elif(tvec[dis_index][0][2] <= 50):
						drone.move_right(0.85)
					if key!= -1:
						drone.keyboard(key)

				elif(markerIds[dis_index][0] == 4):
					if(tvec[dis_index][0][0] > 7):
						drone.move_right(0.2)
					elif(tvec[dis_index][0][0] < -7):
						drone.move_left(0.2)
					elif(tvec[dis_index][0][2] > 500):
						drone.move_forward(4)
					elif(tvec[dis_index][0][2] <= 500 and tvec[dis_index][0][2] > 200):
						drone.move_forward(1)
					elif(tvec[dis_index][0][2] <= 200 and tvec[dis_index][0][2] >= 110):
						drone.move_forward(0.4)
					elif(tvec[dis_index][0][2] < 110 and tvec[dis_index][0][2] > 50):
						drone.move_forward(0.2)
					elif(tvec[dis_index][0][2] <= 50):
						drone.move_left(0.85)
					if key!= -1:
						drone.keyboard(key)

				elif(markerIds[dis_index][0] == 11):
					if(tvec[dis_index][0][0] > 7):
						drone.move_right(0.2)
					elif(tvec[dis_index][0][0] < -7):
						drone.move_left(0.2)
					elif(tvec[dis_index][0][2] > 500):
						drone.move_forward(4)
					elif(tvec[dis_index][0][2] <= 500 and tvec[dis_index][0][2] > 200):
						drone.move_forward(1)
					elif(tvec[dis_index][0][2] <= 200 and tvec[dis_index][0][2] > 120):
						drone.move_forward(0.2)
					elif(tvec[dis_index][0][2] < 120):
						drone.rotate_cw(180)
						time.sleep(2)
						turn_ed = 1
					if key!= -1:
						drone.keyboard(key)


				elif(markerIds[dis_index][0] == 21):
					drone.move_left(0.2)
				
				if key!= -1:
					drone.keyboard(key)	
		if init and key == ord('1'):
			time.sleep(3)
			drone.move_up(0.7)
			init = 0
		if key == ord('2'):
			drone.land()
			time.sleep(3)
		# show the output image
		cv2.imshow("Image", image)
			

if __name__ == "__main__":
	main()
	cap.release()
	cv2.destroyAllWindows()
