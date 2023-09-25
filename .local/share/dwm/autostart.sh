#!/bin/sh

sleep 30 && dbus-update-activation-environment --systemd --all &
#kitty &
#conky -c ~/.config/conky/dobbie_np2.conkyrc &