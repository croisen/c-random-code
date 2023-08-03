#!/usr/bin/env bash


source "$(dirname $(readlink -f  ${BASH_SOURCE[0]}))/file-dependency/check_dependency.sh"
echo "Checking for ImageMagick convert util..."
check_dependency convert

for file in *.jpg *.jpeg *.webp; do
    filename=$(echo $file | sed -sE 's/\.\w+$//')

    if [[ $filename != "*" ]]; then
        echo "Converting $file to output-$filename.png"
        convert $file "output-$filename.png"
    fi
done

echo "Done!"
exit 0
