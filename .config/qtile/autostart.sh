#!/bin/sh

xrdb -load ~/.Xresources &
numlockx on &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
picom -b --config ~/.config/picom/picom.conf &
dunst -conf ~/.config/qtile/dunst/dunstrc_qtile &
xautolock -time 10 -locker lock -corners '+-00' -cornerdelay 15 -notify 15 -notifier "notify-send 'Screen will lock in 15 s'" &
nm-applet &
blueman-applet &
mpdris2-rs &
pasystray --no-notify &
nitrogen --restore &
birdtray &
valent &