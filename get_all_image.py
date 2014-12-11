#!/usr/bin/env python

from PIL import Image
from naoqi import ALProxy

video = ALProxy("ALVideoDevice", '192.168.11.7', 9559)

for cameraId in range(3):
	name = "python_client%d" % cameraId
	client = video.subscribeCamera(name, cameraId, 1, 11, 1)

	try:
		naoImage = video.getImageRemote(client)

		if naoImage is None:
			print 'Image is None. cameraId=%d' % cameraId
			continue

		w = naoImage[0]
		h = naoImage[1]
		array = naoImage[6]
		im = Image.fromstring("RGB", (w, h), array)
		pixels = im.load()

		path = "image%d.png" % cameraId
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