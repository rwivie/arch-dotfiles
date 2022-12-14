# Enable Powerlevel10k instant prompt. Should stay close to the top of ~/.zshrc.
# Initialization code that may require console input (password prompts, [y/n]
# confirmations, etc.) must go above this block; everything else may go below.
if [[ -r "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh" ]]; then
  source "${XDG_CACHE_HOME:-$HOME/.cache}/p10k-instant-prompt-${(%):-%n}.zsh"
fi

# Lines configured by zsh-newuser-install
HISTFILE=~/.histfile
HISTSIZE=1000
SAVEHIST=1000
bindkey -e
# End of lines configured by zsh-newuser-install
# The following lines were added by compinstall
zstyle :compinstall filename '/home/ron/.zshrc'

autoload -Uz compinit
compinit
# End of lines added by compinstall

export EDITOR='nano'
export VISUAL='mousepad'
export BROWSER="firefox"


#=== Test and then source alias definitions.
if [ -f ~/.aliases ]; then
        source ~/.aliases
else
        print "Note: ~.aliases is unavailable."
fi

#=== so I can write from other distros
umask 0002

#=== command not found
source /usr/share/doc/pkgfile/command-not-found.zsh

#=== for sticky-note
if [[ $STICKY_NOTE ]]; then
  PS1=
  cat "$HOME/tmp/sticky-note"
  return
fi

source /usr/share/zsh-theme-powerlevel10k/powerlevel10k.zsh-theme

# To customize prompt, run `p10k configure` or edit ~/.p10k.zsh.
[[ ! -f ~/.p10k.zsh ]] || source ~/.p10k.zsh
