#!/usr/bin/env bash


Agent="Mozilla/5.0 (X11; Linux x86_64; rv:100.0) Gecko/20100101 Firefox/100.0"
printf "Input an nhentai doujin number: "
read doujin_number
doujin_dir="$HOME/.cache/$doujin_number"
mkdir -p $doujin_dir
pages=$(curl -sL "nhentai.net/g/$doujin_number/1/" | sed -nE 's/.*pages">(.*)<\/span><.*/\1/p')

function QUIT {
    rm -rf $doujin_dir
    printf "\nQuitting...\n"
    exit 1
}

trap QUIT SIGINT
curl -sLA $Agent "nhentai.net/g/$doujin_number/1/" | grep -q "Not Found" && echo "Doujin doesn't exist!" && QUIT

for i in $(seq $pages)
do
    image_url=$(curl -sLA $Agent "nhentai.net/g/$doujin_number/$i/" | sed -nE 's/.*<img src="([^"]*)".*/\1/p')
    page_num=$(printf "%03d" $i)
    curl -sA $Agent "$image_url" -o "$doujin_dir/$page_num.jpg"
    printf "\rDownloaded page $i out of $pages"
done

printf "\nConverting images to PDF\n"
convert $doujin_dir/* $doujin_number.pdf
rm -rf $doujin_dir
echo "Done!"
exit 0
