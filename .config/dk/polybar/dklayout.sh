#!/bin/bash

#==== this script is from packrat @ https://github.com/PackRat-SC2018/desktop-01-configs he has some great stuff there.
# define layouts array

# mimic dwm style layout symbols
#
typeset -A layouts=(
[tile]="[]="
[rtile]="=[]"
[mono]="[M]"
[none]="><>"
[float]="[F]"
[grid]="[G]"
[spiral]="[S]"
[dwindle]="󰕴"
[tstack]="[TT]"
[astack]="[AT]"
)

# or use iconic font
# mimic dwm style layout symbols
#
#typeset -A layouts=(
#[tile]="[]="
#[rtile]="=[]"
#[mono]="[ ]"
#[none]="< >"
#[grid]="#"
#[spiral]="\@"
#[dwindle]="@/"
#[tstack]="="
#)

layout=$(dkcmd status num=1 | grep '^L' | sed 's/^L//')
layout="${layouts[$layout]}"
# echo "${$layout:-???}"  # ??? If current layout is unknown # error line 18: ${$layout:-???}: bad substitution

echo $layout

exit 0;
