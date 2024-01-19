#!/bin/sh

export XDG_SESSION_TYPE="x11"
xrdb merge ~/.Xresources &
nitrogen --restore &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
(sleep 5; nm-applet) &
#(sleep 5; blueman-applet) &
numlockx on &
mpdris2-rs &
dunst -conf ~/.config/dunst/dunstrc_dwm &
picom --config ~/.config/picom/picom.conf --daemon &
(sleep 1; xautolock -time 15 -locker slock -corners '+-00' -cornerdelay 15 -notify 15 -notifier "notify-send 'Screen will lock in 15 s'") &
caffeine &
#birdtray &
(sleep 10; thunderbird) &
valent &
greenclip &
sleep 15 && $HOME/.config/dwmblocks-async/build/dwmblocks &
sleep 30 && dbus-update-activation-environment --systemd --all &
#kitty &
#conky -c ~/.config/conky/dobbie_np2.conkyrc &