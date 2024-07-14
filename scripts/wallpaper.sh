while true; 
do
	wallpaper=$(find $HOME/Pictures/Wallpapers/ -type f | shuf -n 1)
	feh ${wallpaper} --bg-scale
	sleep 1m
done
