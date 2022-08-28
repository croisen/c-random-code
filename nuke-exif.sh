#!/usr/bin/env bash


if ! command -v exiftool &>/dev/null; then
    echo "Exiftool cannot be found, please install exiftool"
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

for file in $(ls *.jpg *.png); do
    echo "Nuking the exif data of $file"
    exiftool -overwrite_orginal -all= $file &>/dev/null
done

prename 's/_/ /g' *.jpg *.png
echo "Done!"
exit 0
