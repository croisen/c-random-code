#!/usr/bin/env bash


source "$(dirname $(readlink -f  ${BASH_SOURCE[0]}))/file-dependency/check_dependency.sh"
check_dependency exiftool

for file in *.jpg *.png *.jpeg; do
    if ! [[ $file == "*.png" || $file == "*.jpeg" || $file == "*.jpg" ]]; then
        echo "Nuking the exif data of $file"
        exiftool -overwrite_orginal -all= $file &>/dev/null
    fi
done

echo "Done!"
exit 0
