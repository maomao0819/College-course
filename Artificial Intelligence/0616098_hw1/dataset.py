import os
import numpy as np

def is_pgm_file(path_file):
    if not os.path.isfile(path_file):
        return False
    if path_file is not str and not path_file.endswith('.pgm'):
        return False
    return True

def get_image(path_file):
    # check if it is pgm file first
    if not is_pgm_file(path_file):
        raise Exception("%s is not a PGM file" % path_file)
    # read file
    with open(path_file, 'rb') as f:
        # magic number(the code in the beginning of pgm file) is often "P5"
        magic_number = f.readline().strip().decode('utf-8')
        if not magic_number == "P5":
            raise Exception("The wrong image")
        # get W and H with the pgm format
        width, height = f.readline().strip().decode('utf-8').split(' ')
        width = int(width)
        height = int(height)
        maxval = f.readline().strip()
        # the image pixel value may store than a byte
        if int(maxval) < 256:
            one_reading = 1
        else:
            one_reading = 2
        # read the content to the numpy array
        image = np.zeros((height, width))
        image[:][:] = [[ord(f.read(one_reading)) for j in range(width)] for i in range(height)]
        return image

def loadImages(dataPath):
    """
    load all Images in the folder and transfer a list of tuples. The first 
    element is the numpy array of shape (m, n) representing the image. 
    The second element is its classification (1 or 0)
      Parameters:
        dataPath: The folder path.
      Returns:
        dataset: The list of tuples.
    """
    # Begin your code (Part 1)
    # raise NotImplementedError("To be implemented")
    dataset = []
    directory = os.listdir(dataPath)
    for d in directory:
        # non-face
        if 'non' in d:
            label = 0
        # face
        else:
            label = 1
        path = os.path.join(dataPath, d)
        for f in os.listdir(path):
            file = os.path.join(path, f)
            image = get_image(file)
            dataset.append((image, label))
    # End your code (Part 1)
    return dataset

