#!/bin/zsh
sh $HOME/scripts/status.sh &
fcitx5 &
picom --config=/etc/xdg/picom.conf &
exec dwm
