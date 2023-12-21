#!/usr/bin/env bash

op=$( echo -e " Poweroff\n  Reboot\n Suspend\n Lock\n Logout" | wofi --conf=$HOME/.config/hypr/wofi/config.power --style=$HOME/.config/hypr/wofi/style_power.css | awk '{print tolower($2)}' )

case $op in 
        poweroff)
                ;&
        reboot)
                ;&
        suspend)
                systemctl $op
                ;;
        lock)
		swaylock
                ;;
        logout)
                #hyprctl dispatch exit
                killall -9 Hyprland
                ;;
esac
