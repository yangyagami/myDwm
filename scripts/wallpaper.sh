while true; 
do
	wallpaper=$(find $HOME/Pictures/Wallpapers/ -type f | shuf -n 1)
	echo ${wallpaper}
	feh ${wallpaper} --bg-scale
	sleep 5m
done
