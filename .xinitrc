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

#==== for gnome x11
#export XDG_SESSION_TYPE=x11
#export GDK_BACKEND=x11
#xautolock -time 10 -locker 'lock | xset dpms force off' -corners '+-00' -cornerdelay 15 -notify 15 -notifier "notify-send 'Screen will lock in 15 s'" &
#exec gnome-session

#==== for gnome wayland  uncomment section in ~/.bash_profile
#XDG_SESSION_TYPE=wayland dbus-run-session gnome-session # or use
#gnome-shell --wayland

#==== for dwm
export XDG_SESSION_DESKTOP="dwm"
export XDG_CURRENT_DESKTOP="dwm"
export XDG_SESSION_TYPE="x11"
exec dwmstart.sh

#==== for i3 
#export XDG_SESSION_TYPE="x11"
#export XDG_CURRENT_DESKTOP="i3"
#exec i3
#exec i3 -V -d all &>> "$HOME/.i3.log"

#exec startxfce4
#exec openbox-session
#exec fvwmstart.sh
#exec dk
#exec jwm
