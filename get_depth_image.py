#!/usr/bin/env python

from PIL import Image
from naoqi import ALProxy

video = ALProxy("ALVideoDevice", '192.168.11.7', 9559)

name = "python_client"
client = video.subscribeCamera(name, 2, 1, 0, 1)

try:
	naoImage = video.getImageRemote(client)

	if naoImage is None:
		print 'Image is None.'
		exit()

	imageWidth = naoImage[0]
	imageHeight = naoImage[1]
	array = naoImage[6]
	im = Image.fromstring("L", (imageWidth, imageHeight), array)
	pixels = im.load()

	print '%d %d' % (imageWidth, imageHeight)
	path = "depth_image.png"
	im.save(path, "PNG")
	im.show()
finally:
	video.unsubscribe(client)

# for i in range(imageWidth):
# 	for j in range(imageHeight):
# 		print str(pixels[i, j])

header = '''# .PCD v0.7 - Point Cloud Data file format
VERSION 0.7
FIELDS x y z
SIZE 4 4 4
TYPE F F F
COUNT 1 1 1
WIDTH 10000
HEIGHT 1
VIEWPOINT 0 0 0 1 0 0 0
POINTS 10000
DATA ascii'''

# print header