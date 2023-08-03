#!/usr/bin/env bash


source "$(dirname $(readlink -f  ${BASH_SOURCE[0]}))/file-dependency/check_dependency.sh"
check_dependency ffmpeg

if [[ $? -ne 0 ]]; then
    exit 1
fi

if [[ ! -d "album_art" ]]; then
    mkdir album_art
fi

if [[ ! -d "output" ]]; then
    mkdir output
fi

for file in *.mp3; do
    if [[ "$file" == "*.mp3" ]]; then
        echo "No mp3 file found"
        rmdir album_art/ output/
        exit 1
    fi

    filename=$(echo "$file" | sed -sE "s/\..{2,5}$//")

    if [[ ! -f "album_art/$filename" ]]; then
        search_query=$(echo "$filename" | sed -sE "s/ /+/g")
        yt_search="https://www.youtube.com/results?search_query=$search_query"
        yt_vid=$(curl -s $yt_search | grep -soP "\/watch\?v=.{11}" | head -n1)
    fi
done

echo "Done!"
exit 0
