#!/bin/bash

nitrogen --restore &
xrdb -load ~/.Xresources &
$HOME/.config/dk/polybar/launch.sh &
numlockx on &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
#xsettingsd &
nm-applet &
picom -b --config ~/.config/picom/picom.conf &
dunst -conf ~/.config/dk/dunst/dunstrc &
xautolock -time 10 -locker lock -corners '+-00' -cornerdelay 15 -notify 15 -notifier "notify-send 'Screen will lock in 15 s'" &
blueman-applet &
mpDris2 &
pasystray --no-notify &
birdtray &
valent &
#(sleep 5; $HOME/.config/dk/polybar/bar_toggle.sh) &
