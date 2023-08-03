#!/bin/bash


for file in *.zip; do
    if ! [[ $file == "*.zip" ]]; then
        filename=$(echo $file | sed -sE "s/\..{3}$//")
        unzip -P thatnovelcorner.com "$file"
        rm "$file"
    fi
done

echo "Done!"
exit 0
