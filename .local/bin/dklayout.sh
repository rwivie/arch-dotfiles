#!/bin/sh

#  

xmenu <<EOF | sh &
[]= tile	dkcmd set layout tile pad left=0 right=0 top=0 bottom=0 gap=10
=[] rtile	dkcmd set layout rtile pad left=0 right=0 top=0 bottom=0 gap=10
[M] mono	dkcmd set layout mono pad left=0 right=0 top=0 bottom=0 gap=0
><> none	dkcmd set layout none
[G] grid	dkcmd set layout grid pad left=0 right=0 top=0 bottom=0 gap=10
[S]stack	dkcmd set layout spiral pad left=0 right=0 top=0 bottom=0 gap=10
󰕴 dwindle	dkcmd set layout dwindle pad left=0 right=0 top=0 bottom=0 gap=10
[TT] tstack	dkcmd set layout tstack pad left=0 right=0 top=0 bottom=0 gap=10

 restart dk	killall pasystray && dkcmd restart
EOF