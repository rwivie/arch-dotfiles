#!/usr/bin/env sh

# Terminate already running bar instances
killall -q polybar

# Wait until the processes have been shut down
while pgrep -x polybar >/dev/null; do sleep 1; done

#==== try to load variables ??
#export label-used="%{F${colors.yellow}}used:%gb_used%%{F-}"
#export label-free="%{F${colors.green}}free:%gb_free%%{F-}"
#export label-total="%{F${colors.purple}}total:%gb_total%%{F-}"


# Launch bar1 and bar2  polybar yourbar 2>/path/to/logfile &
polybar i3-bar 2>/home/ron/.polybar-log &
polybar i3-tray 2>/home/ron/.polybar-log &

