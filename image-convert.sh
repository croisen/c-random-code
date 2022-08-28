#!/usr/bin/env bash


if ! command -v convert &> /dev/null; then
    echo "Convert not found, please install ImageMagick"
    dependency_check=1
fi

if ! command -v prename &> /dev/null; then
    echo "Perl rename cannot be found, please install perl rename"
    dependency_check=1
fi

if [[ $dependency_check -ne 0 ]]; then
    exit 1
fi

prename 's/ /_/g' *.jpg *.jpeg *.webp

for file in $(ls *.jpg *.jpeg *.webp 2>/dev/null)
do
    echo "Converting $file"
    filename=$(echo $file | sed -sE 's/\.\w+$//')
    convert $file $filename.png
    rm $file
done

prename 's/_/ /g' *.jpg *.jpeg *.webp
echo "Done!"
exit 0
