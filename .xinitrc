#!/bin/sh

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

# merge in defaults and keymaps

if [ -f $sysresources ]; then
    xrdb -merge $sysresources
fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then
    xrdb -merge "$userresources"
fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# user init scripts and settings
#[ -r ~/.Xmodmap ] && xmodmap ~/.Xmodmap
[ -r ~/.Xresources ] && xrdb -merge ~/.Xresources
[ -r ~/.xprofile ] && . ~/.xprofile

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

## Here dkwm is kept as default
#session=${1:-dkwm}

#case $session in
#    i3wm              ) exec i3wm;;
#    dkwm              ) exec dkwm;;
#    dwmwm             ) exec dwmwm;;
##    kde               ) exec startplasma-x11;;
#    xfce|xfce4        ) exec startxfce4;;
#    fvwmwm            ) exec fvwmwm;;
#    obwm              ) exec openbox-session;;
#    gnwmx             ) exec gnwmx;;
#    # No known session, try to run it as command
#    *                 ) exec $1;;
#esac

#==== for gnome x11
#export XDG_SESSION_TYPE=x11
#export GDK_BACKEND=x11
#xautolock -time 10 -locker 'lock | xset dpms force off' -corners '+-00' -cornerdelay 15 -notify 15 -notifier "notify-send 'Screen will lock in 15 s'" &
#exec gnome-session

#==== for gnome wayland  uncomment section in ~/.bash_profile
#XDG_SESSION_TYPE=wayland dbus-run-session gnome-session # or use
#gnome-shell --wayland

#==== for budgie
#export XDG_SESSION_TYPE="x11"
#export XDG_CURRENT_DESKTOP=Budgie:GNOME
#exec budgie-desktop

#==== for dwm
export XDG_SESSION_DESKTOP="dwm"
export XDG_CURRENT_DESKTOP="dwm"
export XDG_SESSION_TYPE="x11"
##exec dwmstart.sh
exec /home/ron/.config/dwm-6.4/dwm 2>&1 | tee ~/.dwm.log

#==== for bspwm
#export XDG_SESSION_DESKTOP="bspwm"
#export XDG_CURRENT_DESKTOP="bspwm"
#export XDG_SESSION_TYPE="x11"
#exec bspwm

#==== for dk
#export XDG_SESSION_DESKTOP="dk"
#export XDG_CURRENT_DESKTOP="dk"
#export XDG_SESSION_TYPE="x11"
#exec dbus-run-session dk
#exec dk

#==== for qtile
#export XDG_SESSION_DESKTOP="qtile"
#export XDG_CURRENT_DESKTOP="qtile"
#export XDG_SESSION_TYPE="x11"
#exec dbus-run-session qtile start

#==== for awesome
#exec awesome

#==== for i3 
#export XDG_SESSION_TYPE="x11"
#export XDG_CURRENT_DESKTOP="i3"
#exec i3
#exec i3 -V -d all &>> "$HOME/.i3.log"

#==== for fvwm3
#export XDG_SESSION_DESKTOP="fvwm"
#export XDG_CURRENT_DESKTOP="fvwm"
#exec fvwmstart.sh

#exec startxfce4
#exec openbox-session
