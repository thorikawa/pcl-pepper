#! /usr/bin/env python
# -*- coding:utf-8 -*-

"""This is a script to obtain point cloud with pcd format from Pepper's depth sensor."""

__author__ = "Takahiro Poly Horikawa <horikawa.takahiro@gmail.com>"
__version__ = "1.0.0"
__date__    = "14 Dec, 2014"

import argparse
from PIL import Image
from naoqi import ALProxy

# Camera parameters (only tested on Pepper)
# Focal length
FX = 525.0 / 2
FY = 525.0 / 2
# Optical center
CX = 319.5 / 2
CY = 239.5 / 2

# meter to millimeter
UNIT_SCALING = 0.001

NAME = "depth_camera"
CAMERA_ID = 2 # depth
RESOLUTION = 1 # 320*240
FRAMERATE = 15
COLOR_SPACE = 17 # mono16 Note: this is not documented as of Dec 14, 2014

def main(args):
	# reference
	# https://github.com/ros-aldebaran/romeo_robot/blob/master/romeo_sensors/nodes/camera_depth.py
	# https://github.com/ros-perception/image_pipeline/blob/indigo/depth_image_proc/src/nodelets/point_cloud_xyz.cpp

	video = ALProxy('ALVideoDevice', args.ip, args.port)
	client = video.subscribeCamera(NAME, CAMERA_ID, RESOLUTION, COLOR_SPACE, FRAMERATE)

	try:
		image = video.getImageRemote(client)

		if image is None:
			print 'Cannot obtain depth image.'
			exit()

		width = image[0]
		height = image[1]
		array = image[6]

		cloud = []
		for v in range(height):
			for u in range(width):
				offset = (v * width + u) * 2
				depth = ord(array[offset]) + ord(array[offset+1]) * 256 

				x = (u - CX) * depth * UNIT_SCALING / FX
		  		y = (v - CY) * depth * UNIT_SCALING / FY
		  		z = depth * UNIT_SCALING

		  		cloud.append((x, y, z))
	finally:
		video.unsubscribe(client)

	header = '''# .PCD v0.7 - Point Cloud Data file format
VERSION 0.7
FIELDS x y z
SIZE 4 4 4
TYPE F F F
COUNT 1 1 1
WIDTH %d
HEIGHT 1
VIEWPOINT 0 0 0 1 0 0 0
POINTS %d
DATA ascii'''

	f = open(args.output, 'w')
	num = len(cloud)
	f.write(header % (num, num))
	f.write("\n")
	for c in cloud:
		f.write('%f %f %f' % (c[0], c[1], c[2]))
		f.write("\n")
	f.close()

if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument('-o', '--output', required=True, help='File to output point cloud')
	parser.add_argument('-i', '--ip', required=True, help='IP address of Pepper')
	parser.add_argument('-p', '--port', required=False, type=int, default=9559, help='Port number to connect to Pepper')
	args = parser.parse_args()
	main(args)

