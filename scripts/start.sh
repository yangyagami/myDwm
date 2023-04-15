#!/bin/zsh
sh $HOME/scripts/status.sh &
sh $HOME/scripts/wallpaper.sh &
fcitx5 &
picom --config=$HOME/.config/picom/picom.conf &
exec dwm
