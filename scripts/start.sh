#!/bin/zsh
sh $HOME/scripts/status.sh &
sh $HOME/scripts/wallpaper.sh &
fcitx5 &
picom --config=$HOME/.config/picom.conf &
exec dwm
