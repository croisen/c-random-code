#!/usr/bin/env bash


if [[ ! -d "album_art" ]]; then
    mkdir album_art
fi

if [[ ! -d "output" ]]; then
    mkdir output
fi

for file in *.mp3; do
    filename=$(echo "$file" | sed -sE "s/\..{2,5}$//")

    if [[ ! -f "album_art/$filename.png" ]] || [[ $filename -ne "*" ]]; then
        search_query=$(echo "$filename" | sed -sE "s/ /+/g")
        yt_search="https://www.youtube.com/results?search_query=$search_query"
        yt_vid=$(curl -s $yt_search | grep -soP "\/watch\?v=.{11}" | head -n1)
        thumbnail="https://i.ytimg.com/vi/$(echo $yt_vid | sed -sE 's/\/watch\?v=//')/hqdefault.jpg"
        curl -s $thumbnail -o "album_art/$filename"
        echo "Downloaded thumbnail for $filename"
        convert "album_art/$filename" "album_art/$filename.png"
        rm -v "album_art/$filename"
    elif [[ "$filename" -eq "*" ]]; then
        rm -r album_art output
        return 1
    fi

    if [[ ! -f "output/$file" ]]; then
        ffmpeg -i "$file" -i "album_art/$filename.png" -map_metadata 0 -map 0 -map 1 "output/$file"
    fi
done

echo "Done!"
exit 0
