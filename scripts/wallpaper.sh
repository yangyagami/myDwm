#!/bin/bash

IFS=$'\t\n'

# 存储文件名的数组
file_array=()

# 将文件夹下的所有文件名存储到数组中
for file in $HOME/Pictures/Wallpapers/*; do
    if [ -f "$file" ]; then
        file_array+=("$(basename "$file")")
    fi
done

while :
do
    # 遍历数组，设置背景图片
    for filename in "${file_array[@]}"; do
	feh $HOME/Pictures/Wallpapers/$filename --bg-scale
	sleep 2m
    done
done

