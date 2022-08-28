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

if [[ $dependency_check -ne 0 ]]; then
    exit 1
fi

for file in *.jpg *.png *.webp *.jpeg; do
    if ! [[ $file == "*.jpg" || $file == "*.jpeg" || $file == "*.png" || $file == "*.webp" ]]; then
        width=$(file "$file" | grep -soP '\, \d+ ' | grep -soP '\d+')
        height=$(file "$file" | grep -soP 'x \d+' | grep -soP '\d+')
        filename=$(echo "$file" | sed -sE 's/\.\w+$//')
        file_ext=$(echo "$file" | grep -soP '\w+$')

        if [[ $file_ext != "png" ]]; then
            intermediate_file="intermediate-$filename.png"
            convert "$file" "$intermediate_file"
            width=$(file "$intermediate_file" | grep -soP '\, \d+ ' | grep -soP '\d+')
            height=$(file "$intermediate_file" | grep -soP 'x \d+' | grep -soP '\d+')

            if [[ $height -gt $width ]]; then
                echo "Converting $file into portrait-$filename.png"
                convert "$file" -resize $phone_res\! "portrait-$filename.png"
            fi

            rm "$intermediate_file"
        else
            if [[ $height -gt $width ]]; then
                echo "Converting $file into portrait-$filename.png"
                convert "$file" -resize $phone_res\! "portrait-$filename.png"
            fi
        fi
    fi
done

echo "Done!"
exit 0
