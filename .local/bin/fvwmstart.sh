#!/bin/sh

xrdb merge ~/.Xresources &
nitrogen --restore &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
(sleep 5; nm-applet) &
(sleep 5; pasystray) &
(sleep 5; blueman-applet) &
numlockx on &
mpDris2 &
dunst -conf ~/.config/dunst/dunstrc_fvwm &
caffeine &
firewall-applet &
picom --config ~/.config/picom/picom_fvwm.conf --daemon &
(sleep 1; xautolock -time 10 -locker lock -corners '+-00' -cornerdelay 15 -notify 15 -notifier "notify-send 'Screen will lock in 15 s'") &

exec /usr/bin/fvwm3

