import os
import cv2
def detect(dataPath, clf):
    """
    Please read detectData.txt to understand the format. Load the image and get
    the face images. Transfer the face images to 19 x 19 and grayscale images.
    Use clf.classify() function to detect faces. Show face detection results.
    If the result is True, draw the green box on the image. Otherwise, draw
    the red box on the image.
      Parameters:
        dataPath: the path of detectData.txt
      Returns:
        No returns.
    """
    # Begin your code (Part 4)
    # raise NotImplementedError("To be implemented")
    detection_path = os.path.split(dataPath)[0]
    n_face = []
    image = []
    face_loc = []
    # open the file and store the data into lists
    with open(dataPath, 'rb') as f:
        for line in f.readlines():
            img_info = line.decode('utf-8').split()
            # filename, n_face
            if len(img_info) == 2:
                filename = img_info[0]
                n_face.append(int(img_info[-1]))
                image.append(cv2.imread(os.path.join(detection_path, filename)))
            # x, y, w, h
            elif len(img_info) == 4:
                face_loc.append([int(img_info[0]), int(img_info[1]), int(img_info[2]), int(img_info[3])])
    face_id = 0
    for image_id in range(len(image)):
        img = image[image_id]
        num_face = n_face[image_id]
        for _ in range(num_face):
            x, y, w, h = face_loc[face_id]
            face_img = img[y : y + h, x : x + w]
            # resize to 19 * 19
            face_img = cv2.resize(face_img, (19, 19))
            # BGR --> GRAY
            face_img = cv2.cvtColor(face_img, cv2.COLOR_BGR2GRAY)
            # predict with the model
            prediction = clf.classify(face_img)
            # face --> right --> green
            if prediction == 1:
                color = (0, 255, 0)
            # non-face --> wrong --> red
            else: 
                color = (0, 0, 255)
            # draw the rectangle on the image
            cv2.rectangle(img, (x, y), (x + w, y + h), color, 2)
            face_id += 1
        height, width, channels = img.shape
        # shrink the image if it is too large to show
        if height > 2000:
            img = cv2.resize(img, None, fx=0.5, fy=0.5)
        cv2.imshow('My Image', img)
        cv2.waitKey(0)
        cv2.destroyAllWindows()
    # End your code (Part 4)