import numpy as np
import argparse
import time
import cv2
import os
 

f = cv2.FileStorage("rslt.xml", cv2.FILE_STORAGE_READ)
mtx = f.getNode("instric").mat()
dist = f.getNode("distortion").mat()


##73 == shoulder length      180 == height
width = 16
height = 22
objp = [[0,0,0],[(width*1.05),0,0],[0,(height*1.05),0],[(width*1.05),(height*1.05),0]]
objp = np.array(objp,dtype=np.float32)



img = cv2.imread("WIN_20200604_19_00_32_Pro.jpg")
imgpoint = []
# USAGE
# python yolo.py --image images/baggage_claim.jpg --yolo yolo-coco

# import the necessary packages

# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required=True,
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

# load our input image and grab its spatial dimensions
image = cv2.imread(args["image"])
# cap = cv2.VideoCapture(0)

# ret,image = cap.read()
(H, W) = image.shape[:2]
# H = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
# W = cap.get(cv2.CAP_PROP_FRAME_WIDTH)

# determine only the *output* layer names that we need from YOLO
ln = net.getLayerNames()
ln = [ln[i[0] - 1] for i in net.getUnconnectedOutLayers()]

# construct a blob from the input image and then perform a forward
# pass of the YOLO object detector, giving us our bounding boxes and
# associated probabilities
blob = cv2.dnn.blobFromImage(image, 1 / 255.0, (416, 416),
    swapRB=True, crop=False)
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

# ensure at least one detection exists
if len(idxs) > 0:
    # loop over the indexes we are keeping
    for i in idxs.flatten():
        # extract the bounding box coordinates
        (x, y) = (boxes[i][0], boxes[i][1])
        (w, h) = (boxes[i][2], boxes[i][3])

        # draw a bounding box rectangle and label on the image
        color = [int(c) for c in COLORS[classIDs[i]]]
        cv2.rectangle(image, (x, y), (x + w, y + h), color, 2)
        text = "{}: {:.4f}".format(LABELS[classIDs[i]], confidences[i])
        cv2.putText(image, text, (x, y - 5), cv2.FONT_HERSHEY_SIMPLEX,
            0.5, color, 2)
        imgpoint = np.array([[x,y],[x + w, y], [x,y + h], [x+w, y + h]], dtype=np.float32)
        ret, rvecs, tvecs = cv2.solvePnP(objp, imgpoint, mtx, dist)
        # cv2.putText(img, str(boxes[i][0]), (x + y-10, rects_y + rects_h-10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 255), 2, cv2.LINE_AA)
        cv2.putText(img, str(revc[2][0]),(x,y),  cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 255), 2, cv2.LINE_AA)

    
# show the output image
cv2.imshow("Image", image)
cv2.waitKey(0)

#                 imgpoint = np.array([[rects_x,rects_y],[rects_x + rects_w, rects_y], [rects_x,rects_y + rects_h], [rects_x+rects_w, rects_y + rects_h]], dtype=np.float32)
#                 img = cv2.rectangle(img, (faces_x, faces_y), (faces_x + faces_w, faces_y + faces_h), (0, 255, 0), 2)
#                 img = cv2.rectangle(img, (rects_x, rects_y), (rects_x + rects_w, rects_y + rects_h), (0, 255, 255), 2)
                
#                 ret, rvecs, tvecs = cv2.solvePnP(objp, imgpoint, mtx, dist)
#                 cv2.putText(img, str(tvecs[2][0]), (rects_x+rects_w-10, rects_y + rects_h-10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 255), 2, cv2.LINE_AA)
                
#                 imgpoint_face = np.array([[faces_x,faces_y],[faces_x + faces_w, faces_y], [faces_x,faces_y + faces_h], [faces_x+faces_w, faces_y + faces_h]], dtype=np.float32)
#                 ret, rvecs2, tvecs2 = cv2.solvePnP(objp_face, imgpoint_face, mtx, dist)
#                 cv2.putText(img, str(tvecs[2][0]*1.0795), (faces_x+faces_w-5, faces_y +faces_h-5), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2, cv2.LINE_AA)
#                 #print(tvecs[2][0])
# cv2.imshow('556622', img)
    
    
cap.release()
cv2.destroyAllWindows()


#objp = np.zeros((4,3), np.float32),, [rects_x,rects_y + rects_h], [rects_x+rects_w, rects_y + rects_h]
#imgpoint.append(np.array([[rects_x,rects_y],[rects_x + rects_w, rects_y], [rects_x,rects_y + rects_h], [rects_x+rects_w, rects_y + rects_h]], dtype=np.float32))
#imgpoint = [[rects_x,rects_y],[rects_x + rects_w, rects_y], [rects_x,rects_y + rects_h], [rects_x+rects_w, rects_y + rects_h]]

