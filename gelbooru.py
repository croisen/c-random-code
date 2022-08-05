#!/usr/bin/env python3


import os
import random
import re
import requests
import sys
from PIL import Image  


def main():
	tags = ""

	if len(sys.argv) > 1:
		if sys.argv[1] == "--help" or sys.argv[1] == "-h":
			print("My image scraper for gelbooru.")
			print("Usage: " + sys.argv[0] + " <<tags>>" )
			print("-------------------------------------------------")
			print("-h\t\tDisplays this message and exits")
			print("--help\t\tDisplays this message and exits")
			print("-------------------------------------------------")
			print("The tags are to be seperated by spaces")
			print("Ex: " + sys.argv[0] + " closers mirae")
			print("-------------------------------------------------")
			print("But tags that are supposed to have a space will have their spaces replaced with underscores. Does my wording make sense?")
			print("Ex: " + sys.argv[0] + " fire_emblem byleth")

			sys.exit(0)


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

		if os.path.exists(filename):
			print("Nevermind dis pic is already downloaded.")
			sys.exit()
		
		with open(filename, "wb") as file:
			print("Now downloading " + filename)
			file.write(download_the_pic.content)
	else:
		print("Couldn't download the file")

if __name__ == '__main__':
	main()