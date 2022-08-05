#!/usr/bin/env bash


for arg_or_tags in "$@"; do
	if [[ $arg_or_tags == "--help" || $arg_or_tags == "-h" ]]; then
		echo "Croisen's image scraper for gelbooru."
		echo "Usage: $0 <<tags>>" 
		echo "-------------------------------------------------"
		echo "-h		Displays this message and exits"
		echo "--help		Displays this message and exits"
		echo "-------------------------------------------------"
		echo "The tags are to be seperated by spaces"
		echo "Ex: $0 closers mirae"
		echo "-------------------------------------------------"
		echo "But tags that are supposed to have a space will have their spaces replaced with underscores."
		echo "Does my wording make sense?"
		echo "Ex: $0 fire_emblem byleth"

		exit 0
	fi

	tags+="+$arg_or_tags"
done

if [[ -n "$tags" ]]; then
	tags=$(echo $tags | sed -E 's/^\+//')
	url="https://gelbooru.com/index.php?page=post&s=list&tags=$tags"
	echo "Currently trying to connect to Gelbooru"
	url=($(curl -s $url | grep -soP 'https://gelbooru\.com/index\.php\?page=post&amp;s=view&amp;id=[\d\w;&=]+'))

	if [[ -z $url ]]; then
		echo "No image found within search tags"
		exit 1
	fi
	
	echo "Getting image source"
	url=$(echo ${url[$RANDOM % ${#url[@]}]} | sed -E 's/amp;//g')
	url=$(curl -s $url | grep -soP 'https://\w+\.gelbooru\.com/images/\w+/\w+/[\w\.]+' | head -n1)

	echo "Downloading the pic as $(echo $url | grep -soP '\w+\.\w+$')"
	curl -s $url -o "$(echo $url | grep -soP '\w+\.\w+$')"
else
	page_num=$((($RANDOM % 15) * 42))
	url="https://gelbooru.com/index.php?page=post&s=list&tags=all&pid=$page_num"
	echo "Currently trying to connect to Gelbooru"
	url=($(curl -s $url | grep -soP 'https://gelbooru\.com/index\.php\?page=post&amp;s=view&amp;id=[\d\w;&=]+'))

	if [[ -z $url ]]; then
		echo "No image found within search tags"
		exit 1
	fi
	
	echo "Getting image source"
	url=$(echo ${url[$RANDOM % ${#url[@]}]} | sed -E 's/amp;//g')
	url=$(curl -s $url | grep -soP 'https://\w+\.gelbooru\.com/images/\w+/\w+/[\w\.]+' | head -n1)

	echo "Downloading the pic as $(echo $url | grep -soP '\w+\.\w+$')"
	curl -s $url -o "$(echo $url | grep -soP '\w+\.\w+$')"
fi
