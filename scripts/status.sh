#!/bin/zsh

while true; do
		xsetroot -name "$(free -m | awk 'NR==2{printf "Memory Usage: %s/%sMB (%.2f%%)\n", $3,$2,$3*100/$2 }') | $( date +"%F %R" )"
   sleep 1m    # Update time every minute
done &

