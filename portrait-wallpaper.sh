#!/usr/bin/env bash


## The opposite of landscape_wallpaper, a script that will look for pictures that are supposedly "portrait" and resize them to my phone's screen res ##
phone_res="720x1520"
dependency_check=0

if ! command -v convert &> /dev/null; then
    echo "Convert not found, please install ImageMagick"
    dependency_check=1
fi

if ! command -v file &> /dev/null; then
    echo "File command not found, please install File"
    dependency_check=1
fi

if ! command -v prename &>/dev/null; then
    echo "Perl rename cannot be found, please install perl rename"
    dependency_check=1
fi

if [[ $dependency_check -ne 0 ]]; then
    exit 1
fi

prename 's/ /_/g' *.jpg *.png

for file in $(ls *.jpg *.png *.webp *.jpeg 2>/dev/null); do
    width=$(file $file | grep -soP '\, \d+ ' | grep -soP '\d+')
    height=$(file $file | grep -soP 'x \d+' | grep -soP '\d+')
    filename=$(echo $file | sed -sE 's/\.\w+$//')
    file_ext=$(echo $file | grep -soP '\w+$')

    if [[ $file_ext != "png" ]]; then
        intermediate_file="intermediate_$filename.png"
        convert $file $intermediate_file
        width=$(file $intermediate_file | grep -soP '\, \d+ ' | grep -soP '\d+')
        height=$(file $intermediate_file | grep -soP 'x \d+' | grep -soP '\d+')

        if [[ $height -gt $width ]]; then
            echo "Converting $file into portrait_$filename.png"
            convert $file -resize $phone_res\! portrait_$filename.png
        fi

        rm $intermediate_file
    else
        if [[ $height -gt $width ]]; then
            echo "Converting $file into portrait_$filename.png"
            convert $file -resize $phone_res\! portrait_$filename.png
        fi
    fi
done

prename 's/ /_/g' *.jpg *.png
echo "Done!"
exit 0
