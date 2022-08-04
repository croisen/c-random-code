#!/usr/bin/env python3


import random
import re
import requests
import sys
from PIL import Image  


def main():
	tags = ""

	if len(sys.argv) > 1:
		for i in range(1, (len(sys.argv))):
			tags += "+" + sys.argv[i]

		tags = re.sub("^\+", "", tags)
		print("Currently trying to connect to gelbooru")
		url = requests.post("https://gelbooru.com/index.php?page=post&s=list&tags=" + tags)
		picture_list = re.findall("https://gelbooru\.com/index\.php\?page=post&amp;s=view&amp;id=[\d\w;&=]+", url.text)
		
		if not picture_list:
			print("No pictures found with your search tags")

		x = re.sub("amp;", "",random.choice(picture_list))
		print("Getting the source image link")
		url_source = requests.post(str(x))
		pic = re.search("https://\w+\.gelbooru\.com/images/\w+/\w+/[\w\.]+", url_source.text)
	else:
		print("Currently trying to connect to gelbooru")
		url = requests.post("https://gelbooru.com/index.php?page=post&s=list&tags=all&pid=" + str((random.randint(1, 200) * 42)))
		picture_list = re.findall("https://gelbooru\.com/index\.php\?page=post&amp;s=view&amp;id=[\d\w;&=]+", url.text)
		
		if not picture_list:
			print("No pictures found with your search tags")

		x = re.sub("amp;", "",random.choice(picture_list))
		print("Getting the source image link")
		url_source = requests.post(str(x))
		pic = re.search("https://\w+\.gelbooru\.com/images/\w+/\w+/[\w\.]+", url_source.text)

	download_the_pic = requests.get(pic.group())

	if download_the_pic.status_code == 200:
		filename = re.sub("https://\w+\.gelbooru\.com/images/\w+/\w+/", "", pic.group())
		print("Now downloading " + filename)
		
		with open(filename, "wb") as file:
			file.write(download_the_pic.content)
	else:
		print("Couldn't download the file")

if __name__ == '__main__':
	main()