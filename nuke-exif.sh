#!/usr/bin/env bash


if ! command -v exiftool &>/dev/null; then
    echo "Exiftool cannot be found, please install exiftool"
    exit 1
fi

for file in *.jpg *.png *.jpeg; do
    if ! [[ $file == "*.png" || $file == "*.jpeg" || $file == "*.jpg" ]]; then
        echo "Nuking the exif data of $file"
        exiftool -overwrite_orginal -all= $file &>/dev/null
    fi
done

echo "Done!"
exit 0
