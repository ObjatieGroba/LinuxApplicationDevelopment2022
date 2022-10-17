#!/bin/bash

i=0
text_lines=()
coords=()

while read -r line
do
    text_lines+=("$line")
    for j in $(seq 0 $((${#line} - 1)) )
    do
        coords+=("$i $j")
    done
    ((++i))
done

coords="$(echo "$coords" | shuf)"

clear
for line in $(shuf -i 0-$((${#coords[@]}-1)) )
do
    coord=(${coords[$line]})
    tput cup ${coord[0]} ${coord[1]}
    echo "${text_lines[${coord[0]}]:${coord[1]}:1}"
    sleep ${1:-0.1}

done
tput cup "${#text_lines[@]}" 0
