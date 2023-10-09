#!/bin/sh

# You must place file "COPYING" in same folder of this script.
FILE=`dirname $0`/keybinds.conf

zenity --text-info \
       --title="License" \
       --filename=$FILE \
       --width=800 \
       --height=600 \
       --checkbox="I would like to edit cheatsheet."

case $? in
    0)
        #echo "...editing "
        notify-send "here we go ... "
	# next step
        exec mousepad $HOME/.config/hypr/keybinds.conf
	;;
    1)
        #echo "Closing..."
        notify-send "aaawwwww fuuuccckkk!!!!"
	;;
    -1)
        #echo "awww fuuuck!!!!."
        ;;
esac