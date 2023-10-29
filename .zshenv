#!/bin/zsh

typeset -U path PATH
path=(~/.local/bin ~/.local/bin/statusbar ~/.cargo/bin $path)
export PATH

#==== exports
export EDITOR='nano'
export VISUAL='mousepad'
export BROWSER="firefox"
export TERMINAL="kitty"
export QT_QPA_PLATFORMTHEME=qt5ct
export WTRLOC="Coleman"

#==== for ranger to use only local config
export RANGER_LOAD_DEFAULT_RC=false

#==== use either mesa's radv or amd's amdvlk
#AMD_VULKAN_ICD=AMDVLK
export AMD_VULKAN_ICD=RADV


export LIBVA_DRIVER_NAME=radeonsi
#export VDPAU_DRIVER=nvidia
export VDPAU_DRIVER=radeonsi
#export VDPAU_DRIVER=radeonsi_drv_video

# XDG - set defaults as they may not be set
# See https://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html
# and https://wiki.archlinux.org/index.php/XDG_Base_Directory_support
export XDG_CONFIG_HOME="$HOME/.config"
export XDG_DATA_HOME="$HOME/.local/share"
export XDG_CACHE_HOME="$HOME/.cache"

if [ ! -w ${XDG_RUNTIME_DIR:="/run/user/$UID"} ]; then
    echo "\$XDG_RUNTIME_DIR ($XDG_RUNTIME_DIR) not writable. Unsetting." >&2
    unset XDG_RUNTIME_DIR
else
    export XDG_RUNTIME_DIR
fi