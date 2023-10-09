#!/bin/bash

# Define the command to run
COMMAND="$XDG_CONFIG_HOME/waybar/scripts/recording.sh toggle fullscreen"

# Check if the command is running
if pgrep -f "$COMMAND" >/dev/null; then
    echo "Stopping the command: $COMMAND"
    pkill -f "$COMMAND"
else
    echo "Starting the command: $COMMAND"
    $COMMAND &
fi
