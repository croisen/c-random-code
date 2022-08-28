#!/bin/bash


if ! command -v prename &>/dev/null; then
    echo "Perl rename cannot be found, please install perl rename"
    exit 1
fi

prename 's/ //g' *.zip

for file in $(ls *.zip)
do
    unzip -P thatnovelcorner.com $file
    rm $file
done

prename 's/ Premium//g' *.epub
echo "Done!"
exit 0
