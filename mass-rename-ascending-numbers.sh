#!/usr/bin/env bash


if ! command -v prename; then
    echo "Perl rename cannot be found, please install perl rename"
    exit 1
fi

prename 's/ /-/g' *

last_file=$(ls *.*| tail -n1)
last_numbered_file=$(ls *.*| grep -sP '^\d{7}\.\w+' | tail -n1)

echo "Last file in this folder: $last_file"
echo "Last numbered file in this folder: $last_numbered_file"
printf '\n%s\n> ' "On what number should I start?"
read count

if ! [ $count -eq $count 2>/dev/null ]; then
    echo "This ain't a number man, I'm quitting..."
    exit 1
fi

for file in $(ls *.* 2>/dev/null | grep -svP '^\d{7}\.\w+'); do
    count_padding=$(printf '%07d' "${count}")
    file_extension=$(echo $file | grep -soP '\.\w+$' )
    mv -v --backup=numbered --suffix=.bak $file $count_padding$file_extension
    ((count++))
done

echo "Done!"
exit 0
