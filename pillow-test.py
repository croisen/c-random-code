#!/usr/bin/env python3

import os
from PIL import Image
import re

images_in_dir = os.listdir()

image_width = 1366
image_height = 768

for image in images_in_dir:
	if image.endswith('.png') or image.endswith('.jpg'):
		filename_regex = re.search('.*\.', image)
		filename = filename_regex.group().replace('.', '')
		print(filename)

		image_file = Image.open(image)
		image_file.resize((image_width, image_height), Image.ANTIALIAS)
		image_file.save('idk'+filename+'.png')