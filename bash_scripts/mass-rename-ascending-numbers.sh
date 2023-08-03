#!/usr/bin/env bash


last_file=$(ls *.*| tail -n1)
last_numbered_file=$(ls *.*| grep -sP '^\d{7}\.\w+' | tail -n1)

echo "Last file in this folder: $last_file"
echo "Last numbered file in this folder: $last_numbered_file"
printf '\n%s\n> ' "On what number should I start?"
read count

if ! [[ $count -eq $count ]]; then
    echo "This ain't a number man, I'm quitting..."
    exit 1
fi

for file in *; do
    if [[ -f $file ]] && ! echo $file | grep -soP "^\d{7}\.\w+"; then
        count_padding=$(printf '%07d' "${count}")
        file_ext=$(echo "$file" | grep -soP '\..{2,5}$' )
        mv -v --backup=numbered --suffix=.bak "$file" "$count_padding$file_ext"
        ((count++))
    fi
done

echo "Done!"
exit 0
